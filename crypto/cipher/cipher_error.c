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

#include <openssl/err.h>

#include <openssl/cipher.h>

const ERR_STRING_DATA CIPHER_error_string_data[] = {
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_EVP_AEAD_CTX_init, 0), "EVP_AEAD_CTX_init"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_EVP_AEAD_CTX_open, 0), "EVP_AEAD_CTX_open"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_EVP_AEAD_CTX_seal, 0), "EVP_AEAD_CTX_seal"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_EVP_CIPHER_CTX_copy, 0), "EVP_CIPHER_CTX_copy"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_EVP_CIPHER_CTX_ctrl, 0), "EVP_CIPHER_CTX_ctrl"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_EVP_CipherInit_ex, 0), "EVP_CipherInit_ex"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_EVP_DecryptFinal_ex, 0), "EVP_DecryptFinal_ex"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_EVP_EncryptFinal_ex, 0), "EVP_EncryptFinal_ex"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_aes_gcm_init, 0), "aead_aes_gcm_init"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_aes_gcm_open, 0), "aead_aes_gcm_open"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_aes_gcm_seal, 0), "aead_aes_gcm_seal"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_aes_key_wrap_init, 0), "aead_aes_key_wrap_init"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_aes_key_wrap_open, 0), "aead_aes_key_wrap_open"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_aes_key_wrap_seal, 0), "aead_aes_key_wrap_seal"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_chacha20_poly1305_init, 0), "aead_chacha20_poly1305_init"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_chacha20_poly1305_open, 0), "aead_chacha20_poly1305_open"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_chacha20_poly1305_seal, 0), "aead_chacha20_poly1305_seal"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_rc4_md5_tls_init, 0), "aead_rc4_md5_tls_init"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_rc4_md5_tls_open, 0), "aead_rc4_md5_tls_open"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aead_rc4_md5_tls_seal, 0), "aead_rc4_md5_tls_seal"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aes_init_key, 0), "aes_init_key"},
  {ERR_PACK(ERR_LIB_CIPHER, CIPHER_F_aesni_init_key, 0), "aesni_init_key"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_AES_KEY_SETUP_FAILED), "AES_KEY_SETUP_FAILED"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_BAD_DECRYPT), "BAD_DECRYPT"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_BAD_KEY_LENGTH), "BAD_KEY_LENGTH"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_BUFFER_TOO_SMALL), "BUFFER_TOO_SMALL"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_CTRL_NOT_IMPLEMENTED), "CTRL_NOT_IMPLEMENTED"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_CTRL_OPERATION_NOT_IMPLEMENTED), "CTRL_OPERATION_NOT_IMPLEMENTED"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH), "DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_INITIALIZATION_ERROR), "INITIALIZATION_ERROR"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_INPUT_NOT_INITIALIZED), "INPUT_NOT_INITIALIZED"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_INVALID_AD), "INVALID_AD"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_INVALID_AD_SIZE), "INVALID_AD_SIZE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_IV_TOO_LARGE), "IV_TOO_LARGE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_NO_CIPHER_SET), "NO_CIPHER_SET"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_OUTPUT_ALIASES_INPUT), "OUTPUT_ALIASES_INPUT"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_TAG_TOO_LARGE), "TAG_TOO_LARGE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_TOO_LARGE), "TOO_LARGE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_UNSUPPORTED_AD_SIZE), "UNSUPPORTED_AD_SIZE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_UNSUPPORTED_INPUT_SIZE), "UNSUPPORTED_INPUT_SIZE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_UNSUPPORTED_KEY_SIZE), "UNSUPPORTED_KEY_SIZE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_UNSUPPORTED_NONCE_SIZE), "UNSUPPORTED_NONCE_SIZE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_UNSUPPORTED_TAG_SIZE), "UNSUPPORTED_TAG_SIZE"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_WRAP_MODE_NOT_ALLOWED), "WRAP_MODE_NOT_ALLOWED"},
  {ERR_PACK(ERR_LIB_CIPHER, 0, CIPHER_R_WRONG_FINAL_BLOCK_LENGTH), "WRONG_FINAL_BLOCK_LENGTH"},
  {0, NULL},
};
