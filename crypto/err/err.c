/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
/* ====================================================================
 * Copyright (c) 1998-2006 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com). */

#include <openssl/err.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

#if defined(OPENSSL_WINDOWS)
#include <Windows.h>
#endif

#include <openssl/lhash.h>
#include <openssl/mem.h>
#include <openssl/thread.h>


/* err_fns contains a pointer to the current error implementation. */
static const struct ERR_FNS_st *err_fns = NULL;
extern const struct ERR_FNS_st openssl_err_default_impl;

#define ERRFN(a) err_fns->a

/* err_fns_check is an internal function that checks whether "err_fns" is set
 * and if not, sets it to the default. */
static void err_fns_check(void) {
  /* In practice, this is not a race problem because loading the error strings
   * at init time will cause this pointer to be set before the process goes
   * multithreaded. */
  if (err_fns) {
    return;
  }

  CRYPTO_w_lock(CRYPTO_LOCK_ERR);
  if (!err_fns) {
    err_fns = &openssl_err_default_impl;
  }
  CRYPTO_w_unlock(CRYPTO_LOCK_ERR);
}

/* err_clear_data frees the optional |data| member of the given error. */
static void err_clear_data(struct err_error_st *error) {
  if (error->data != NULL && (error->flags & ERR_FLAG_MALLOCED) != 0) {
    OPENSSL_free(error->data);
  }
  error->data = NULL;
  error->flags &= ~ERR_FLAG_MALLOCED;
}

/* err_clear clears the given queued error. */
static void err_clear(struct err_error_st *error) {
  err_clear_data(error);
  memset(error, 0, sizeof(struct err_error_st));
}

/* err_get_state gets the ERR_STATE object for the current thread. */
static ERR_STATE *err_get_state(void) {
  err_fns_check();
  return ERRFN(get_state)();
}

static uint32_t get_error_values(int inc, int top, const char **file, int *line,
                                 char **data, int *flags) {
  unsigned i = 0;
  ERR_STATE *state;
  struct err_error_st *error;
  uint32_t ret;

  state = err_get_state();

  if (state->bottom == state->top) {
    return 0;
  }

  if (top) {
    /* last error */
    i = state->top;
  } else {
    i = (state->bottom + 1) % ERR_NUM_ERRORS;
  }

  error = &state->errors[i];
  ret = error->packed;

  if (file != NULL && line != NULL) {
    if (error->file == NULL) {
      *file = "NA";
      *line = 0;
    } else {
      *file = error->file;
      *line = error->line;
    }
  }

  if (data != NULL) {
    if (error->data == NULL) {
      *data = "";
      if (flags != NULL) {
        *flags = 0;
      }
    } else {
      *data = error->data;
      if (flags != NULL) {
        *flags = error->flags & ERR_FLAG_PUBLIC_MASK;
      }
      error->data = NULL;
      error->flags = 0;
    }
  }

  if (inc) {
    assert(!top);
    err_clear(error);
    state->bottom = i;
  }

  return ret;
}

uint32_t ERR_get_error(void) {
  return get_error_values(1, 0, NULL, NULL, NULL, NULL);
}

uint32_t ERR_get_error_line(const char **file, int *line) {
  return get_error_values(1, 0, file, line, NULL, NULL);
}

uint32_t ERR_get_error_line_data(const char **file, int *line,
                                 char **data, int *flags) {
  return get_error_values(1, 0, file, line, data, flags);
}

uint32_t ERR_peek_error(void) {
  return get_error_values(0, 0, NULL, NULL, NULL, NULL);
}

uint32_t ERR_peek_error_line(const char **file, int *line) {
  return get_error_values(0, 0, file, line, NULL, NULL);
}

uint32_t ERR_peek_error_line_data(const char **file, int *line,
                                  const char **data, int *flags) {
  return get_error_values(0, 0, file, line, (char **) data, flags);
}

uint32_t ERR_peek_last_error(void) {
  return get_error_values(0, 1, NULL, NULL, NULL, NULL);
}

uint32_t ERR_peek_last_error_line(const char **file, int *line) {
  return get_error_values(0, 1, file, line, NULL, NULL);
}

uint32_t ERR_peek_last_error_line_data(const char **file, int *line,
                                       const char **data, int *flags) {
  return get_error_values(0, 1, file, line, (char **) data, flags);
}

