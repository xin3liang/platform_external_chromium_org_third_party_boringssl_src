/* Copyright (c) 2014, Google Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

#include <openssl/base.h>

#if !defined(OPENSSL_WINDOWS)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include <sys/types.h>

#include <openssl/bio.h>
#include <openssl/bytestring.h>
#include <openssl/ssl.h>

#include "async_bio.h"
#include "packeted_bio.h"
#include "test_config.h"

static int usage(const char *program) {
  fprintf(stderr, "Usage: %s [flags...]\n",
          program);
  return 1;
}

static int g_ex_data_index = 0;

static void SetConfigPtr(SSL *ssl, const TestConfig *config) {
  SSL_set_ex_data(ssl, g_ex_data_index, (void *)config);
}

static const TestConfig *GetConfigPtr(SSL *ssl) {
  return (const TestConfig *)SSL_get_ex_data(ssl, g_ex_data_index);
}

static int early_callback_called = 0;

static int select_certificate_callback(const struct ssl_early_callback_ctx *ctx) {
  early_callback_called = 1;

  const TestConfig *config = GetConfigPtr(ctx->ssl);

  if (config->expected_server_name.empty()) {
    return 1;
  }

  const uint8_t *extension_data;
  size_t extension_len;
  CBS extension, server_name_list, host_name;
  uint8_t name_type;

  if (!SSL_early_callback_ctx_extension_get(ctx, TLSEXT_TYPE_server_name,
                                            &extension_data,
                                            &extension_len)) {
    fprintf(stderr, "Could not find server_name extension.\n");
    return -1;
  }

  CBS_init(&extension, extension_data, extension_len);
  if (!CBS_get_u16_length_prefixed(&extension, &server_name_list) ||
      CBS_len(&extension) != 0 ||
      !CBS_get_u8(&server_name_list, &name_type) ||
      name_type != TLSEXT_NAMETYPE_host_name ||
      !CBS_get_u16_length_prefixed(&server_name_list, &host_name) ||
      CBS_len(&server_name_list) != 0) {
    fprintf(stderr, "Could not decode server_name extension.\n");
    return -1;
  }

  if (!CBS_mem_equal(&host_name,
                     (const uint8_t*)config->expected_server_name.data(),
                     config->expected_server_name.size())) {
    fprintf(stderr, "Server name mismatch.\n");
  }

  return 1;
}

static int skip_verify(int preverify_ok, X509_STORE_CTX *store_ctx) {
  return 1;
}

static int next_protos_advertised_callback(SSL *ssl,
                                           const uint8_t **out,
                                           unsigned int *out_len,
                                           void *arg) {
  const TestConfig *config = GetConfigPtr(ssl);
  if (config->advertise_npn.empty())
    return SSL_TLSEXT_ERR_NOACK;

  // TODO(davidben): Support passing byte strings with NULs to the
  // test shim.
  *out = (const uint8_t*)config->advertise_npn.data();
  *out_len = config->advertise_npn.size();
  return SSL_TLSEXT_ERR_OK;
}

static int next_proto_select_callback(SSL* ssl,
                                      uint8_t** out,
                                      uint8_t* outlen,
                                      const uint8_t* in,
                                      unsigned inlen,
                                      void* arg) {
  const TestConfig *config = GetConfigPtr(ssl);
  if (config->select_next_proto.empty())
    return SSL_TLSEXT_ERR_NOACK;

  *out = (uint8_t*)config->select_next_proto.data();
  *outlen = config->select_next_proto.size();
  return SSL_TLSEXT_ERR_OK;
}

static int cookie_generate_callback(SSL *ssl, uint8_t *cookie, size_t *cookie_len) {
  *cookie_len = 32;
  memset(cookie, 42, *cookie_len);
  return 1;
}

static int cookie_verify_callback(SSL *ssl, const uint8_t *cookie, size_t cookie_len) {
  if (cookie_len != 32) {
    fprintf(stderr, "Cookie length mismatch.\n");
    return 0;
  }
  for (size_t i = 0; i < cookie_len; i++) {
    if (cookie[i] != 42) {
      fprintf(stderr, "Cookie mismatch.\n");
      return 0;
    }
  }
  return 1;
}

static SSL_CTX *setup_ctx(const TestConfig *config) {
  SSL_CTX *ssl_ctx = NULL;
  DH *dh = NULL;

  const SSL_METHOD *method;
  if (config->is_dtls) {
    // TODO(davidben): Get DTLS 1.2 working and test the version negotiation
    // codepath. This doesn't currently work because
    // - Session resumption is broken: https://crbug.com/403378
    // - DTLS hasn't been updated for EVP_AEAD.
    if (config->is_server) {
      method = DTLSv1_server_method();
    } else {
      method = DTLSv1_client_method();
    }
  } else {
    if (config->is_server) {
      method = SSLv23_server_method();
    } else {
      method = SSLv23_client_method();
    }
  }
  ssl_ctx = SSL_CTX_new(method);
  if (ssl_ctx == NULL) {
    goto err;
  }

  if (config->is_dtls) {
    // DTLS needs read-ahead to function on a datagram BIO.
    //
    // TODO(davidben): this should not be necessary. DTLS code should only
    // expect a datagram BIO.
    SSL_CTX_set_read_ahead(ssl_ctx, 1);
  }

  if (!SSL_CTX_set_ecdh_auto(ssl_ctx, 1)) {
    goto err;
  }

  if (!SSL_CTX_set_cipher_list(ssl_ctx, "ALL")) {
    goto err;
  }

  dh = DH_get_2048_256(NULL);
  if (!SSL_CTX_set_tmp_dh(ssl_ctx, dh)) {
    goto err;
  }

  SSL_CTX_set_session_cache_mode(ssl_ctx, SSL_SESS_CACHE_BOTH);

  ssl_ctx->select_certificate_cb = select_certificate_callback;

  SSL_CTX_set_next_protos_advertised_cb(
      ssl_ctx, next_protos_advertised_callback, NULL);
  SSL_CTX_set_next_proto_select_cb(
      ssl_ctx, next_proto_select_callback, NULL);

  SSL_CTX_set_cookie_generate_cb(ssl_ctx, cookie_generate_callback);
  SSL_CTX_set_cookie_verify_cb(ssl_ctx, cookie_verify_callback);

  DH_free(dh);
  return ssl_ctx;

 err:
  if (dh != NULL) {
    DH_free(dh);
  }
  if (ssl_ctx != NULL) {
    SSL_CTX_free(ssl_ctx);
  }
  return NULL;
}

static int retry_async(SSL *ssl, int ret, BIO *bio) {
  // No error; don't retry.
  if (ret >= 0) {
    return 0;
  }
  // See if we needed to read or write more. If so, allow one byte through on
  // the appropriate end to maximally stress the state machine.
  int err = SSL_get_error(ssl, ret);
  if (err == SSL_ERROR_WANT_READ) {
    async_bio_allow_read(bio, 1);
    return 1;
  } else if (err == SSL_ERROR_WANT_WRITE) {
    async_bio_allow_write(bio, 1);
    return 1;
  }
  return 0;
}

static int do_exchange(SSL_SESSION **out_session,
                       SSL_CTX *ssl_ctx,
                       const TestConfig *config,
                       bool is_resume,
                       int fd,
                       SSL_SESSION *session) {
  early_callback_called = 0;

  SSL *ssl = SSL_new(ssl_ctx);
  if (ssl == NULL) {
    BIO_print_errors_fp(stdout);
    return 1;
  }

  SetConfigPtr(ssl, config);

  if (config->fallback_scsv) {
    if (!SSL_enable_fallback_scsv(ssl)) {
      BIO_print_errors_fp(stdout);
      return 1;
    }
  }
  if (!config->key_file.empty()) {
    if (!SSL_use_PrivateKey_file(ssl, config->key_file.c_str(),
                                 SSL_FILETYPE_PEM)) {
      BIO_print_errors_fp(stdout);
      return 1;
    }
  }
  if (!config->cert_file.empty()) {
    if (!SSL_use_certificate_file(ssl, config->cert_file.c_str(),
                                  SSL_FILETYPE_PEM)) {
      BIO_print_errors_fp(stdout);
      return 1;
    }
  }
  if (config->require_any_client_certificate) {
    SSL_set_verify(ssl, SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT,
                   skip_verify);
  }
  if (config->false_start) {
    SSL_set_mode(ssl, SSL_MODE_HANDSHAKE_CUTTHROUGH);
  }
  if (config->cbc_record_splitting) {
    SSL_set_mode(ssl, SSL_MODE_CBC_RECORD_SPLITTING);
  }
  if (config->partial_write) {
    SSL_set_mode(ssl, SSL_MODE_ENABLE_PARTIAL_WRITE);
  }
  if (config->no_tls12) {
    SSL_set_options(ssl, SSL_OP_NO_TLSv1_2);
  }
  if (config->no_tls11) {
    SSL_set_options(ssl, SSL_OP_NO_TLSv1_1);
  }
  if (config->no_tls1) {
    SSL_set_options(ssl, SSL_OP_NO_TLSv1);
  }
  if (config->no_ssl3) {
    SSL_set_options(ssl, SSL_OP_NO_SSLv3);
  }
  if (config->cookie_exchange) {
    SSL_set_options(ssl, SSL_OP_COOKIE_EXCHANGE);
  }

  BIO *bio = BIO_new_fd(fd, 1 /* take ownership */);
  if (bio == NULL) {
    BIO_print_errors_fp(stdout);
    return 1;
  }
  if (config->is_dtls) {
    BIO *packeted = packeted_bio_create();
    BIO_push(packeted, bio);
    bio = packeted;
  }
  if (config->async) {
    BIO *async =
        config->is_dtls ? async_bio_create_datagram() : async_bio_create();
    BIO_push(async, bio);
    bio = async;
  }
  SSL_set_bio(ssl, bio, bio);

  if (session != NULL) {
    if (SSL_set_session(ssl, session) != 1) {
      fprintf(stderr, "failed to set session\n");
      return 2;
    }
  }

  int ret;
  do {
    if (config->is_server) {
      ret = SSL_accept(ssl);
    } else {
      ret = SSL_connect(ssl);
    }
  } while (config->async && retry_async(ssl, ret, bio));
  if (ret != 1) {
    SSL_free(ssl);
    BIO_print_errors_fp(stdout);
    return 2;
  }

  if (is_resume && !SSL_session_reused(ssl)) {
    fprintf(stderr, "session was not reused\n");
    return 2;
  }

  if (!config->expected_server_name.empty()) {
    const char *server_name =
        SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);
    if (server_name != config->expected_server_name) {
      fprintf(stderr, "servername mismatch (got %s; want %s)\n",
              server_name, config->expected_server_name.c_str());
      return 2;
    }

    if (!early_callback_called) {
      fprintf(stderr, "early callback not called\n");
      return 2;
    }
  }

  if (!config->expected_certificate_types.empty()) {
    uint8_t *certificate_types;
    int num_certificate_types =
      SSL_get0_certificate_types(ssl, &certificate_types);
    if (num_certificate_types !=
        (int)config->expected_certificate_types.size() ||
        memcmp(certificate_types,
               config->expected_certificate_types.data(),
               num_certificate_types) != 0) {
      fprintf(stderr, "certificate types mismatch\n");
      return 2;
    }
  }

  if (!config->expected_next_proto.empty()) {
    const uint8_t *next_proto;
    unsigned next_proto_len;
    SSL_get0_next_proto_negotiated(ssl, &next_proto, &next_proto_len);
    if (next_proto_len != config->expected_next_proto.size() ||
        memcmp(next_proto, config->expected_next_proto.data(),
               next_proto_len) != 0) {
      fprintf(stderr, "negotiated next proto mismatch\n");
      return 2;
    }
  }

  if (config->write_different_record_sizes) {
    if (config->is_dtls) {
      fprintf(stderr, "write_different_record_sizes not supported for DTLS\n");
      return 6;
    }
    // This mode writes a number of different record sizes in an attempt to
    // trip up the CBC record splitting code.
    uint8_t buf[32769];
    memset(buf, 0x42, sizeof(buf));
    static const size_t kRecordSizes[] = {
        0, 1, 255, 256, 257, 16383, 16384, 16385, 32767, 32768, 32769};
    for (size_t i = 0; i < sizeof(kRecordSizes) / sizeof(kRecordSizes[0]);
         i++) {
      int w;
      const size_t len = kRecordSizes[i];
      size_t off = 0;

      if (len > sizeof(buf)) {
        fprintf(stderr, "Bad kRecordSizes value.\n");
        return 5;
      }

      do {
        w = SSL_write(ssl, buf + off, len - off);
        if (w > 0) {
          off += (size_t) w;
        }
      } while ((config->async && retry_async(ssl, w, bio)) ||
               (w > 0 && off < len));

      if (w < 0 || off != len) {
        SSL_free(ssl);
        BIO_print_errors_fp(stdout);
        return 4;
      }
    }
  } else {
    for (;;) {
      uint8_t buf[512];
      int n;
      do {
        n = SSL_read(ssl, buf, sizeof(buf));
      } while (config->async && retry_async(ssl, n, bio));
      if (n < 0) {
        SSL_free(ssl);
        BIO_print_errors_fp(stdout);
        return 3;
      } else if (n == 0) {
        break;
      } else {
        for (int i = 0; i < n; i++) {
          buf[i] ^= 0xff;
        }
        int w;
        do {
          w = SSL_write(ssl, buf, n);
        } while (config->async && retry_async(ssl, w, bio));
        if (w != n) {
          SSL_free(ssl);
          BIO_print_errors_fp(stdout);
          return 4;
        }
      }
    }
  }

  if (out_session) {
    *out_session = SSL_get1_session(ssl);
  }

  SSL_shutdown(ssl);
  SSL_free(ssl);
  return 0;
}

int main(int argc, char **argv) {
#if !defined(OPENSSL_WINDOWS)
  signal(SIGPIPE, SIG_IGN);
#endif

  if (!SSL_library_init()) {
    return 1;
  }
  g_ex_data_index = SSL_get_ex_new_index(0, NULL, NULL, NULL, NULL);

  TestConfig config;
  if (!ParseConfig(argc - 1, argv + 1, &config)) {
    return usage(argv[0]);
  }

  SSL_CTX *ssl_ctx = setup_ctx(&config);
  if (ssl_ctx == NULL) {
    BIO_print_errors_fp(stdout);
    return 1;
  }

  SSL_SESSION *session = NULL;
  int ret = do_exchange(&session,
                        ssl_ctx, &config,
                        false /* is_resume */,
                        3 /* fd */, NULL /* session */);
  if (ret != 0) {
    goto out;
  }

  if (config.resume) {
    ret = do_exchange(NULL,
                      ssl_ctx, &config,
                      true /* is_resume */,
                      4 /* fd */,
                      config.is_server ? NULL : session);
    if (ret != 0) {
      goto out;
    }
  }

  ret = 0;

out:
  SSL_SESSION_free(session);
  SSL_CTX_free(ssl_ctx);
  return ret;
}
