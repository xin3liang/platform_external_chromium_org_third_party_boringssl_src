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
 *
 * The DSS routines are based on patches supplied by
 * Steven Schoch <schoch@sheba.arc.nasa.gov>. */

#include <openssl/dsa.h>

#include <openssl/asn1.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/ex_data.h>
#include <openssl/mem.h>

#include "internal.h"

extern const DSA_METHOD DSA_default_method;

DSA *DSA_new(void) { return DSA_new_method(NULL); }

DSA *DSA_new_method(const ENGINE *engine) {
  DSA *dsa = (DSA *)OPENSSL_malloc(sizeof(DSA));
  if (dsa == NULL) {
    OPENSSL_PUT_ERROR(DSA, DSA_new_method, ERR_R_MALLOC_FAILURE);
    return NULL;
  }

  memset(dsa, 0, sizeof(DSA));

  if (engine) {
    dsa->meth = ENGINE_get_DSA_method(engine);
  }

  if (dsa->meth == NULL) {
    dsa->meth = (DSA_METHOD*) &DSA_default_method;
  }
  METHOD_ref(dsa->meth);

  dsa->write_params = 1;
  dsa->references = 1;

  if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_DSA, dsa, &dsa->ex_data)) {
    METHOD_unref(dsa->meth);
    OPENSSL_free(dsa);
    return NULL;
  }

  if (dsa->meth->init && !dsa->meth->init(dsa)) {
    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_DSA, dsa, &dsa->ex_data);
    METHOD_unref(dsa->meth);
    OPENSSL_free(dsa);
    return NULL;
  }

  return dsa;
}

void DSA_free(DSA *dsa) {
  if (dsa == NULL) {
    return;
  }

  if (CRYPTO_add(&dsa->references, -1, CRYPTO_LOCK_DSA) > 0) {
    return;
  }

  if (dsa->meth->finish) {
    dsa->meth->finish(dsa);
  }
  METHOD_unref(dsa->meth);

  CRYPTO_free_ex_data(CRYPTO_EX_INDEX_DSA, dsa, &dsa->ex_data);

  if (dsa->p != NULL)
    BN_clear_free(dsa->p);
  if (dsa->q != NULL)
    BN_clear_free(dsa->q);
  if (dsa->g != NULL)
    BN_clear_free(dsa->g);
  if (dsa->pub_key != NULL)
    BN_clear_free(dsa->pub_key);
  if (dsa->priv_key != NULL)
    BN_clear_free(dsa->priv_key);
  if (dsa->kinv != NULL)
    BN_clear_free(dsa->kinv);
  if (dsa->r != NULL)
    BN_clear_free(dsa->r);
  OPENSSL_free(dsa);
}

int DSA_up_ref(DSA *dsa) {
  CRYPTO_add(&dsa->references, 1, CRYPTO_LOCK_DSA);
  return 1;
}

int DSA_generate_parameters_ex(DSA *dsa, unsigned bits, const uint8_t *seed_in,
                               size_t seed_len, int *out_counter,
                               unsigned long *out_h, BN_GENCB *cb) {
  if (dsa->meth->generate_parameters) {
    return dsa->meth->generate_parameters(dsa, bits, seed_in, seed_len,
                                          out_counter, out_h, cb);
  }
  return DSA_default_method.generate_parameters(dsa, bits, seed_in, seed_len,
                                                out_counter, out_h, cb);
}

int DSA_generate_key(DSA *dsa) {
  if (dsa->meth->keygen) {
    return dsa->meth->keygen(dsa);
  }
  return DSA_default_method.keygen(dsa);
}

DSA_SIG *DSA_SIG_new(void) {
  DSA_SIG *sig;
  sig = OPENSSL_malloc(sizeof(DSA_SIG));
  if (!sig) {
    return NULL;
  }
  sig->r = NULL;
  sig->s = NULL;
  return sig;
}

void DSA_SIG_free(DSA_SIG *sig) {
  if (!sig) {
    return;
  }

  if (sig->r) {
    BN_free(sig->r);
  }
  if (sig->s) {
    BN_free(sig->s);
  }
  OPENSSL_free(sig);
}

DSA_SIG *DSA_do_sign(const uint8_t *digest, size_t digest_len, DSA *dsa) {
  if (dsa->meth->sign) {
    return dsa->meth->sign(digest, digest_len, dsa);
  }
  return DSA_default_method.sign(digest, digest_len, dsa);
}