void ERR_clear_error(void) {
  ERR_STATE *const state = err_get_state();
  unsigned i;

  for (i = 0; i < ERR_NUM_ERRORS; i++) {
    err_clear(&state->errors[i]);
  }

  state->top = state->bottom = 0;
}

void ERR_remove_thread_state(const CRYPTO_THREADID *tid) {
  CRYPTO_THREADID current;
  ERR_STATE *state;
  unsigned i;

  if (tid == NULL) {
    CRYPTO_THREADID_current(&current);
    tid = &current;
  }

  err_fns_check();
  state = ERRFN(release_state)(tid);
  if (state == NULL) {
    return;
  }

  for (i = 0; i < ERR_NUM_ERRORS; i++) {
    err_clear(&state->errors[i]);
  }

  OPENSSL_free(state);
}

int ERR_get_next_error_library() {
  err_fns_check();
  return ERRFN(get_next_library)();
}

void ERR_clear_system_error(void) {
  errno = 0;
}

char *ERR_error_string(uint32_t packed_error, char *ret) {
  static char buf[ERR_ERROR_STRING_BUF_LEN];

  if (ret == NULL) {
    /* TODO(fork): remove this. */
    ret = buf;
  }

#if !defined(NDEBUG)
  /* This is aimed to help catch callers who don't provide
   * |ERR_ERROR_STRING_BUF_LEN| bytes of space. */
  memset(ret, 0, ERR_ERROR_STRING_BUF_LEN);
#endif

  ERR_error_string_n(packed_error, ret, ERR_ERROR_STRING_BUF_LEN);

  return ret;
}

void ERR_error_string_n(uint32_t packed_error, char *buf, size_t len) {
  char lib_buf[64], func_buf[64], reason_buf[64];
  const char *lib_str, *func_str, *reason_str;
  unsigned lib, func, reason;

  if (len == 0) {
    return;
  }

  lib = ERR_GET_LIB(packed_error);
  func = ERR_GET_FUNC(packed_error);
  reason = ERR_GET_REASON(packed_error);

  lib_str = ERR_lib_error_string(packed_error);
  func_str = ERR_func_error_string(packed_error);
  reason_str = ERR_reason_error_string(packed_error);

  if (lib_str == NULL) {
    BIO_snprintf(lib_buf, sizeof(lib_buf), "lib(%u)", lib);
    lib_str = lib_buf;
  }

  if (func_str == NULL) {
    BIO_snprintf(func_buf, sizeof(func_buf), "func(%u)", func);
    func_str = func_buf;
  }

  if (reason_str == NULL) {
    BIO_snprintf(reason_buf, sizeof(reason_buf), "reason(%u)", reason);
    reason_str = reason_buf;
  }

  BIO_snprintf(buf, len, "error:%08" PRIx32 ":%s:%s:%s",
               packed_error, lib_str, func_str, reason_str);

  if (strlen(buf) == len - 1) {
    /* output may be truncated; make sure we always have 5 colon-separated
     * fields, i.e. 4 colons. */
    static const unsigned num_colons = 4;
    unsigned i;
    char *s = buf;

    if (len <= num_colons) {
      /* In this situation it's not possible to ensure that the correct number
       * of colons are included in the output. */
      return;
    }

    for (i = 0; i < num_colons; i++) {
      char *colon = strchr(s, ':');
      char *last_pos = &buf[len - 1] - num_colons + i;

      if (colon == NULL || colon > last_pos) {
        /* set colon |i| at last possible position (buf[len-1] is the
         * terminating 0). If we're setting this colon, then all whole of the
         * rest of the string must be colons in order to have the correct
         * number. */
        memset(last_pos, ':', num_colons - i);
        break;
      }

      s = colon + 1;
    }
  }
}

/* err_component_error_string returns the error string associated with
 * |packed_error|, which must be of a special form matching the keys inserted
 * into the error hash table. */
static const char *err_component_error_string(uint32_t packed_error) {
  ERR_STRING_DATA *p;

  err_fns_check();
  p = ERRFN(get_item)(packed_error);

  if (p == NULL) {
    return NULL;
  }
  return p->string;
}

const char *ERR_lib_error_string(uint32_t packed_error) {
  return err_component_error_string(ERR_PACK(ERR_GET_LIB(packed_error), 0, 0));
}

const char *ERR_func_error_string(uint32_t packed_error) {
  return err_component_error_string(
      ERR_PACK(ERR_GET_LIB(packed_error), ERR_GET_FUNC(packed_error), 0));
}

