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

#ifndef OPENSSL_HEADER_DSA_H
#define OPENSSL_HEADER_DSA_H

#include <openssl/base.h>

#include <openssl/engine.h>
#include <openssl/ex_data.h>

#if defined(__cplusplus)
extern "C" {
#endif


/* DSA contains functions for signing and verifing with the Digital Signature
 * Algorithm. */


/* Allocation and destruction. */

/* DSA_new returns a new, empty DSA object or NULL on error. */
OPENSSL_EXPORT DSA *DSA_new(void);

/* DSA_new_method acts the same as |DH_new| but takes an explicit |ENGINE|. */
OPENSSL_EXPORT DSA *DSA_new_method(const ENGINE *engine);

/* DSA_free decrements the reference count of |dsa| and frees it if the
 * reference count drops to zero. */
OPENSSL_EXPORT void DSA_free(DSA *dsa);

/* DSA_up_ref increments the reference count of |dsa|. */
OPENSSL_EXPORT int DSA_up_ref(DSA *dsa);


/* Parameter generation. */

/* DSA_generate_parameters_ex generates a set of DSA parameters by following
 * the procedure given in FIPS 186-4, appendix A.
 * (http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-4.pdf)
 *
 * The larger prime will have a length of |bits| (e.g. 2048). The |seed| value
 * allows others to generate and verify the same parameters and should be
 * random input which is kept for reference. If |out_counter| or |out_h| are
 * not NULL then the counter and h value used in the generation are written to
 * them.
 *
 * The |cb| argument is passed to |BN_generate_prime_ex| and is thus called
 * during the generation process in order to indicate progress. See the
 * comments for that function for details. In addition to the calls made by
 * |BN_generate_prime_ex|, |DSA_generate_parameters_ex| will call it with
 * |event| equal to 2 and 3 at different stages of the process.
 *
 * It returns one on success and zero otherwise. */
OPENSSL_EXPORT int DSA_generate_parameters_ex(DSA *dsa, unsigned bits,
                                              const uint8_t *seed,
                                              size_t seed_len, int *out_counter,
                                              unsigned long *out_h,
                                              BN_GENCB *cb);

/* DSAparams_dup returns a freshly allocated |DSA| that contains a copy of the
 * parameters from |dsa|. It returns NULL on error. */
OPENSSL_EXPORT DSA *DSAparams_dup(const DSA *dsa);


/* Key generation. */

/* DSA_generate_key generates a public/private key pair in |dsa|, which must
 * already have parameters setup. It returns one on success and zero on
 * error. */
OPENSSL_EXPORT int DSA_generate_key(DSA *dsa);


/* Signatures. */

/* DSA_SIG contains a DSA signature as a pair of integers. */
typedef struct DSA_SIG_st {
  BIGNUM *r, *s;
} DSA_SIG;

/* DSA_SIG_new returns a freshly allocated, DIG_SIG structure or NULL on error.
 * Both |r| and |s| in the signature will be NULL. */
OPENSSL_EXPORT DSA_SIG *DSA_SIG_new(void);

/* DSA_SIG_free frees the contents of |sig| and then frees |sig| itself. */
OPENSSL_EXPORT void DSA_SIG_free(DSA_SIG *sig);

/* DSA_do_sign returns a signature of the hash in |digest| by the key in |dsa|
 * and returns an allocated, DSA_SIG structure, or NULL on error. */
OPENSSL_EXPORT DSA_SIG *DSA_do_sign(const uint8_t *digest, size_t digest_len,
                                    DSA *dsa);

/* DSA_do_verify verifies that |sig| is a valid signature, by the public key in
 * |dsa|, of the hash in |digest|. It returns one if so, zero if invalid and -1
 * on error.
 *
 * WARNING: do not use. This function returns -1 for error, 0 for invalid and 1
 * for valid. However, this is dangerously different to the usual OpenSSL
 * convention and could be a disaster if a user did |if (DSA_do_verify(...))|.
 * Because of this, |DSA_check_signature| is a safer version of this.
 *
 * TODO(fork): deprecate. */
OPENSSL_EXPORT int DSA_do_verify(const uint8_t *digest, size_t digest_len,
                                 DSA_SIG *sig, const DSA *dsa);

/* DSA_check_signature sets |*out_valid| to zero. Then it verifies that |sig|
 * is a valid signature, by the public key in |dsa| of the hash in |digest|
 * and, if so, it sets |*out_valid| to one.
 *
 * It returns one if it was able to verify the signature as valid or invalid,
 * and zero on error. */
OPENSSL_EXPORT int DSA_do_check_signature(int *out_valid, const uint8_t *digest,
                                          size_t digest_len, DSA_SIG *sig,
                                          const DSA *dsa);


/* ASN.1 signatures.
 *
 * These functions also perform DSA signature operations, but deal with ASN.1
 * encoded signatures as opposed to raw |BIGNUM|s. If you don't know what
 * encoding a DSA signature is in, it's probably ASN.1. */

/* DSA_sign signs |digest| with the key in |dsa| and writes the resulting
 * signature, in ASN.1 form, to |out_sig| and the length of the signature to
 * |*out_siglen|. There must be, at least, |DSA_size(dsa)| bytes of space in
 * |out_sig|. It returns one on success and zero otherwise.
 *
 * (The |type| argument is ignored.) */
OPENSSL_EXPORT int DSA_sign(int type, const uint8_t *digest, size_t digest_len,
                            uint8_t *out_sig, unsigned int *out_siglen,
                            DSA *dsa);

/* DSA_verify verifies that |sig| is a valid, ASN.1 signature, by the public
 * key in |dsa|, of the hash in |digest|. It returns one if so, zero if invalid
 * and -1 on error.
 *
 * (The |type| argument is ignored.)
 *
 * WARNING: do not use. This function returns -1 for error, 0 for invalid and 1
 * for valid. However, this is dangerously different to the usual OpenSSL
 * convention and could be a disaster if a user did |if (DSA_do_verify(...))|.
 * Because of this, |DSA_check_signature| is a safer version of this.
 *
 * TODO(fork): deprecate. */
OPENSSL_EXPORT int DSA_verify(int type, const uint8_t *digest,
                              size_t digest_len, const uint8_t *sig,
                              size_t sig_len, const DSA *dsa);

/* DSA_check_signature sets |*out_valid| to zero. Then it verifies that |sig|
 * is a valid, ASN.1 signature, by the public key in |dsa|, of the hash in
 * |digest|. If so, it sets |*out_valid| to one.
 *
 * It returns one if it was able to verify the signature as valid or invalid,
 * and zero on error. */
OPENSSL_EXPORT int DSA_check_signature(int *out_valid, const uint8_t *digest,
                                       size_t digest_len, const uint8_t *sig,
                                       size_t sig_len, const DSA *dsa);

/* DSA_size returns the size, in bytes, of an ASN.1 encoded, DSA signature
 * generated by |dsa|. Parameters must already have been setup in |dsa|. */
OPENSSL_EXPORT int DSA_size(const DSA *dsa);


/* ASN.1 encoding. */

/* d2i_DSA_SIG parses an ASN.1, DER-encoded, DSA signature from |len| bytes at
 * |*inp|. If |out_sig| is not NULL then, on exit, a pointer to the result is
 * in |*out_sig|. If |*out_sig| is already non-NULL on entry then the result is
 * written directly into |*out_sig|, otherwise a fresh |DSA_SIG| is allocated.
 * On successful exit, |*inp| is advanced past the DER structure. It returns
 * the result or NULL on error. */
OPENSSL_EXPORT DSA_SIG *d2i_DSA_SIG(DSA_SIG **out_sig, const uint8_t **inp,
                                    long len);

/* i2d_DSA_SIG marshals |in| to an ASN.1, DER structure. If |outp| is not NULL
 * then the result is written to |*outp| and |*outp| is advanced just past the
 * output. It returns the number of bytes in the result, whether written or not,
 * or a negative value on error. */
OPENSSL_EXPORT int i2d_DSA_SIG(const DSA_SIG *in, uint8_t **outp);

/* d2i_DSAPublicKey parses an ASN.1, DER-encoded, DSA public key from |len|
 * bytes at |*inp|. If |out| is not NULL then, on exit, a pointer to the result
 * is in |*out|. If |*out| is already non-NULL on entry then the result is
 * written directly into |*out|, otherwise a fresh |DSA| is allocated. On
 * successful exit, |*inp| is advanced past the DER structure. It returns the
 * result or NULL on error. */
OPENSSL_EXPORT DSA *d2i_DSAPublicKey(DSA **out, const uint8_t **inp, long len);

/* i2d_DSAPublicKey marshals a public key from |in| to an ASN.1, DER structure.
 * If |outp| is not NULL then the result is written to |*outp| and |*outp| is
 * advanced just past the output. It returns the number of bytes in the result,
 * whether written or not, or a negative value on error. */
OPENSSL_EXPORT int i2d_DSAPublicKey(const DSA *in, unsigned char **outp);

/* d2i_DSAPrivateKey parses an ASN.1, DER-encoded, DSA private key from |len|
 * bytes at |*inp|. If |out| is not NULL then, on exit, a pointer to the result
 * is in |*out|. If |*out| is already non-NULL on entry then the result is
 * written directly into |*out|, otherwise a fresh |DSA| is allocated. On
 * successful exit, |*inp| is advanced past the DER structure. It returns the
 * result or NULL on error. */
OPENSSL_EXPORT DSA *d2i_DSAPrivateKey(DSA **out, const uint8_t **inp, long len);

/* i2d_DSAPrivateKey marshals a private key from |in| to an ASN.1, DER structure.
 * If |outp| is not NULL then the result is written to |*outp| and |*outp| is
 * advanced just past the output. It returns the number of bytes in the result,
 * whether written or not, or a negative value on error. */
OPENSSL_EXPORT int i2d_DSAPrivateKey(const DSA *in, unsigned char **outp);

/* d2i_DSAparams parses ASN.1, DER-encoded, DSA parameters from |len| bytes at
 * |*inp|. If |out| is not NULL then, on exit, a pointer to the result is in
 * |*out|. If |*out| is already non-NULL on entry then the result is written
 * directly into |*out|, otherwise a fresh |DSA| is allocated. On successful
 * exit, |*inp| is advanced past the DER structure. It returns the result or
 * NULL on error. */
OPENSSL_EXPORT DSA *d2i_DSAparams(DSA **out, const uint8_t **inp, long len);

/* i2d_DSAparams marshals DSA parameters from |in| to an ASN.1, DER structure.
 * If |outp| is not NULL then the result is written to |*outp| and |*outp| is
 * advanced just past the output. It returns the number of bytes in the result,
 * whether written or not, or a negative value on error. */
OPENSSL_EXPORT int i2d_DSAparams(const DSA *in, unsigned char **outp);


/* Precomputation. */

/* DSA_sign_setup precomputes the message independent part of the DSA signature
 * and writes them to |*out_kinv| and |*out_r|. Returns one on success, zero on
 * error.
 *
 * TODO(fork): decide what to do with this. Since making DSA* opaque there's no
 * way for the user to install them. Also, it forces the DSA* not to be const
 * when passing to the signing function. */
OPENSSL_EXPORT int DSA_sign_setup(const DSA *dsa, BN_CTX *ctx,
                                  BIGNUM **out_kinv, BIGNUM **out_r);


/* ex_data functions.
 *
 * These functions are wrappers. See |ex_data.h| for details. */

OPENSSL_EXPORT int DSA_get_ex_new_index(long argl, void *argp,
                                        CRYPTO_EX_new *new_func,
                                        CRYPTO_EX_dup *dup_func,
                                        CRYPTO_EX_free *free_func);
OPENSSL_EXPORT int DSA_set_ex_data(DSA *d, int idx, void *arg);
OPENSSL_EXPORT void *DSA_get_ex_data(const DSA *d, int idx);


struct dsa_method {
  struct openssl_method_common_st common;

  void *app_data;

  int (*init)(DSA *dsa);
  int (*finish)(DSA *dsa);

  DSA_SIG *(*sign)(const uint8_t *digest, size_t digest_len, DSA *dsa);

  int (*sign_setup)(const DSA *dsa, BN_CTX *ctx_in, BIGNUM **kinvp, BIGNUM **rp,
                    const uint8_t *digest, size_t digest_len);

  int (*verify)(int *out_valid, const uint8_t *digest, size_t digest_len,
                DSA_SIG *sig, const DSA *dsa);

  /* generate_parameters, if non-NULL, is used to generate DSA parameters. */
  int (*generate_parameters)(DSA *dsa, unsigned bits, const uint8_t *seed,
                             size_t seed_len, int *counter_ret,
                             unsigned long *h_ret, BN_GENCB *cb);

  /* keygen, if non-NULL, is used to generate DSA keys. */
  int (*keygen)(DSA *dsa);
};

struct dsa_st {
  long version;
  int write_params;
  BIGNUM *p;
  BIGNUM *q; /* == 20 */
  BIGNUM *g;

  BIGNUM *pub_key;  /* y public key */
  BIGNUM *priv_key; /* x private key */

  BIGNUM *kinv; /* Signing pre-calc */
  BIGNUM *r;    /* Signing pre-calc */

  int flags;
  /* Normally used to cache montgomery values */
  BN_MONT_CTX *method_mont_p;
  int references;
  CRYPTO_EX_DATA ex_data;
  DSA_METHOD *meth;
  /* functional reference if 'meth' is ENGINE-provided */
  ENGINE *engine;
};


#if defined(__cplusplus)
}  /* extern C */
#endif

#define DSA_F_sign 100
#define DSA_F_verify 101
#define DSA_F_dsa_sig_cb 102
#define DSA_F_DSA_new_method 103
#define DSA_F_sign_setup 104
#define DSA_R_NEED_NEW_SETUP_VALUES 100
#define DSA_R_BAD_Q_VALUE 101
#define DSA_R_MODULUS_TOO_LARGE 102
#define DSA_R_MISSING_PARAMETERS 103

#endif  /* OPENSSL_HEADER_DSA_H */