int DSA_do_verify(const uint8_t *digest, size_t digest_len, DSA_SIG *sig,
                  const DSA *dsa) {
  int valid, ret;

  if (dsa->meth->verify) {
    ret = dsa->meth->verify(&valid, digest, digest_len, sig, dsa);
  } else {
    ret = DSA_default_method.verify(&valid, digest, digest_len, sig, dsa);
  }

  if (!ret) {
    return -1;
  } else if (!valid) {
    return 0;
  }
  return 1;
}

int DSA_do_check_signature(int *out_valid, const uint8_t *digest,
                           size_t digest_len, DSA_SIG *sig, const DSA *dsa) {
  if (dsa->meth->verify) {
    return dsa->meth->verify(out_valid, digest, digest_len, sig, dsa);
  }

  return DSA_default_method.verify(out_valid, digest, digest_len, sig, dsa);
}

int DSA_sign(int type, const uint8_t *digest, size_t digest_len,
             uint8_t *out_sig, unsigned int *out_siglen, DSA *dsa) {
  DSA_SIG *s;

  s = DSA_do_sign(digest, digest_len, dsa);
  if (s == NULL) {
    *out_siglen = 0;
    return 0;
  }

  *out_siglen = i2d_DSA_SIG(s, &out_sig);
  DSA_SIG_free(s);
  return 1;
}

int DSA_verify(int type, const uint8_t *digest, size_t digest_len,
               const uint8_t *sig, size_t sig_len, const DSA *dsa) {
  DSA_SIG *s = NULL;
  int ret = -1, valid;

  s = DSA_SIG_new();
  if (s == NULL) {
    goto err;
  }

  if (d2i_DSA_SIG(&s, &sig, sig_len) == NULL) {
    goto err;
  }

  if (!DSA_do_check_signature(&valid, digest, digest_len, s, dsa)) {
    goto err;
  }

  ret = valid;

err:
  if (s) {
    DSA_SIG_free(s);
  }
  return ret;
}

int DSA_check_signature(int *out_valid, const uint8_t *digest,
                        size_t digest_len, const uint8_t *sig, size_t sig_len,
                        const DSA *dsa) {
  DSA_SIG *s = NULL;
  int ret = 0;

  s = DSA_SIG_new();
  if (s == NULL) {
    goto err;
  }

  if (d2i_DSA_SIG(&s, &sig, sig_len) == NULL) {
    goto err;
  }

  ret = DSA_do_check_signature(out_valid, digest, digest_len, s, dsa);

err:
  if (s) {
    DSA_SIG_free(s);
  }
  return ret;
}

int DSA_size(const DSA *dsa) {
  int ret, i;
  ASN1_INTEGER bs;
  unsigned char buf[4]; /* 4 bytes looks really small.
                           However, i2d_ASN1_INTEGER() will not look
                           beyond the first byte, as long as the second
                           parameter is NULL. */

  i = BN_num_bits(dsa->q);
  bs.length = (i + 7) / 8;
  bs.data = buf;
  bs.type = V_ASN1_INTEGER;
  /* If the top bit is set the asn1 encoding is 1 larger. */
  buf[0] = 0xff;

  i = i2d_ASN1_INTEGER(&bs, NULL);
  i += i; /* r and s */
  ret = ASN1_object_size(1, i, V_ASN1_SEQUENCE);
  return ret;
}

int DSA_sign_setup(const DSA *dsa, BN_CTX *ctx, BIGNUM **out_kinv,
                   BIGNUM **out_r) {
  if (dsa->meth->sign_setup) {
    return dsa->meth->sign_setup(dsa, ctx, out_kinv, out_r, NULL, 0);
  }

  return DSA_default_method.sign_setup(dsa, ctx, out_kinv, out_r, NULL, 0);
}

int DSA_get_ex_new_index(long argl, void *argp, CRYPTO_EX_new *new_func,
                         CRYPTO_EX_dup *dup_func, CRYPTO_EX_free *free_func) {
  return CRYPTO_get_ex_new_index(CRYPTO_EX_INDEX_DSA, argl, argp, new_func,
                                 dup_func, free_func);
}

int DSA_set_ex_data(DSA *d, int idx, void *arg) {
  return CRYPTO_set_ex_data(&d->ex_data, idx, arg);
}

void *DSA_get_ex_data(const DSA *d, int idx) {
  return CRYPTO_get_ex_data(&d->ex_data, idx);
}