const char *ERR_reason_error_string(uint32_t packed_error) {
  const char *reason_str = err_component_error_string(
      ERR_PACK(ERR_GET_LIB(packed_error), 0, ERR_GET_REASON(packed_error)));

  if (reason_str != NULL) {
    return reason_str;
  }

  return err_component_error_string(
      ERR_PACK(0, 0, ERR_GET_REASON(packed_error)));
}

void ERR_print_errors_cb(ERR_print_errors_callback_t callback, void *ctx) {
  CRYPTO_THREADID current_thread;
  char buf[ERR_ERROR_STRING_BUF_LEN];
  char buf2[1024];
  unsigned long thread_hash;
  const char *file;
  char *data;
  int line, flags;
  uint32_t packed_error;

  CRYPTO_THREADID_current(&current_thread);
  thread_hash = CRYPTO_THREADID_hash(&current_thread);

  for (;;) {
    packed_error = ERR_get_error_line_data(&file, &line, &data, &flags);
    if (packed_error == 0) {
      break;
    }

    ERR_error_string_n(packed_error, buf, sizeof(buf));
    BIO_snprintf(buf2, sizeof(buf2), "%lu:%s:%s:%d:%s\n", thread_hash, buf,
                 file, line, (flags & ERR_FLAG_STRING) ? data : "");
    if (callback(buf2, strlen(buf2), ctx) <= 0) {
      break;
    }
    if (flags & ERR_FLAG_MALLOCED) {
      OPENSSL_free(data);
    }
  }
}

/* err_set_error_data sets the data on the most recent error. The |flags|
 * argument is a combination of the |ERR_FLAG_*| values. */
static void err_set_error_data(char *data, int flags) {
  ERR_STATE *const state = err_get_state();
  struct err_error_st *error;

  if (state->top == state->bottom) {
    return;
  }

  error = &state->errors[state->top];

  err_clear_data(error);
  error->data = data;
  error->flags = flags;
}

void ERR_put_error(int library, int func, int reason, const char *file,
                   unsigned line) {
  ERR_STATE *const state = err_get_state();
  struct err_error_st *error;

  if (library == ERR_LIB_SYS && reason == 0) {
#if defined(WIN32)
    reason = GetLastError();
#else
    reason = errno;
#endif
  }

  state->top = (state->top + 1) % ERR_NUM_ERRORS;
  if (state->top == state->bottom) {
    state->bottom = (state->bottom + 1) % ERR_NUM_ERRORS;
  }

  error = &state->errors[state->top];
  err_clear(error);
  error->file = file;
  error->line = line;
  error->packed = ERR_PACK(library, func, reason);
}

/* ERR_add_error_data_vdata takes a variable number of const char* pointers,
 * concatenates them and sets the result as the data on the most recent
 * error. */
static void err_add_error_vdata(unsigned num, va_list args) {
  size_t alloced, new_len, len = 0, substr_len;
  char *buf;
  const char *substr;
  unsigned i;

  alloced = 80;
  buf = OPENSSL_malloc(alloced + 1);
  if (buf == NULL) {
    return;
  }

  for (i = 0; i < num; i++) {
    substr = va_arg(args, const char *);
    if (substr == NULL) {
      continue;
    }

    substr_len = strlen(substr);
    new_len = len + substr_len;
    if (new_len > alloced) {
      char *new_buf;

      if (alloced + 20 + 1 < alloced) {
        /* overflow. */
        OPENSSL_free(buf);
        return;
      }

      alloced = new_len + 20;
      new_buf = OPENSSL_realloc(buf, alloced + 1);
      if (new_buf == NULL) {
        OPENSSL_free(buf);
        return;
      }
      buf = new_buf;
    }

    memcpy(buf + len, substr, substr_len);
    len = new_len;
  }

  buf[len] = 0;
  err_set_error_data(buf, ERR_FLAG_MALLOCED | ERR_FLAG_STRING);
}

void ERR_add_error_data(unsigned count, ...) {
  va_list args;
  va_start(args, count);
  err_add_error_vdata(count, args);
  va_end(args);
}

void ERR_add_error_dataf(const char *format, ...) {
  va_list ap;
  char *buf;
  static const unsigned buf_len = 256;

  /* A fixed-size buffer is used because va_copy (which would be needed in
   * order to call vsnprintf twice and measure the buffer) wasn't defined until
   * C99. */
  buf = OPENSSL_malloc(buf_len + 1);
  if (buf == NULL) {
    return;
  }

  va_start(ap, format);
  BIO_vsnprintf(buf, buf_len, format, ap);
  buf[buf_len] = 0;
  va_end(ap);

  err_set_error_data(buf, ERR_FLAG_MALLOCED | ERR_FLAG_STRING);
}

int ERR_set_mark(void) {
  ERR_STATE *const state = err_get_state();

  if (state->bottom == state->top) {
    return 0;
  }
  state->errors[state->top].flags |= ERR_FLAG_MARK;
  return 1;
}

int ERR_pop_to_mark(void) {
  ERR_STATE *const state = err_get_state();
  struct err_error_st *error;

  while (state->bottom != state->top) {
    error = &state->errors[state->top];

    if ((error->flags & ERR_FLAG_MARK) != 0) {
      break;
    }

    err_clear(error);
    if (state->top == 0) {
      state->top = ERR_NUM_ERRORS - 1;
    } else {
      state->top--;
    }
  }

  if (state->bottom == state->top) {
    return 0;
  }

  error->flags &= ~ERR_FLAG_MARK;
  return 1;
}

static const char *const kLibraryNames[ERR_NUM_LIBS] = {
    "invalid library (0)",
    "unknown library",                            /* ERR_LIB_NONE */
    "system library",                             /* ERR_LIB_SYS */
    "bignum routines",                            /* ERR_LIB_BN */
    "RSA routines",                               /* ERR_LIB_RSA */
    "Diffie-Hellman routines",                    /* ERR_LIB_DH */
    "public key routines",                        /* ERR_LIB_EVP */
    "memory buffer routines",                     /* ERR_LIB_BUF */
    "object identifier routines",                 /* ERR_LIB_OBJ */
    "PEM routines",                               /* ERR_LIB_PEM */
    "DSA routines",                               /* ERR_LIB_DSA */
    "X.509 certificate routines",                 /* ERR_LIB_X509 */
    "ASN.1 encoding routines",                    /* ERR_LIB_ASN1 */
    "configuration file routines",                /* ERR_LIB_CONF */
    "common libcrypto routines",                  /* ERR_LIB_CRYPTO */
    "elliptic curve routines",                    /* ERR_LIB_EC */
    "SSL routines",                               /* ERR_LIB_SSL */
    "BIO routines",                               /* ERR_LIB_BIO */
    "PKCS7 routines",                             /* ERR_LIB_PKCS7 */
    "PKCS8 routines",                             /* ERR_LIB_PKCS8 */
    "X509 V3 routines",                           /* ERR_LIB_X509V3 */
    "PKCS12 routines",                            /* ERR_LIB_PKCS12 */
    "random number generator",                    /* ERR_LIB_RAND */
    "ENGINE routines",                            /* ERR_LIB_ENGINE */
    "OCSP routines",                              /* ERR_LIB_OCSP */
    "UI routines",                                /* ERR_LIB_UI */
    "COMP routines",                              /* ERR_LIB_COMP */
    "ECDSA routines",                             /* ERR_LIB_ECDSA */
    "ECDH routines",                              /* ERR_LIB_ECDH */
    "HMAC routines",                              /* ERR_LIB_HMAC */
    "Digest functions",                           /* ERR_LIB_DIGEST */
    "Cipher functions",                           /* ERR_LIB_CIPHER */
    "User defined functions",                     /* ERR_LIB_USER */
};

#define NUM_SYS_ERRNOS 127

/* kStaticErrors provides storage for ERR_STRING_DATA values that are created
 * at init time because we assume that ERR_STRING_DATA structures aren't
 * allocated on the heap. */
static ERR_STRING_DATA kStaticErrors[ERR_NUM_LIBS * 2 + NUM_SYS_ERRNOS];

static ERR_STRING_DATA kGlobalErrors[] = {
    {ERR_R_MALLOC_FAILURE, "malloc failure"},
    {ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED, "function should not be called"},
    {ERR_R_PASSED_NULL_PARAMETER, "passed a null parameter"},
    {ERR_R_INTERNAL_ERROR, "internal error"},
    {ERR_R_OVERFLOW, "overflow"},

    {ERR_PACK(ERR_LIB_SYS, SYS_F_fopen, 0), "fopen"},
    {ERR_PACK(ERR_LIB_SYS, SYS_F_fclose, 0), "fclose"},
    {ERR_PACK(ERR_LIB_SYS, SYS_F_fread, 0), "fread"},
    {ERR_PACK(ERR_LIB_SYS, SYS_F_fwrite, 0), "fwrite"},
    {ERR_PACK(ERR_LIB_SYS, SYS_F_socket, 0), "socket"},
    {ERR_PACK(ERR_LIB_SYS, SYS_F_setsockopt, 0), "setsockopt"},
    {ERR_PACK(ERR_LIB_SYS, SYS_F_connect, 0), "connect"},
    {ERR_PACK(ERR_LIB_SYS, SYS_F_getaddrinfo, 0), "getaddrinfo"},

    {0, NULL},
};


extern const ERR_STRING_DATA ASN1_error_string_data[];
extern const ERR_STRING_DATA BIO_error_string_data[];
extern const ERR_STRING_DATA BN_error_string_data[];
extern const ERR_STRING_DATA BUF_error_string_data[];
extern const ERR_STRING_DATA CIPHER_error_string_data[];
extern const ERR_STRING_DATA CONF_error_string_data[];
extern const ERR_STRING_DATA CRYPTO_error_string_data[];
extern const ERR_STRING_DATA DH_error_string_data[];
extern const ERR_STRING_DATA DIGEST_error_string_data[];
extern const ERR_STRING_DATA DSA_error_string_data[];
extern const ERR_STRING_DATA ECDH_error_string_data[];
extern const ERR_STRING_DATA ECDSA_error_string_data[];
extern const ERR_STRING_DATA EC_error_string_data[];
extern const ERR_STRING_DATA EVP_error_string_data[];
extern const ERR_STRING_DATA OBJ_error_string_data[];
extern const ERR_STRING_DATA PEM_error_string_data[];
extern const ERR_STRING_DATA RSA_error_string_data[];
extern const ERR_STRING_DATA X509V3_error_string_data[];
extern const ERR_STRING_DATA X509_error_string_data[];

static void err_load_strings(void) {
  unsigned i, j = 0;

  err_fns_check();

  /* This loop loads strings for the libraries for the ERR_R_*_LIB
   * reasons. */
  for (i = ERR_LIB_NONE; i < ERR_NUM_LIBS; i++) {
    ERR_STRING_DATA *data = &kStaticErrors[j++];
    data->string = kLibraryNames[i];
    data->error = ERR_PACK(i, 0, 0);
    ERRFN(set_item)(data);

    data = &kStaticErrors[j++];
    data->string = kLibraryNames[i];
    data->error = ERR_PACK(0, 0, i);
    ERRFN(set_item)(data);
  }

  for (i = 1; i < 1 + NUM_SYS_ERRNOS; i++) {
    /* The "SYS" library sets errno values as the reason for its errors.
     * Thus we load the first |NUM_SYS_ERRNOS| errno strings as the
     * reason strings for that library. */

    ERR_STRING_DATA *data = &kStaticErrors[j++];
    data->string = strerror(i);
    data->error = ERR_PACK(ERR_LIB_SYS, 0, i);
    ERRFN(set_item)(data);
  }

  ERR_load_strings(kGlobalErrors);

  ERR_load_strings(ASN1_error_string_data);
  ERR_load_strings(BIO_error_string_data);
  ERR_load_strings(BN_error_string_data);
  ERR_load_strings(BUF_error_string_data);
  ERR_load_strings(CIPHER_error_string_data);
  ERR_load_strings(CONF_error_string_data);
  ERR_load_strings(CRYPTO_error_string_data);
  ERR_load_strings(DH_error_string_data);
  ERR_load_strings(DIGEST_error_string_data);
  ERR_load_strings(DSA_error_string_data);
  ERR_load_strings(ECDH_error_string_data);
  ERR_load_strings(ECDSA_error_string_data);
  ERR_load_strings(EC_error_string_data);
  ERR_load_strings(EVP_error_string_data);
  ERR_load_strings(OBJ_error_string_data);
  ERR_load_strings(PEM_error_string_data);
  ERR_load_strings(RSA_error_string_data);
  ERR_load_strings(X509V3_error_string_data);
  ERR_load_strings(X509_error_string_data);
}

void ERR_load_strings(const ERR_STRING_DATA *str) {
  err_fns_check();

  while (str->error) {
    ERRFN(set_item)(str);
    str++;
  }
}

void ERR_load_crypto_strings() { err_load_strings(); }

void ERR_free_strings() {
  err_fns_check();
  ERRFN(shutdown)();
}

void ERR_load_BIO_strings() {}
