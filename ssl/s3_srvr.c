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
 * Copyright (c) 1998-2007 The OpenSSL Project.  All rights reserved.
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
 * Hudson (tjh@cryptsoft.com).
 *
 */
/* ====================================================================
 * Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 *
 * Portions of the attached software ("Contribution") are developed by 
 * SUN MICROSYSTEMS, INC., and are contributed to the OpenSSL project.
 *
 * The Contribution is licensed pursuant to the OpenSSL open source
 * license provided above.
 *
 * ECC cipher suite support in OpenSSL originally written by
 * Vipul Gupta and Sumit Gupta of Sun Microsystems Laboratories.
 *
 */
/* ====================================================================
 * Copyright 2005 Nokia. All rights reserved.
 *
 * The portions of the attached software ("Contribution") is developed by
 * Nokia Corporation and is licensed pursuant to the OpenSSL open source
 * license.
 *
 * The Contribution, originally written by Mika Kousa and Pasi Eronen of
 * Nokia Corporation, consists of the "PSK" (Pre-Shared Key) ciphersuites
 * support (see RFC 4279) to OpenSSL.
 *
 * No patent licenses or other rights except those expressly stated in
 * the OpenSSL open source license shall be deemed granted or received
 * expressly, by implication, estoppel, or otherwise.
 *
 * No assurances are provided by Nokia that the Contribution does not
 * infringe the patent or other intellectual property rights of any third
 * party or that the license provides you with all the necessary rights
 * to make use of the Contribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. IN
 * ADDITION TO THE DISCLAIMERS INCLUDED IN THE LICENSE, NOKIA
 * SPECIFICALLY DISCLAIMS ANY LIABILITY FOR CLAIMS BROUGHT BY YOU OR ANY
 * OTHER ENTITY BASED ON INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS OR
 * OTHERWISE. */

#define NETSCAPE_HANG_BUG

#include <stdio.h>
#include <string.h>

#include <openssl/bn.h>
#include <openssl/buf.h>
#include <openssl/bytestring.h>
#include <openssl/cipher.h>
#include <openssl/dh.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <openssl/mem.h>
#include <openssl/obj.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/x509.h>

#include "ssl_locl.h"
#include "../crypto/dh/internal.h"

static const SSL_METHOD *ssl3_get_server_method(int ver);

static const SSL_METHOD *ssl3_get_server_method(int ver)
	{
	if (ver == SSL3_VERSION)
		return(SSLv3_server_method());
	else
		return(NULL);
	}

IMPLEMENT_ssl3_meth_func(SSLv3_server_method,
			ssl3_accept,
			ssl_undefined_function,
			ssl3_get_server_method)

int ssl3_accept(SSL *s)
	{
	BUF_MEM *buf;
	unsigned long alg_a;
	void (*cb)(const SSL *ssl,int type,int val)=NULL;
	int ret= -1;
	int new_state,state,skip=0;

	ERR_clear_error();
	ERR_clear_system_error();

	if (s->info_callback != NULL)
		cb=s->info_callback;
	else if (s->ctx->info_callback != NULL)
		cb=s->ctx->info_callback;

	/* init things to blank */
	s->in_handshake++;
	if (!SSL_in_init(s) || SSL_in_before(s)) SSL_clear(s);

	if (s->cert == NULL)
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_accept, SSL_R_NO_CERTIFICATE_SET);
		return(-1);
		}

	for (;;)
		{
		state=s->state;

		switch (s->state)
			{
		case SSL_ST_RENEGOTIATE:
			s->renegotiate=1;
			/* s->state=SSL_ST_ACCEPT; */

		case SSL_ST_BEFORE:
		case SSL_ST_ACCEPT:
		case SSL_ST_BEFORE|SSL_ST_ACCEPT:
		case SSL_ST_OK|SSL_ST_ACCEPT:

			s->server=1;
			if (cb != NULL) cb(s,SSL_CB_HANDSHAKE_START,1);

			if ((s->version>>8) != 3)
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_accept, ERR_R_INTERNAL_ERROR);
				return -1;
				}
			s->type=SSL_ST_ACCEPT;

			if (s->init_buf == NULL)
				{
				if ((buf=BUF_MEM_new()) == NULL)
					{
					ret= -1;
					goto end;
					}
				if (!BUF_MEM_grow(buf,SSL3_RT_MAX_PLAIN_LENGTH))
					{
					ret= -1;
					goto end;
					}
				s->init_buf=buf;
				}

			if (!ssl3_setup_buffers(s))
				{
				ret= -1;
				goto end;
				}

			s->init_num=0;

			if (s->state != SSL_ST_RENEGOTIATE)
				{
				/* Ok, we now need to push on a buffering BIO so that
				 * the output is sent in a way that TCP likes :-)
				 */
				if (!ssl_init_wbio_buffer(s,1)) { ret= -1; goto end; }
				
				ssl3_init_finished_mac(s);
				s->state=SSL3_ST_SR_CLNT_HELLO_A;
				s->ctx->stats.sess_accept++;
				}
			else if (!s->s3->send_connection_binding &&
				!(s->options & SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION))
				{
				/* Server attempting to renegotiate with
				 * client that doesn't support secure
				 * renegotiation.
				 */
				OPENSSL_PUT_ERROR(SSL, ssl3_accept, SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED);
				ssl3_send_alert(s,SSL3_AL_FATAL,SSL_AD_HANDSHAKE_FAILURE);
				ret = -1;
				goto end;
				}
			else
				{
				/* s->state == SSL_ST_RENEGOTIATE,
				 * we will just send a HelloRequest */
				s->ctx->stats.sess_accept_renegotiate++;
				s->state=SSL3_ST_SW_HELLO_REQ_A;
				}
			break;

		case SSL3_ST_SW_HELLO_REQ_A:
		case SSL3_ST_SW_HELLO_REQ_B:

			s->shutdown=0;
			ret=ssl3_send_hello_request(s);
			if (ret <= 0) goto end;
			s->s3->tmp.next_state=SSL3_ST_SW_HELLO_REQ_C;
			s->state=SSL3_ST_SW_FLUSH;
			s->init_num=0;

			ssl3_init_finished_mac(s);
			break;

		case SSL3_ST_SW_HELLO_REQ_C:
			s->state=SSL_ST_OK;
			break;

		case SSL3_ST_SR_CLNT_HELLO_A:
		case SSL3_ST_SR_CLNT_HELLO_B:
		case SSL3_ST_SR_CLNT_HELLO_C:
		case SSL3_ST_SR_CLNT_HELLO_D:
			s->shutdown=0;
			ret=ssl3_get_client_hello(s);
			if (ret == PENDING_SESSION) {
				s->rwstate = SSL_PENDING_SESSION;
				goto end;
			}
			if (ret == CERTIFICATE_SELECTION_PENDING)
				{
				s->rwstate = SSL_CERTIFICATE_SELECTION_PENDING;
				goto end;
				}
			if (ret <= 0) goto end;
			s->renegotiate = 2;
			s->state=SSL3_ST_SW_SRVR_HELLO_A;
			s->init_num=0;
			break;

		case SSL3_ST_SW_SRVR_HELLO_A:
		case SSL3_ST_SW_SRVR_HELLO_B:
			ret=ssl3_send_server_hello(s);
			if (ret <= 0) goto end;
			if (s->hit)
				{
				if (s->tlsext_ticket_expected)
					s->state=SSL3_ST_SW_SESSION_TICKET_A;
				else
					s->state=SSL3_ST_SW_CHANGE_A;
				}
			else
				s->state = SSL3_ST_SW_CERT_A;
			s->init_num = 0;
			break;

		case SSL3_ST_SW_CERT_A:
		case SSL3_ST_SW_CERT_B:
			if (ssl_cipher_has_server_public_key(s->s3->tmp.new_cipher))
				{
				ret=ssl3_send_server_certificate(s);
				if (ret <= 0) goto end;
				if (s->tlsext_status_expected)
					s->state=SSL3_ST_SW_CERT_STATUS_A;
				else
					s->state=SSL3_ST_SW_KEY_EXCH_A;
				}
			else
				{
				skip = 1;
				s->state=SSL3_ST_SW_KEY_EXCH_A;
				}
			s->init_num=0;
			break;

		case SSL3_ST_SW_KEY_EXCH_A:
		case SSL3_ST_SW_KEY_EXCH_B:
			alg_a = s->s3->tmp.new_cipher->algorithm_auth;

			/* Send a ServerKeyExchange message if:
			 * - The key exchange is ephemeral or anonymous
			 *   Diffie-Hellman.
			 * - There is a PSK identity hint.
			 *
			 * TODO(davidben): This logic is currently duplicated
			 * in d1_srvr.c. Fix this. In the meantime, keep them
			 * in sync.
			 */
			if (ssl_cipher_requires_server_key_exchange(s->s3->tmp.new_cipher) ||
			    ((alg_a & SSL_aPSK) && s->session->psk_identity_hint))
				{
				ret=ssl3_send_server_key_exchange(s);
				if (ret <= 0) goto end;
				}
			else
				skip=1;

			s->state=SSL3_ST_SW_CERT_REQ_A;
			s->init_num=0;
			break;

		case SSL3_ST_SW_CERT_REQ_A:
		case SSL3_ST_SW_CERT_REQ_B:
			if (/* don't request cert unless asked for it: */
				!(s->verify_mode & SSL_VERIFY_PEER) ||
				/* Don't request a certificate if an obc was presented */
				((s->verify_mode & SSL_VERIFY_PEER_IF_NO_OBC) &&
				 s->s3->tlsext_channel_id_valid) ||
				/* if SSL_VERIFY_CLIENT_ONCE is set,
				 * don't request cert during re-negotiation: */
				((s->session->peer != NULL) &&
				 (s->verify_mode & SSL_VERIFY_CLIENT_ONCE)) ||
				/* never request cert in anonymous ciphersuites
				 * (see section "Certificate request" in SSL 3 drafts
				 * and in RFC 2246): */
				((s->s3->tmp.new_cipher->algorithm_auth & SSL_aNULL) &&
				 /* ... except when the application insists on verification
				  * (against the specs, but s3_clnt.c accepts this for SSL 3) */
				 !(s->verify_mode & SSL_VERIFY_FAIL_IF_NO_PEER_CERT)) ||
				/* With normal PSK Certificates and
				 * Certificate Requests are omitted */
				(s->s3->tmp.new_cipher->algorithm_mkey & SSL_kPSK))
				{
				/* no cert request */
				skip=1;
				s->s3->tmp.cert_request=0;
				s->state=SSL3_ST_SW_SRVR_DONE_A;
				if (s->s3->handshake_buffer)
					if (!ssl3_digest_cached_records(s))
						return -1;
				}
			else
				{
				s->s3->tmp.cert_request=1;
				ret=ssl3_send_certificate_request(s);
				if (ret <= 0) goto end;
#ifndef NETSCAPE_HANG_BUG
				s->state=SSL3_ST_SW_SRVR_DONE_A;
#else
				s->state=SSL3_ST_SW_FLUSH;
				s->s3->tmp.next_state=SSL3_ST_SR_CERT_A;
#endif
				s->init_num=0;
				}
			break;

		case SSL3_ST_SW_SRVR_DONE_A:
		case SSL3_ST_SW_SRVR_DONE_B:
			ret=ssl3_send_server_done(s);
			if (ret <= 0) goto end;
			s->s3->tmp.next_state=SSL3_ST_SR_CERT_A;
			s->state=SSL3_ST_SW_FLUSH;
			s->init_num=0;
			break;
		
		case SSL3_ST_SW_FLUSH:

			/* This code originally checked to see if
			 * any data was pending using BIO_CTRL_INFO
			 * and then flushed. This caused problems
			 * as documented in PR#1939. The proposed
			 * fix doesn't completely resolve this issue
			 * as buggy implementations of BIO_CTRL_PENDING
			 * still exist. So instead we just flush
			 * unconditionally.
			 */

			s->rwstate=SSL_WRITING;
			if (BIO_flush(s->wbio) <= 0)
				{
				ret= -1;
				goto end;
				}
			s->rwstate=SSL_NOTHING;

			s->state=s->s3->tmp.next_state;
			break;

		case SSL3_ST_SR_CERT_A:
		case SSL3_ST_SR_CERT_B:
			if (s->s3->tmp.cert_request)
				{
				ret=ssl3_get_client_certificate(s);
				if (ret <= 0) goto end;
				}
			s->init_num=0;
			s->state=SSL3_ST_SR_KEY_EXCH_A;
			break;

		case SSL3_ST_SR_KEY_EXCH_A:
		case SSL3_ST_SR_KEY_EXCH_B:
			ret=ssl3_get_client_key_exchange(s);
			if (ret <= 0)
				goto end;
			s->state=SSL3_ST_SR_CERT_VRFY_A;
			s->init_num=0;

			/* TODO(davidben): These two blocks are different
			 * between SSL and DTLS. Resolve the difference and code
			 * duplication. */
			if (SSL_USE_SIGALGS(s))
				{
				if (!s->session->peer)
					break;
				/* For sigalgs freeze the handshake buffer
				 * at this point and digest cached records.
				 */
				if (!s->s3->handshake_buffer)
					{
					OPENSSL_PUT_ERROR(SSL, ssl3_accept, ERR_R_INTERNAL_ERROR);
					return -1;
					}
				s->s3->flags |= TLS1_FLAGS_KEEP_HANDSHAKE;
				if (!ssl3_digest_cached_records(s))
					return -1;
				}
			else
				{
				int offset=0;
				int dgst_num;

				/* We need to get hashes here so if there is
				 * a client cert, it can be verified
				 * FIXME - digest processing for CertificateVerify
				 * should be generalized. But it is next step
				 */
				if (s->s3->handshake_buffer)
					if (!ssl3_digest_cached_records(s))
						return -1;
				for (dgst_num=0; dgst_num<SSL_MAX_DIGEST;dgst_num++)	
					if (s->s3->handshake_dgst[dgst_num]) 
						{
						int dgst_size;

						s->method->ssl3_enc->cert_verify_mac(s,EVP_MD_CTX_type(s->s3->handshake_dgst[dgst_num]),&(s->s3->tmp.cert_verify_md[offset]));
						dgst_size=EVP_MD_CTX_size(s->s3->handshake_dgst[dgst_num]);
						if (dgst_size < 0)
							{
							ret = -1;
							goto end;
							}
						offset+=dgst_size;
						}		
				}
			break;

		case SSL3_ST_SR_CERT_VRFY_A:
		case SSL3_ST_SR_CERT_VRFY_B:
			ret=ssl3_get_cert_verify(s);
			if (ret <= 0) goto end;

			s->state = SSL3_ST_SR_CHANGE;
			s->init_num=0;
			break;

		case SSL3_ST_SR_CHANGE: {
			char next_proto_neg = 0;
			char channel_id = 0;
# if !defined(OPENSSL_NO_NEXTPROTONEG)
			next_proto_neg = s->s3->next_proto_neg_seen;
# endif
			channel_id = s->s3->tlsext_channel_id_valid;

			/* At this point, the next message must be entirely
			 * behind a ChangeCipherSpec. */
			if (!ssl3_expect_change_cipher_spec(s))
				{
				ret = -1;
				goto end;
				}
			if (next_proto_neg)
				s->state = SSL3_ST_SR_NEXT_PROTO_A;
			else if (channel_id)
				s->state = SSL3_ST_SR_CHANNEL_ID_A;
			else
				s->state = SSL3_ST_SR_FINISHED_A;
			break;
		}

#if !defined(OPENSSL_NO_NEXTPROTONEG)
		case SSL3_ST_SR_NEXT_PROTO_A:
		case SSL3_ST_SR_NEXT_PROTO_B:
			ret=ssl3_get_next_proto(s);
			if (ret <= 0) goto end;
			s->init_num = 0;
			if (s->s3->tlsext_channel_id_valid)
				s->state=SSL3_ST_SR_CHANNEL_ID_A;
			else
				s->state=SSL3_ST_SR_FINISHED_A;
			break;
#endif

		case SSL3_ST_SR_CHANNEL_ID_A:
		case SSL3_ST_SR_CHANNEL_ID_B:
			ret=ssl3_get_channel_id(s);
			if (ret <= 0) goto end;
			s->init_num = 0;
			s->state=SSL3_ST_SR_FINISHED_A;
			break;

		case SSL3_ST_SR_FINISHED_A:
		case SSL3_ST_SR_FINISHED_B:
			ret=ssl3_get_finished(s,SSL3_ST_SR_FINISHED_A,
				SSL3_ST_SR_FINISHED_B);
			if (ret <= 0) goto end;
			if (s->hit)
				s->state=SSL_ST_OK;
			else if (s->tlsext_ticket_expected)
				s->state=SSL3_ST_SW_SESSION_TICKET_A;
			else
				s->state=SSL3_ST_SW_CHANGE_A;
			/* If this is a full handshake with ChannelID then
			 * record the hashshake hashes in |s->session| in case
			 * we need them to verify a ChannelID signature on a
			 * resumption of this session in the future. */
			if (!s->hit && s->s3->tlsext_channel_id_new)
				{
				ret = tls1_record_handshake_hashes_for_channel_id(s);
				if (ret <= 0) goto end;
				}
			s->init_num=0;
			break;

		case SSL3_ST_SW_SESSION_TICKET_A:
		case SSL3_ST_SW_SESSION_TICKET_B:
			ret=ssl3_send_newsession_ticket(s);
			if (ret <= 0) goto end;
			s->state=SSL3_ST_SW_CHANGE_A;
			s->init_num=0;
			break;

		case SSL3_ST_SW_CERT_STATUS_A:
		case SSL3_ST_SW_CERT_STATUS_B:
			ret=ssl3_send_cert_status(s);
			if (ret <= 0) goto end;
			s->state=SSL3_ST_SW_KEY_EXCH_A;
			s->init_num=0;
			break;

		case SSL3_ST_SW_CHANGE_A:
		case SSL3_ST_SW_CHANGE_B:

			s->session->cipher=s->s3->tmp.new_cipher;
			if (!s->method->ssl3_enc->setup_key_block(s))
				{ ret= -1; goto end; }

			ret=ssl3_send_change_cipher_spec(s,
				SSL3_ST_SW_CHANGE_A,SSL3_ST_SW_CHANGE_B);

			if (ret <= 0) goto end;
			s->state=SSL3_ST_SW_FINISHED_A;
			s->init_num=0;

			if (!s->method->ssl3_enc->change_cipher_state(s,
				SSL3_CHANGE_CIPHER_SERVER_WRITE))
				{
				ret= -1;
				goto end;
				}

			break;

		case SSL3_ST_SW_FINISHED_A:
		case SSL3_ST_SW_FINISHED_B:
			ret=ssl3_send_finished(s,
				SSL3_ST_SW_FINISHED_A,SSL3_ST_SW_FINISHED_B,
				s->method->ssl3_enc->server_finished_label,
				s->method->ssl3_enc->server_finished_label_len);
			if (ret <= 0) goto end;
			s->state = SSL3_ST_SW_FLUSH;
			if (s->hit)
				s->s3->tmp.next_state = SSL3_ST_SR_CHANGE;
			else
				s->s3->tmp.next_state = SSL_ST_OK;
			s->init_num=0;
			break;

		case SSL_ST_OK:
			/* clean a few things up */
			ssl3_cleanup_key_block(s);

			BUF_MEM_free(s->init_buf);
			s->init_buf=NULL;

			/* remove buffering on output */
			ssl_free_wbio_buffer(s);

			s->init_num=0;

			/* If we aren't retaining peer certificates then we can
			 * discard it now. */
			if (s->session->peer && s->ctx->retain_only_sha256_of_client_certs)
				{
				X509_free(s->session->peer);
				s->session->peer = NULL;
				}

			if (s->renegotiate == 2) /* skipped if we just sent a HelloRequest */
				{
				s->renegotiate=0;
				s->new_session=0;
				
				ssl_update_cache(s,SSL_SESS_CACHE_SERVER);
				
				s->ctx->stats.sess_accept_good++;
				/* s->server=1; */
				s->handshake_func=ssl3_accept;

				if (cb != NULL) cb(s,SSL_CB_HANDSHAKE_DONE,1);
				}
			
			ret = 1;
			goto end;
			/* break; */

		default:
			OPENSSL_PUT_ERROR(SSL, ssl3_accept, SSL_R_UNKNOWN_STATE);
			ret= -1;
			goto end;
			/* break; */
			}
		
		if (!s->s3->tmp.reuse_message && !skip)
			{
			if (s->debug)
				{
				if ((ret=BIO_flush(s->wbio)) <= 0)
					goto end;
				}


			if ((cb != NULL) && (s->state != state))
				{
				new_state=s->state;
				s->state=state;
				cb(s,SSL_CB_ACCEPT_LOOP,1);
				s->state=new_state;
				}
			}
		skip=0;
		}
end:
	/* BIO_flush(s->wbio); */

	s->in_handshake--;
	if (cb != NULL)
		cb(s,SSL_CB_ACCEPT_EXIT,ret);
	return(ret);
	}

int ssl3_send_hello_request(SSL *s)
	{

	if (s->state == SSL3_ST_SW_HELLO_REQ_A)
		{
		ssl_set_handshake_header(s, SSL3_MT_HELLO_REQUEST, 0);
		s->state=SSL3_ST_SW_HELLO_REQ_B;
		}

	/* SSL3_ST_SW_HELLO_REQ_B */
	return ssl_do_write(s);
	}

int ssl3_get_client_hello(SSL *s)
	{
	int i,ok,al=SSL_AD_INTERNAL_ERROR,ret= -1;
	long n;
	const SSL_CIPHER *c;
	STACK_OF(SSL_CIPHER) *ciphers=NULL;
	struct ssl_early_callback_ctx early_ctx;
	CBS client_hello;
	uint16_t client_version;
	CBS client_random, session_id, cipher_suites, compression_methods;

	/* We do this so that we will respond with our native type.
	 * If we are TLSv1 and we get SSLv3, we will respond with TLSv1,
	 * This down switching should be handled by a different method.
	 * If we are SSLv3, we will respond with SSLv3, even if prompted with
	 * TLSv1.
	 */
	switch (s->state) {
	case SSL3_ST_SR_CLNT_HELLO_A:
	case SSL3_ST_SR_CLNT_HELLO_B:
		s->first_packet=1;
		n=s->method->ssl_get_message(s,
			SSL3_ST_SR_CLNT_HELLO_A,
			SSL3_ST_SR_CLNT_HELLO_B,
			SSL3_MT_CLIENT_HELLO,
			SSL3_RT_MAX_PLAIN_LENGTH,
			&ok);

		if (!ok) return((int)n);
		s->first_packet=0;

		/* If we require cookies and this ClientHello doesn't
		 * contain one, just return since we do not want to
		 * allocate any memory yet. So check cookie length...
		 */
		if (SSL_IS_DTLS(s) && (SSL_get_options(s) & SSL_OP_COOKIE_EXCHANGE))
			{
			CBS session_id;
			uint8_t cookie_length;

			CBS_init(&client_hello, s->init_msg, n);
			if (!CBS_skip(&client_hello, 2 + SSL3_RANDOM_SIZE) ||
				!CBS_get_u8_length_prefixed(&client_hello, &session_id) ||
				!CBS_get_u8(&client_hello, &cookie_length))
				{
				al = SSL_AD_DECODE_ERROR;
				OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_DECODE_ERROR);
				goto f_err;
				}

			if (cookie_length == 0)
				return 1;
			}
		s->state = SSL3_ST_SR_CLNT_HELLO_C;
		/* fallthrough */
	case SSL3_ST_SR_CLNT_HELLO_C:
	case SSL3_ST_SR_CLNT_HELLO_D:
		/* We have previously parsed the ClientHello message,
		 * and can't call ssl_get_message again without hashing
		 * the message into the Finished digest again. */
		n = s->init_num;

		memset(&early_ctx, 0, sizeof(early_ctx));
		early_ctx.ssl = s;
		early_ctx.client_hello = s->init_msg;
		early_ctx.client_hello_len = n;
		if (!ssl_early_callback_init(&early_ctx))
			{
			al = SSL_AD_DECODE_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_CLIENTHELLO_PARSE_FAILED);
			goto f_err;
			}

		if (s->state == SSL3_ST_SR_CLNT_HELLO_C &&
		    s->ctx->select_certificate_cb != NULL)
			{
			int ret;

			s->state = SSL3_ST_SR_CLNT_HELLO_D;
			ret = s->ctx->select_certificate_cb(&early_ctx);
			if (ret == 0)
				return CERTIFICATE_SELECTION_PENDING;
			else if (ret == -1)
				{
				/* Connection rejected. */
				al = SSL_AD_ACCESS_DENIED;
				OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_CONNECTION_REJECTED);
				goto f_err;
				}
			}
		s->state = SSL3_ST_SR_CLNT_HELLO_D;
		break;
	default:
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_UNKNOWN_STATE);
		return -1;
	}

	CBS_init(&client_hello, s->init_msg, n);
	if (!CBS_get_u16(&client_hello, &client_version) ||
		!CBS_get_bytes(&client_hello, &client_random, SSL3_RANDOM_SIZE) ||
		!CBS_get_u8_length_prefixed(&client_hello, &session_id) ||
		CBS_len(&session_id) > SSL_MAX_SSL_SESSION_ID_LENGTH)
		{
		al = SSL_AD_DECODE_ERROR;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_DECODE_ERROR);
		goto f_err;
		}

	/* use version from inside client hello, not from record header
	 * (may differ: see RFC 2246, Appendix E, second paragraph) */
	s->client_version = client_version;

	if (SSL_IS_DTLS(s)  ?	(s->client_version > s->version &&
				 s->method->version != DTLS_ANY_VERSION)
			    :	(s->client_version < s->version))
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_WRONG_VERSION_NUMBER);
		if ((s->client_version>>8) == SSL3_VERSION_MAJOR &&
			!s->enc_write_ctx && !s->write_hash)
			{
			/* similar to ssl3_get_record, send alert using remote version number */
			s->version = s->client_version;
			}
		al = SSL_AD_PROTOCOL_VERSION;
		goto f_err;
		}

	/* Load the client random. */
	memcpy(s->s3->client_random, CBS_data(&client_random), SSL3_RANDOM_SIZE);

	s->hit=0;
	/* Versions before 0.9.7 always allow clients to resume sessions in renegotiation.
	 * 0.9.7 and later allow this by default, but optionally ignore resumption requests
	 * with flag SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION (it's a new flag rather
	 * than a change to default behavior so that applications relying on this for security
	 * won't even compile against older library versions).
	 *
	 * 1.0.1 and later also have a function SSL_renegotiate_abbreviated() to request
	 * renegotiation but not a new session (s->new_session remains unset): for servers,
	 * this essentially just means that the SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION
	 * setting will be ignored.
	 */
	if ((s->new_session && (s->options & SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION)))
		{
		if (!ssl_get_new_session(s,1))
			goto err;
		}
	else
		{
		i=ssl_get_prev_session(s, &early_ctx);
		if (i == 1)
			{ /* previous session */
			s->hit=1;
			}
		else if (i == -1)
			goto err;
		else if (i == PENDING_SESSION)
			{
			ret = PENDING_SESSION;
			goto err;
			}
		else /* i == 0 */
			{
			if (!ssl_get_new_session(s,1))
				goto err;
			}
		}

	if (SSL_IS_DTLS(s))
		{
		CBS cookie;

		/* TODO(davidben): The length check here is off. Per
		 * spec, the maximum cookie length is 32. However, the
		 * DTLS1_COOKIE_LENGTH check is checking against 256,
		 * not 32 (so it's actually redundant).
		 * 07a9d1a2c2b735cbc327065000b545deb5e136cf from
		 * OpenSSL switched this from 32 to 256. */
		if (!CBS_get_u8_length_prefixed(&client_hello, &cookie) ||
			CBS_len(&cookie) > DTLS1_COOKIE_LENGTH)
			{
			al = SSL_AD_DECODE_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_DECODE_ERROR);
			goto f_err;
			}

		/* Verify the cookie if appropriate option is set. */
		if ((SSL_get_options(s) & SSL_OP_COOKIE_EXCHANGE) &&
			CBS_len(&cookie) > 0)
			{
			if (s->ctx->app_verify_cookie_cb != NULL)
				{
				if (s->ctx->app_verify_cookie_cb(s,
						CBS_data(&cookie), CBS_len(&cookie)) == 0)
					{
					al=SSL_AD_HANDSHAKE_FAILURE;
					OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_COOKIE_MISMATCH);
					goto f_err;
					}
				/* else cookie verification succeeded */
				}
			else if (!CBS_mem_equal(&cookie, s->d1->cookie, s->d1->cookie_len))
				{
				/* default verification */
				al=SSL_AD_HANDSHAKE_FAILURE;
				OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_COOKIE_MISMATCH);
				goto f_err;
				}
			/* Set to -2 so if successful we return 2 and
			 * don't send HelloVerifyRequest. */
			ret = -2;
			}

		if (s->method->version == DTLS_ANY_VERSION)
			{
			/* Select version to use */
			if (s->client_version <= DTLS1_2_VERSION &&
				!(s->options & SSL_OP_NO_DTLSv1_2))
				{
				s->version = DTLS1_2_VERSION;
				s->method = DTLSv1_2_server_method();
				}
			else if (s->client_version <= DTLS1_VERSION &&
				!(s->options & SSL_OP_NO_DTLSv1))
				{
				s->version = DTLS1_VERSION;
				s->method = DTLSv1_server_method();
				}
			else
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_WRONG_VERSION_NUMBER);
				s->version = s->client_version;
				al = SSL_AD_PROTOCOL_VERSION;
				goto f_err;
				}
			s->session->ssl_version = s->version;
			}
		}

	if (!CBS_get_u16_length_prefixed(&client_hello, &cipher_suites) ||
		!CBS_get_u8_length_prefixed(&client_hello, &compression_methods) ||
		CBS_len(&compression_methods) == 0)
		{
		al = SSL_AD_DECODE_ERROR;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_DECODE_ERROR);
		goto f_err;
		}

	/* TODO(davidben): Per spec, cipher_suites can never be empty
	 * (specified at the ClientHello structure level). This logic
	 * allows it to be empty if resuming a session. Can we always
	 * require non-empty? If a client sends empty cipher_suites
	 * because it's resuming a session, it could always fail to
	 * resume a session, so it's unlikely to actually work. */
	if (CBS_len(&cipher_suites) == 0 && CBS_len(&session_id) != 0)
		{
		/* We need a cipher if we are not resuming a session. */
		al = SSL_AD_ILLEGAL_PARAMETER;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_NO_CIPHERS_SPECIFIED);
		goto f_err;
		}

	if (ssl_bytes_to_cipher_list(s, &cipher_suites, &ciphers) == NULL)
		{
		goto err;
		}

	/* If it is a hit, check that the cipher is in the list */
	if (s->hit && CBS_len(&cipher_suites) > 0)
		{
		int found_cipher = 0;
		unsigned long id = s->session->cipher->id;

		for (i=0; i<sk_SSL_CIPHER_num(ciphers); i++)
			{
			c=sk_SSL_CIPHER_value(ciphers,i);
			if (c->id == id)
				{
				found_cipher = 1;
				break;
				}
			}
		if (!found_cipher)
			{
			/* we need to have the cipher in the cipher
			 * list if we are asked to reuse it */
			al=SSL_AD_ILLEGAL_PARAMETER;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_REQUIRED_CIPHER_MISSING);
			goto f_err;
			}
		}

	/* Only null compression is supported. */
	if (memchr(CBS_data(&compression_methods), 0,
			CBS_len(&compression_methods)) == NULL)
		{
		al = SSL_AD_ILLEGAL_PARAMETER;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_NO_COMPRESSION_SPECIFIED);
		goto f_err;
		}

	/* TLS extensions*/
	if (s->version >= SSL3_VERSION)
		{
		if (!ssl_parse_clienthello_tlsext(s, &client_hello))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_PARSE_TLSEXT);
			goto err;
			}
		}

        /* There should be nothing left over in the record. */
	if (CBS_len(&client_hello) != 0)
		{
		/* wrong packet length */
		al=SSL_AD_DECODE_ERROR;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_BAD_PACKET_LENGTH);
		goto f_err;
		}

	/* Check if we want to use external pre-shared secret for this
	 * handshake for not reused session only. We need to generate
	 * server_random before calling tls_session_secret_cb in order to allow
	 * SessionTicket processing to use it in key derivation. */
	{
		unsigned char *pos;
		pos=s->s3->server_random;
		if (ssl_fill_hello_random(s, 1, pos, SSL3_RANDOM_SIZE) <= 0)
			{
			goto f_err;
			}
	}

	if (!s->hit && s->version >= TLS1_VERSION && s->tls_session_secret_cb)
		{
		const SSL_CIPHER *pref_cipher=NULL;

		s->session->master_key_length=sizeof(s->session->master_key);
		if(s->tls_session_secret_cb(s, s->session->master_key, &s->session->master_key_length,
			ciphers, &pref_cipher, s->tls_session_secret_cb_arg))
			{
			s->hit=1;
			s->session->ciphers=ciphers;
			s->session->verify_result=X509_V_OK;

			ciphers=NULL;

			/* check if some cipher was preferred by call back */
			pref_cipher=pref_cipher ? pref_cipher : ssl3_choose_cipher(s, s->session->ciphers, ssl_get_cipher_preferences(s));
			if (pref_cipher == NULL)
				{
				al=SSL_AD_HANDSHAKE_FAILURE;
				OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_NO_SHARED_CIPHER);
				goto f_err;
				}

			s->session->cipher=pref_cipher;

			if (s->cipher_list)
				ssl_cipher_preference_list_free(s->cipher_list);

			if (s->cipher_list_by_id)
				sk_SSL_CIPHER_free(s->cipher_list_by_id);

			s->cipher_list = ssl_cipher_preference_list_from_ciphers(s->session->ciphers);
			s->cipher_list_by_id = sk_SSL_CIPHER_dup(s->session->ciphers);
			}
		}

	/* Given s->session->ciphers and SSL_get_ciphers, we must
	 * pick a cipher */

	if (!s->hit)
		{
		if (s->session->ciphers != NULL)
			sk_SSL_CIPHER_free(s->session->ciphers);
		s->session->ciphers=ciphers;
		if (ciphers == NULL)
			{
			al=SSL_AD_ILLEGAL_PARAMETER;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_NO_CIPHERS_PASSED);
			goto f_err;
			}
		ciphers=NULL;
		/* Let cert callback update server certificates if required */
		if (s->cert->cert_cb)
			{
			int rv = s->cert->cert_cb(s, s->cert->cert_cb_arg);
			if (rv == 0)
				{
				al=SSL_AD_INTERNAL_ERROR;
				OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_CERT_CB_ERROR);
				goto f_err;
				}
			if (rv < 0)
				{
				s->rwstate=SSL_X509_LOOKUP;
				return -1;
				}
			s->rwstate = SSL_NOTHING;
			}
		c=ssl3_choose_cipher(s,s->session->ciphers,
				     ssl_get_cipher_preferences(s));

		if (c == NULL)
			{
			al=SSL_AD_HANDSHAKE_FAILURE;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_NO_SHARED_CIPHER);
			goto f_err;
			}
		s->s3->tmp.new_cipher=c;
		}
	else
		{
		/* Session-id reuse */
		s->s3->tmp.new_cipher=s->session->cipher;
		}

	if (!SSL_USE_SIGALGS(s) || !(s->verify_mode & SSL_VERIFY_PEER))
		{
		if (!ssl3_digest_cached_records(s))
			goto f_err;
		}
	
	/* we now have the following setup. 
	 * client_random
	 * cipher_list 		- our prefered list of ciphers
	 * ciphers 		- the clients prefered list of ciphers
	 * compression		- basically ignored right now
	 * ssl version is set	- sslv3
	 * s->session		- The ssl session has been setup.
	 * s->hit		- session reuse flag
	 * s->tmp.new_cipher	- the new cipher to use.
	 */

	/* Handles TLS extensions that we couldn't check earlier */
	if (s->version >= SSL3_VERSION)
		{
		if (ssl_check_clienthello_tlsext_late(s) <= 0)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_hello, SSL_R_CLIENTHELLO_TLSEXT);
			goto err;
			}
		}

	if (ret < 0) ret=-ret;
	if (0)
		{
f_err:
		ssl3_send_alert(s,SSL3_AL_FATAL,al);
		}
err:
	if (ciphers != NULL) sk_SSL_CIPHER_free(ciphers);
	return ret;
	}

int ssl3_send_server_hello(SSL *s)
	{
	unsigned char *buf;
	unsigned char *p,*d;
	int sl;
	unsigned long l;

	if (s->state == SSL3_ST_SW_SRVR_HELLO_A)
		{
		/* We only accept ChannelIDs on connections with ECDHE in order
		 * to avoid a known attack while we fix ChannelID itself. */
		if (s->s3 &&
		    s->s3->tlsext_channel_id_valid &&
		    (s->s3->tmp.new_cipher->algorithm_mkey & SSL_kEECDH) == 0)
			s->s3->tlsext_channel_id_valid = 0;

		/* If this is a resumption and the original handshake didn't
		 * support ChannelID then we didn't record the original
		 * handshake hashes in the session and so cannot resume with
		 * ChannelIDs. */
		if (s->hit &&
		    s->s3->tlsext_channel_id_new &&
		    s->session->original_handshake_hash_len == 0)
			s->s3->tlsext_channel_id_valid = 0;

		if (s->mode & SSL_MODE_RELEASE_BUFFERS)
			{
			/* Free s->session->ciphers in order to release memory. This
			 * breaks SSL_get_shared_ciphers(), but many servers will
			 * prefer the memory savings. */
			sk_SSL_CIPHER_free(s->session->ciphers);
			s->session->ciphers = NULL;
			}

		buf=(unsigned char *)s->init_buf->data;
		/* Do the message type and length last */
		d=p= ssl_handshake_start(s);

		*(p++)=s->version>>8;
		*(p++)=s->version&0xff;

		/* Random stuff */
		memcpy(p,s->s3->server_random,SSL3_RANDOM_SIZE);
		p+=SSL3_RANDOM_SIZE;

		/* There are several cases for the session ID to send
		 * back in the server hello:
		 * - For session reuse from the session cache,
		 *   we send back the old session ID.
		 * - If stateless session reuse (using a session ticket)
		 *   is successful, we send back the client's "session ID"
		 *   (which doesn't actually identify the session).
		 * - If it is a new session, we send back the new
		 *   session ID.
		 * - However, if we want the new session to be single-use,
		 *   we send back a 0-length session ID.
		 * s->hit is non-zero in either case of session reuse,
		 * so the following won't overwrite an ID that we're supposed
		 * to send back.
		 */
		if (!(s->ctx->session_cache_mode & SSL_SESS_CACHE_SERVER)
			&& !s->hit)
			s->session->session_id_length=0;

		sl=s->session->session_id_length;
		if (sl > (int)sizeof(s->session->session_id))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_send_server_hello, ERR_R_INTERNAL_ERROR);
			return -1;
			}
		*(p++)=sl;
		memcpy(p,s->session->session_id,sl);
		p+=sl;

		/* put the cipher */
                s2n(ssl3_get_cipher_value(s->s3->tmp.new_cipher), p);

		/* put the compression method */
			*(p++)=0;
		if (ssl_prepare_serverhello_tlsext(s) <= 0)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_send_server_hello, SSL_R_SERVERHELLO_TLSEXT);
			return -1;
			}
		if ((p = ssl_add_serverhello_tlsext(s, p, buf+SSL3_RT_MAX_PLAIN_LENGTH)) == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_send_server_hello, ERR_R_INTERNAL_ERROR);
			return -1;
			}
		/* do the header */
		l=(p-d);
		ssl_set_handshake_header(s, SSL3_MT_SERVER_HELLO, l);
		s->state=SSL3_ST_SW_SRVR_HELLO_B;
		}

	/* SSL3_ST_SW_SRVR_HELLO_B */
	return ssl_do_write(s);
	}

int ssl3_send_server_done(SSL *s)
	{

	if (s->state == SSL3_ST_SW_SRVR_DONE_A)
		{
		ssl_set_handshake_header(s, SSL3_MT_SERVER_DONE, 0);
		s->state = SSL3_ST_SW_SRVR_DONE_B;
		}

	/* SSL3_ST_SW_SRVR_DONE_B */
	return ssl_do_write(s);
	}

int ssl3_send_server_key_exchange(SSL *s)
	{
	unsigned char *q;
	int j,num;
	unsigned char md_buf[MD5_DIGEST_LENGTH+SHA_DIGEST_LENGTH];
	unsigned int u;
#ifndef OPENSSL_NO_DH
	DH *dh=NULL,*dhp;
#endif
#ifndef OPENSSL_NO_ECDH
	EC_KEY *ecdh=NULL, *ecdhp;
	unsigned char *encodedPoint = NULL;
	int encodedlen = 0;
	int curve_id = 0;
	BN_CTX *bn_ctx = NULL; 
#endif
	const char* psk_identity_hint = NULL;
	size_t psk_identity_hint_len = 0;
	EVP_PKEY *pkey;
	const EVP_MD *md = NULL;
	unsigned char *p,*d;
	int al,i;
	unsigned long alg_k;
	unsigned long alg_a;
	int n;
	CERT *cert;
	BIGNUM *r[4];
	int nr[4],kn;
	BUF_MEM *buf;
	EVP_MD_CTX md_ctx;

	EVP_MD_CTX_init(&md_ctx);
	if (s->state == SSL3_ST_SW_KEY_EXCH_A)
		{
		alg_k=s->s3->tmp.new_cipher->algorithm_mkey;
		alg_a=s->s3->tmp.new_cipher->algorithm_auth;
		cert=s->cert;

		buf=s->init_buf;

		r[0]=r[1]=r[2]=r[3]=NULL;
		n=0;
		if (alg_a & SSL_aPSK)
			{
			/* size for PSK identity hint */
			psk_identity_hint = s->session->psk_identity_hint;
			if (psk_identity_hint)
				psk_identity_hint_len = strlen(psk_identity_hint);
			else
				psk_identity_hint_len = 0;
			n+=2+psk_identity_hint_len;
			}
#ifndef OPENSSL_NO_DH
		if (alg_k & SSL_kEDH)
			{
			dhp=cert->dh_tmp;
			if ((dhp == NULL) && (s->cert->dh_tmp_cb != NULL))
				dhp=s->cert->dh_tmp_cb(s, 0, 1024);
			if (dhp == NULL)
				{
				al=SSL_AD_HANDSHAKE_FAILURE;
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, SSL_R_MISSING_TMP_DH_KEY);
				goto f_err;
				}

			if (s->s3->tmp.dh != NULL)
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_INTERNAL_ERROR);
				goto err;
				}

			if ((dh=DHparams_dup(dhp)) == NULL)
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_DH_LIB);
				goto err;
				}

			s->s3->tmp.dh=dh;
			if ((dhp->pub_key == NULL ||
			     dhp->priv_key == NULL ||
			     (s->options & SSL_OP_SINGLE_DH_USE)))
				{
				if(!DH_generate_key(dh))
				    {
				    OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_DH_LIB);
				    goto err;
				    }
				}
			else
				{
				dh->pub_key=BN_dup(dhp->pub_key);
				dh->priv_key=BN_dup(dhp->priv_key);
				if ((dh->pub_key == NULL) ||
					(dh->priv_key == NULL))
					{
					OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_DH_LIB);
					goto err;
					}
				}
			r[0]=dh->p;
			r[1]=dh->g;
			r[2]=dh->pub_key;
			}
		else
#endif
#ifndef OPENSSL_NO_ECDH
		if (alg_k & SSL_kEECDH)
			{
			const EC_GROUP *group;

			ecdhp=cert->ecdh_tmp;
			if (s->cert->ecdh_tmp_auto)
				{
				/* Get NID of appropriate shared curve */
				int nid = tls1_get_shared_curve(s);
				if (nid != NID_undef)
					ecdhp = EC_KEY_new_by_curve_name(nid);
				}
			else if ((ecdhp == NULL) && s->cert->ecdh_tmp_cb)
				{
				ecdhp = s->cert->ecdh_tmp_cb(s, 0, 1024);
				}
			if (ecdhp == NULL)
				{
				al=SSL_AD_HANDSHAKE_FAILURE;
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, SSL_R_MISSING_TMP_ECDH_KEY);
				goto f_err;
				}

			if (s->s3->tmp.ecdh != NULL)
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_INTERNAL_ERROR);
				goto err;
				}

			/* Duplicate the ECDH structure. */
			if (ecdhp == NULL)
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_ECDH_LIB);
				goto err;
				}
			if (s->cert->ecdh_tmp_auto)
				ecdh = ecdhp;
			else if ((ecdh = EC_KEY_dup(ecdhp)) == NULL)
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_ECDH_LIB);
				goto err;
				}

			s->s3->tmp.ecdh=ecdh;
			if ((EC_KEY_get0_public_key(ecdh) == NULL) ||
			    (EC_KEY_get0_private_key(ecdh) == NULL) ||
			    (s->options & SSL_OP_SINGLE_ECDH_USE))
				{
				if(!EC_KEY_generate_key(ecdh))
				    {
				    OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_ECDH_LIB);
				    goto err;
				    }
				}

			if (((group = EC_KEY_get0_group(ecdh)) == NULL) ||
			    (EC_KEY_get0_public_key(ecdh)  == NULL) ||
			    (EC_KEY_get0_private_key(ecdh) == NULL))
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_ECDH_LIB);
				goto err;
				}

			/* XXX: For now, we only support ephemeral ECDH
			 * keys over named (not generic) curves. For 
			 * supported named curves, curve_id is non-zero.
			 */
			if ((curve_id = 
			    tls1_ec_nid2curve_id(EC_GROUP_get_curve_name(group)))
			    == 0)
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, SSL_R_UNSUPPORTED_ELLIPTIC_CURVE);
				goto err;
				}

			/* Encode the public key.
			 * First check the size of encoding and
			 * allocate memory accordingly.
			 */
			encodedlen = EC_POINT_point2oct(group, 
			    EC_KEY_get0_public_key(ecdh),
			    POINT_CONVERSION_UNCOMPRESSED, 
			    NULL, 0, NULL);

			encodedPoint = (unsigned char *) 
			    OPENSSL_malloc(encodedlen*sizeof(unsigned char)); 
			bn_ctx = BN_CTX_new();
			if ((encodedPoint == NULL) || (bn_ctx == NULL))
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_MALLOC_FAILURE);
				goto err;
				}


			encodedlen = EC_POINT_point2oct(group, 
			    EC_KEY_get0_public_key(ecdh), 
			    POINT_CONVERSION_UNCOMPRESSED, 
			    encodedPoint, encodedlen, bn_ctx);

			if (encodedlen == 0) 
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_ECDH_LIB);
				goto err;
				}

			BN_CTX_free(bn_ctx);  bn_ctx=NULL;

			/* XXX: For now, we only support named (not 
			 * generic) curves in ECDH ephemeral key exchanges.
			 * In this situation, we need four additional bytes
			 * to encode the entire ServerECDHParams
			 * structure. 
			 */
			n += 4 + encodedlen;

			/* We'll generate the serverKeyExchange message
			 * explicitly so we can set these to NULLs
			 */
			r[0]=NULL;
			r[1]=NULL;
			r[2]=NULL;
			r[3]=NULL;
			}
		else
#endif /* !OPENSSL_NO_ECDH */
		if (!(alg_k & SSL_kPSK))
			{
			al=SSL_AD_HANDSHAKE_FAILURE;
			OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE);
			goto f_err;
			}
		for (i=0; i < 4 && r[i] != NULL; i++)
			{
			nr[i]=BN_num_bytes(r[i]);
			n+=2+nr[i];
			}

		if (ssl_cipher_has_server_public_key(s->s3->tmp.new_cipher))
			{
			if ((pkey=ssl_get_sign_pkey(s,s->s3->tmp.new_cipher,&md))
				== NULL)
				{
				al=SSL_AD_DECODE_ERROR;
				goto f_err;
				}
			kn=EVP_PKEY_size(pkey);
			}
		else
			{
			pkey=NULL;
			kn=0;
			}

		if (!BUF_MEM_grow_clean(buf,n+SSL_HM_HEADER_LENGTH(s)+kn))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_LIB_BUF);
			goto err;
			}
		d = p = ssl_handshake_start(s);

		for (i=0; i < 4 && r[i] != NULL; i++)
			{
			s2n(nr[i],p);
			BN_bn2bin(r[i],p);
			p+=nr[i];
			}

/* Note: ECDHE PSK ciphersuites use SSL_kEECDH and SSL_aPSK.
 * When one of them is used, the server key exchange record needs to have both
 * the psk_identity_hint and the ServerECDHParams. */
		if (alg_a & SSL_aPSK)
			{
			/* copy PSK identity hint (if provided) */
			s2n(psk_identity_hint_len, p);
			if (psk_identity_hint_len > 0)
				{
				memcpy(p, psk_identity_hint, psk_identity_hint_len);
				p+=psk_identity_hint_len;
				}
			}

#ifndef OPENSSL_NO_ECDH
		if (alg_k & SSL_kEECDH)
			{
			/* XXX: For now, we only support named (not generic) curves.
			 * In this situation, the serverKeyExchange message has:
			 * [1 byte CurveType], [2 byte CurveName]
			 * [1 byte length of encoded point], followed by
			 * the actual encoded point itself
			 */
			*p = NAMED_CURVE_TYPE;
			p += 1;
			*p = 0;
			p += 1;
			*p = curve_id;
			p += 1;
			*p = encodedlen;
			p += 1;
			memcpy((unsigned char*)p, 
			    (unsigned char *)encodedPoint, 
			    encodedlen);
			OPENSSL_free(encodedPoint);
			encodedPoint = NULL;
			p += encodedlen;
			}
#endif /* OPENSSL_NO_ECDH */

		/* not anonymous */
		if (pkey != NULL)
			{
			/* n is the length of the params, they start at &(d[4])
			 * and p points to the space at the end. */
			if (pkey->type == EVP_PKEY_RSA && !SSL_USE_SIGALGS(s))
				{
				q=md_buf;
				j=0;
				for (num=2; num > 0; num--)
					{
					EVP_DigestInit_ex(&md_ctx,
						(num == 2) ? EVP_md5() : EVP_sha1(), NULL);
					EVP_DigestUpdate(&md_ctx,&(s->s3->client_random[0]),SSL3_RANDOM_SIZE);
					EVP_DigestUpdate(&md_ctx,&(s->s3->server_random[0]),SSL3_RANDOM_SIZE);
					EVP_DigestUpdate(&md_ctx,d,n);
					EVP_DigestFinal_ex(&md_ctx,q,
						(unsigned int *)&i);
					q+=i;
					j+=i;
					}
				if (RSA_sign(NID_md5_sha1, md_buf, j,
					&(p[2]), &u, pkey->pkey.rsa) <= 0)
					{
					OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_LIB_RSA);
					goto err;
					}
				s2n(u,p);
				n+=u+2;
				}
			else
			if (md)
				{
				/* send signature algorithm */
				if (SSL_USE_SIGALGS(s))
					{
					if (!tls12_get_sigandhash(p, pkey, md))
						{
						/* Should never happen */
						al=SSL_AD_INTERNAL_ERROR;
						OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_R_INTERNAL_ERROR);
						goto f_err;
						}
					p+=2;
					}
#ifdef SSL_DEBUG
				fprintf(stderr, "Using hash %s\n",
							EVP_MD_name(md));
#endif
				EVP_SignInit_ex(&md_ctx, md, NULL);
				EVP_SignUpdate(&md_ctx,&(s->s3->client_random[0]),SSL3_RANDOM_SIZE);
				EVP_SignUpdate(&md_ctx,&(s->s3->server_random[0]),SSL3_RANDOM_SIZE);
				EVP_SignUpdate(&md_ctx,d,n);
				if (!EVP_SignFinal(&md_ctx,&(p[2]),
					(unsigned int *)&i,pkey))
					{
					OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, ERR_LIB_EVP);
					goto err;
					}
				s2n(i,p);
				n+=i+2;
				if (SSL_USE_SIGALGS(s))
					n+= 2;
				}
			else
				{
				/* Is this error check actually needed? */
				al=SSL_AD_HANDSHAKE_FAILURE;
				OPENSSL_PUT_ERROR(SSL, ssl3_send_server_key_exchange, SSL_R_UNKNOWN_PKEY_TYPE);
				goto f_err;
				}
			}

		ssl_set_handshake_header(s, SSL3_MT_SERVER_KEY_EXCHANGE, n);
		}

	s->state = SSL3_ST_SW_KEY_EXCH_B;
	EVP_MD_CTX_cleanup(&md_ctx);
	return ssl_do_write(s);
f_err:
	ssl3_send_alert(s,SSL3_AL_FATAL,al);
err:
#ifndef OPENSSL_NO_ECDH
	if (encodedPoint != NULL) OPENSSL_free(encodedPoint);
	BN_CTX_free(bn_ctx);
#endif
	EVP_MD_CTX_cleanup(&md_ctx);
	return(-1);
	}

int ssl3_send_certificate_request(SSL *s)
	{
	unsigned char *p,*d;
	int i,j,nl,off,n;
	STACK_OF(X509_NAME) *sk=NULL;
	X509_NAME *name;
	BUF_MEM *buf;

	if (s->state == SSL3_ST_SW_CERT_REQ_A)
		{
		buf=s->init_buf;

		d=p=ssl_handshake_start(s);

		/* get the list of acceptable cert types */
		p++;
		n=ssl3_get_req_cert_type(s,p);
		d[0]=n;
		p+=n;
		n++;

		if (SSL_USE_SIGALGS(s))
			{
			const unsigned char *psigs;
			nl = tls12_get_psigalgs(s, &psigs);
			s2n(nl, p);
			memcpy(p, psigs, nl);
			p += nl;
			n += nl + 2;
			}

		off=n;
		p+=2;
		n+=2;

		sk=SSL_get_client_CA_list(s);
		nl=0;
		if (sk != NULL)
			{
			for (i=0; i<sk_X509_NAME_num(sk); i++)
				{
				name=sk_X509_NAME_value(sk,i);
				j=i2d_X509_NAME(name,NULL);
				if (!BUF_MEM_grow_clean(buf,SSL_HM_HEADER_LENGTH(s)+n+j+2))
					{
					OPENSSL_PUT_ERROR(SSL, ssl3_send_certificate_request, ERR_R_BUF_LIB);
					goto err;
					}
				p = ssl_handshake_start(s) + n;
				s2n(j,p);
				i2d_X509_NAME(name,&p);
				n+=2+j;
				nl+=2+j;
				}
			}
		/* else no CA names */
		p = ssl_handshake_start(s) + off;
		s2n(nl,p);

		ssl_set_handshake_header(s, SSL3_MT_CERTIFICATE_REQUEST, n);

#ifdef NETSCAPE_HANG_BUG
		if (!SSL_IS_DTLS(s))
			{
			if (!BUF_MEM_grow_clean(buf, s->init_num + 4))
				{
				OPENSSL_PUT_ERROR(SSL, ssl3_send_certificate_request, ERR_R_BUF_LIB);
				goto err;
				}
			p=(unsigned char *)s->init_buf->data + s->init_num;
			/* do the header */
			*(p++)=SSL3_MT_SERVER_DONE;
			*(p++)=0;
			*(p++)=0;
			*(p++)=0;
			s->init_num += 4;
			}
#endif

		s->state = SSL3_ST_SW_CERT_REQ_B;
		}

	/* SSL3_ST_SW_CERT_REQ_B */
	return ssl_do_write(s);
err:
	return(-1);
	}

int ssl3_get_client_key_exchange(SSL *s)
	{
	int al,ok;
	long n;
	CBS client_key_exchange;
	unsigned long alg_k;
	unsigned long alg_a;
	uint8_t *premaster_secret = NULL;
	size_t premaster_secret_len = 0;
	RSA *rsa=NULL;
	uint8_t *decrypt_buf = NULL;
	EVP_PKEY *pkey=NULL;
#ifndef OPENSSL_NO_DH
	BIGNUM *pub=NULL;
	DH *dh_srvr;
#endif

#ifndef OPENSSL_NO_ECDH
	EC_KEY *srvr_ecdh = NULL;
	EVP_PKEY *clnt_pub_pkey = NULL;
	EC_POINT *clnt_ecpoint = NULL;
	BN_CTX *bn_ctx = NULL;
	unsigned int psk_len = 0;
	unsigned char psk[PSK_MAX_PSK_LEN];
#endif

	n=s->method->ssl_get_message(s,
		SSL3_ST_SR_KEY_EXCH_A,
		SSL3_ST_SR_KEY_EXCH_B,
		SSL3_MT_CLIENT_KEY_EXCHANGE,
		2048, /* ??? */
		&ok);

	if (!ok) return((int)n);
	CBS_init(&client_key_exchange, s->init_msg, n);

	alg_k=s->s3->tmp.new_cipher->algorithm_mkey;
	alg_a=s->s3->tmp.new_cipher->algorithm_auth;

	/* If using a PSK key exchange, prepare the pre-shared key. */
	if (alg_a & SSL_aPSK)
		{
		CBS psk_identity;

		/* If using PSK, the ClientKeyExchange contains a
		 * psk_identity. If PSK, then this is the only field
		 * in the message. */
		if (!CBS_get_u16_length_prefixed(&client_key_exchange, &psk_identity) ||
			((alg_k & SSL_kPSK) && CBS_len(&client_key_exchange) != 0))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_DECODE_ERROR);
			al = SSL_AD_DECODE_ERROR;
			goto f_err;
			}

		if (s->psk_server_callback == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_PSK_NO_SERVER_CB);
			al = SSL_AD_INTERNAL_ERROR;
			goto f_err;
			}

		if (CBS_len(&psk_identity) > PSK_MAX_IDENTITY_LEN ||
			CBS_contains_zero_byte(&psk_identity))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_DATA_LENGTH_TOO_LONG);
			al = SSL_AD_ILLEGAL_PARAMETER;
			goto f_err;
			}

		if (!CBS_strdup(&psk_identity, &s->session->psk_identity))
			{
			al = SSL_AD_INTERNAL_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto f_err;
			}

		/* Look up the key for the identity. */
		psk_len = s->psk_server_callback(s, s->session->psk_identity, psk, sizeof(psk));
		if (psk_len > PSK_MAX_PSK_LEN)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_INTERNAL_ERROR);
			al = SSL_AD_INTERNAL_ERROR;
			goto f_err;
			}
		else if (psk_len == 0)
			{
			/* PSK related to the given identity not found */
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_PSK_IDENTITY_NOT_FOUND);
			al = SSL_AD_UNKNOWN_PSK_IDENTITY;
			goto f_err;
			}
		}

	/* Depending on the key exchange method, compute |premaster_secret| and
	 * |premaster_secret_len|. */
	if (alg_k & SSL_kRSA)
		{
		CBS encrypted_premaster_secret;
		uint8_t rand_premaster_secret[SSL_MAX_MASTER_KEY_LENGTH];
		int decrypt_good_mask;
		uint8_t version_good;
		size_t rsa_size, decrypt_len, premaster_index, j;

		pkey=s->cert->pkeys[SSL_PKEY_RSA_ENC].privatekey;
		if (	(pkey == NULL) ||
			(pkey->type != EVP_PKEY_RSA) ||
			(pkey->pkey.rsa == NULL))
			{
			al=SSL_AD_HANDSHAKE_FAILURE;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_MISSING_RSA_CERTIFICATE);
			goto f_err;
			}
		rsa=pkey->pkey.rsa;

		/* TLS and [incidentally] DTLS{0xFEFF} */
		if (s->version > SSL3_VERSION)
			{
			CBS copy = client_key_exchange;
			if (!CBS_get_u16_length_prefixed(&client_key_exchange,
					&encrypted_premaster_secret) ||
				CBS_len(&client_key_exchange) != 0)
				{
				if (!(s->options & SSL_OP_TLS_D5_BUG))
					{
					al = SSL_AD_DECODE_ERROR;
					OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_TLS_RSA_ENCRYPTED_VALUE_LENGTH_IS_WRONG);
					goto f_err;
					}
				else
					encrypted_premaster_secret = copy;
				}
			}
		else
			encrypted_premaster_secret = client_key_exchange;

		/* Reject overly short RSA keys because we want to be sure that
		 * the buffer size makes it safe to iterate over the entire size
		 * of a premaster secret (SSL_MAX_MASTER_KEY_LENGTH). The actual
		 * expected size is larger due to RSA padding, but the bound is
		 * sufficient to be safe. */
		rsa_size = RSA_size(rsa);
		if (rsa_size < SSL_MAX_MASTER_KEY_LENGTH)
			{
			al = SSL_AD_DECRYPT_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_DECRYPTION_FAILED);
			goto f_err;
			}

		/* We must not leak whether a decryption failure occurs because
		 * of Bleichenbacher's attack on PKCS #1 v1.5 RSA padding (see
		 * RFC 2246, section 7.4.7.1). The code follows that advice of
		 * the TLS RFC and generates a random premaster secret for the
		 * case that the decrypt fails. See
		 * https://tools.ietf.org/html/rfc5246#section-7.4.7.1 */
		if (RAND_pseudo_bytes(rand_premaster_secret,
				      sizeof(rand_premaster_secret)) <= 0)
			goto err;

		/* Allocate a buffer large enough for an RSA decryption. */
		decrypt_buf = OPENSSL_malloc(rsa_size);
		if (decrypt_buf == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}

		/* Decrypt with no padding. PKCS#1 padding will be removed as
		 * part of the timing-sensitive code below. */
		if (!RSA_decrypt(rsa, &decrypt_len, decrypt_buf, rsa_size,
				CBS_data(&encrypted_premaster_secret),
				CBS_len(&encrypted_premaster_secret),
				RSA_NO_PADDING))
			{
			goto err;
			}
		if (decrypt_len != rsa_size)
			{
			/* This should never happen, but do a check so we do not
			 * read uninitialized memory. */
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_INTERNAL_ERROR);
			goto err;
			}

		/* Remove the PKCS#1 padding and adjust decrypt_len as
		 * appropriate. decrypt_good_mask will be zero if the premaster
		 * if good and non-zero otherwise. */
		decrypt_good_mask = RSA_message_index_PKCS1_type_2(
			decrypt_buf, decrypt_len, &premaster_index);
		decrypt_good_mask--;
		decrypt_len = decrypt_len - premaster_index;

		/* decrypt_len should be SSL_MAX_MASTER_KEY_LENGTH. */
		decrypt_good_mask |= decrypt_len ^ SSL_MAX_MASTER_KEY_LENGTH;

		/* Copy over the unpadded premaster. Whatever the value of
		 * |decrypt_good_mask|, copy as if the premaster were the right
		 * length. It is important the memory access pattern be
		 * constant. */
		premaster_secret = BUF_memdup(
			decrypt_buf + (rsa_size - SSL_MAX_MASTER_KEY_LENGTH),
			SSL_MAX_MASTER_KEY_LENGTH);
		if (premaster_secret == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}
		OPENSSL_free(decrypt_buf);
		decrypt_buf = NULL;

		/* If the version in the decrypted pre-master secret is correct
		 * then version_good will be zero. The Klima-Pokorny-Rosa
		 * extension of Bleichenbacher's attack
		 * (http://eprint.iacr.org/2003/052/) exploits the version
		 * number check as a "bad version oracle". Thus version checks
		 * are done in constant time and are treated like any other
		 * decryption error. */
		version_good = premaster_secret[0] ^ (s->client_version>>8);
		version_good |= premaster_secret[1] ^ (s->client_version&0xff);

		/* If any bits in version_good are set then they'll poision
		 * decrypt_good_mask and cause rand_premaster_secret to be
		 * used. */
		decrypt_good_mask |= version_good;

		/* decrypt_good_mask will be zero iff decrypt_len ==
		 * SSL_MAX_MASTER_KEY_LENGTH and the version check passed. We
		 * fold the bottom 32 bits of it with an OR so that the LSB
		 * will be zero iff everything is good. This assumes that we'll
		 * never decrypt a value > 2**31 bytes, which seems safe. */
		decrypt_good_mask |= decrypt_good_mask >> 16;
		decrypt_good_mask |= decrypt_good_mask >> 8;
		decrypt_good_mask |= decrypt_good_mask >> 4;
		decrypt_good_mask |= decrypt_good_mask >> 2;
		decrypt_good_mask |= decrypt_good_mask >> 1;
		/* Now select only the LSB and subtract one. If decrypt_len ==
		 * SSL_MAX_MASTER_KEY_LENGTH and the version check passed then
		 * decrypt_good_mask will be all ones. Otherwise it'll be all
		 * zeros. */
		decrypt_good_mask &= 1;
		decrypt_good_mask--;

		/* Now copy rand_premaster_secret over premaster_secret using
		 * decrypt_good_mask. */
		for (j = 0; j < sizeof(rand_premaster_secret); j++)
			{
			premaster_secret[j] = (premaster_secret[j] & decrypt_good_mask) |
			       (rand_premaster_secret[j] & ~decrypt_good_mask);
			}

		premaster_secret_len = sizeof(rand_premaster_secret);
		}
#ifndef OPENSSL_NO_DH
	else if (alg_k & SSL_kEDH)
		{
		CBS dh_Yc;
		int dh_len;

		if (!CBS_get_u16_length_prefixed(&client_key_exchange, &dh_Yc) ||
			CBS_len(&dh_Yc) == 0 ||
			CBS_len(&client_key_exchange) != 0)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_DH_PUBLIC_VALUE_LENGTH_IS_WRONG);
			al = SSL_R_DECODE_ERROR;
			goto f_err;
			}

		if (s->s3->tmp.dh == NULL)
			{
			al=SSL_AD_HANDSHAKE_FAILURE;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_MISSING_TMP_DH_KEY);
			goto f_err;
			}
                dh_srvr=s->s3->tmp.dh;

		pub = BN_bin2bn(CBS_data(&dh_Yc), CBS_len(&dh_Yc), NULL);
		if (pub == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_BN_LIB);
			goto err;
			}

		/* Allocate a buffer for the premaster secret. */
		premaster_secret = OPENSSL_malloc(DH_size(dh_srvr));
		if (premaster_secret == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}

		dh_len = DH_compute_key(premaster_secret, pub, dh_srvr);
		if (dh_len <= 0)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_DH_LIB);
			BN_clear_free(pub);
			goto err;
			}

		DH_free(s->s3->tmp.dh);
		s->s3->tmp.dh=NULL;
		BN_clear_free(pub);
		pub=NULL;

		premaster_secret_len = dh_len;
		}
#endif

#ifndef OPENSSL_NO_ECDH
	else if (alg_k & SSL_kEECDH)
		{
		int field_size = 0, ecdh_len;
		const EC_KEY   *tkey;
		const EC_GROUP *group;
		const BIGNUM *priv_key;
		CBS ecdh_Yc;

		/* initialize structures for server's ECDH key pair */
		if ((srvr_ecdh = EC_KEY_new()) == NULL) 
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}

                /* Use the ephermeral values we saved when generating the
                 * ServerKeyExchange msg. */
                tkey = s->s3->tmp.ecdh;

		group    = EC_KEY_get0_group(tkey);
		priv_key = EC_KEY_get0_private_key(tkey);

		if (!EC_KEY_set_group(srvr_ecdh, group) ||
		    !EC_KEY_set_private_key(srvr_ecdh, priv_key))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_EC_LIB);
			goto err;
			}

		/* Let's get client's public key */
		if ((clnt_ecpoint = EC_POINT_new(group)) == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}

		/* Get client's public key from encoded point
		 * in the ClientKeyExchange message.
		 */
		if (!CBS_get_u8_length_prefixed(&client_key_exchange, &ecdh_Yc) ||
			CBS_len(&client_key_exchange) != 0)
			{
			al = SSL_AD_DECODE_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_DECODE_ERROR);
			goto f_err;
			}

		if ((bn_ctx = BN_CTX_new()) == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}

		if (!EC_POINT_oct2point(group, clnt_ecpoint,
				CBS_data(&ecdh_Yc), CBS_len(&ecdh_Yc), bn_ctx))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_EC_LIB);
			goto err;
			}

		/* Allocate a buffer for both the secret and the PSK. */
		field_size = EC_GROUP_get_degree(group);
		if (field_size <= 0)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_ECDH_LIB);
			goto err;
			}

		ecdh_len = (field_size + 7) / 8;
		premaster_secret = OPENSSL_malloc(ecdh_len);
		if (premaster_secret == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}

		/* Compute the shared pre-master secret */
		ecdh_len = ECDH_compute_key(premaster_secret,
			ecdh_len, clnt_ecpoint, srvr_ecdh, NULL);
		if (ecdh_len <= 0)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_ECDH_LIB);
			goto err;
			}

		EVP_PKEY_free(clnt_pub_pkey);
		EC_POINT_free(clnt_ecpoint);
		EC_KEY_free(srvr_ecdh);
		BN_CTX_free(bn_ctx);
		EC_KEY_free(s->s3->tmp.ecdh);
		s->s3->tmp.ecdh = NULL;

		premaster_secret_len = ecdh_len;
		}
#endif
	else if (alg_k & SSL_kPSK)
		{
		/* For plain PSK, other_secret is a block of 0s with the same
		 * length as the pre-shared key. */
		premaster_secret_len = psk_len;
		premaster_secret = OPENSSL_malloc(premaster_secret_len);
		if (premaster_secret == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}
		memset(premaster_secret, 0, premaster_secret_len);
		}
	else
		{
		al=SSL_AD_HANDSHAKE_FAILURE;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, SSL_R_UNKNOWN_CIPHER_TYPE);
		goto f_err;
		}

	/* For a PSK cipher suite, the actual pre-master secret is combined with
	 * the pre-shared key. */
	if (alg_a & SSL_aPSK)
		{
		CBB new_premaster, child;
		uint8_t *new_data;
		size_t new_len;

		if (!CBB_init(&new_premaster, 2 + psk_len + 2 + premaster_secret_len))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_MALLOC_FAILURE);
			goto err;
			}
		if (!CBB_add_u16_length_prefixed(&new_premaster, &child) ||
			!CBB_add_bytes(&child, premaster_secret, premaster_secret_len) ||
			!CBB_add_u16_length_prefixed(&new_premaster, &child) ||
			!CBB_add_bytes(&child, psk, psk_len) ||
			!CBB_finish(&new_premaster, &new_data, &new_len))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_key_exchange, ERR_R_INTERNAL_ERROR);
			CBB_cleanup(&new_premaster);
			goto err;
			}

		OPENSSL_cleanse(premaster_secret, premaster_secret_len);
		OPENSSL_free(premaster_secret);
		premaster_secret = new_data;
		premaster_secret_len = new_len;
		}

	/* Compute the master secret */
	s->session->master_key_length = s->method->ssl3_enc
		->generate_master_secret(s,
			s->session->master_key, premaster_secret, premaster_secret_len);

	OPENSSL_cleanse(premaster_secret, premaster_secret_len);
	OPENSSL_free(premaster_secret);
	return 1;
f_err:
	ssl3_send_alert(s,SSL3_AL_FATAL,al);
err:
	if (premaster_secret)
		{
		if (premaster_secret_len)
			OPENSSL_cleanse(premaster_secret, premaster_secret_len);
		OPENSSL_free(premaster_secret);
		}
	if (decrypt_buf)
		OPENSSL_free(decrypt_buf);
#ifndef OPENSSL_NO_ECDH
	EVP_PKEY_free(clnt_pub_pkey);
	EC_POINT_free(clnt_ecpoint);
	if (srvr_ecdh != NULL) 
		EC_KEY_free(srvr_ecdh);
	BN_CTX_free(bn_ctx);
#endif
	return(-1);
	}

int ssl3_get_cert_verify(SSL *s)
	{
	EVP_PKEY *pkey=NULL;
	int al,ok,ret=0;
	long n;
	CBS certificate_verify, signature;
	int type = 0;
	X509 *peer = s->session->peer;
	const EVP_MD *md = NULL;
	EVP_MD_CTX mctx;

	EVP_MD_CTX_init(&mctx);

	/* Determine if a CertificateVerify message is expected at all. It is
	 * important that this be determined before ssl_get_message is called,
	 * so as not to process the ChangeCipherSpec message early. */
	if (peer != NULL)
		{
		pkey = X509_get_pubkey(peer);
		type = X509_certificate_type(peer,pkey);
		}
	if (!(type & EVP_PKT_SIGN))
		{
		ret = 1;
		goto done_with_buffer;
		}

	n=s->method->ssl_get_message(s,
		SSL3_ST_SR_CERT_VRFY_A,
		SSL3_ST_SR_CERT_VRFY_B,
		SSL3_MT_CERTIFICATE_VERIFY,
		SSL3_RT_MAX_PLAIN_LENGTH,
		&ok);

	if (!ok)
		{
		ret = (int)n;
		goto done;
		}

	CBS_init(&certificate_verify, s->init_msg, n);

	/* We now have a signature that we need to verify. */
	/* TODO(davidben): This should share code with
	 * ssl3_get_server_key_exchange. */

	if (SSL_USE_SIGALGS(s))
		{
		if (!tls12_check_peer_sigalg(&md, &al, s, &certificate_verify, pkey))
			goto f_err;
		}

	if (!CBS_get_u16_length_prefixed(&certificate_verify, &signature) ||
		CBS_len(&certificate_verify) != 0)
		{
		al = SSL_AD_DECODE_ERROR;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_cert_verify, SSL_R_DECODE_ERROR);
		goto f_err;
		}

	if (SSL_USE_SIGALGS(s))
		{
		size_t hdatalen;
		const uint8_t *hdata;
		if (!BIO_mem_contents(s->s3->handshake_buffer, &hdata, &hdatalen))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_cert_verify, ERR_R_INTERNAL_ERROR);
			al=SSL_AD_INTERNAL_ERROR;
			goto f_err;
			}
		if (!EVP_VerifyInit_ex(&mctx, md, NULL)
			|| !EVP_VerifyUpdate(&mctx, hdata, hdatalen))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_cert_verify, ERR_R_EVP_LIB);
			al=SSL_AD_INTERNAL_ERROR;
			goto f_err;
			}

		if (EVP_VerifyFinal(&mctx,
				CBS_data(&signature), CBS_len(&signature),
				pkey) <= 0)
			{
			al=SSL_AD_DECRYPT_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_cert_verify, SSL_R_BAD_SIGNATURE);
			goto f_err;
			}
		}
	else
	if (pkey->type == EVP_PKEY_RSA)
		{
		if (!RSA_verify(NID_md5_sha1, s->s3->tmp.cert_verify_md,
				MD5_DIGEST_LENGTH+SHA_DIGEST_LENGTH,
				CBS_data(&signature), CBS_len(&signature),
				pkey->pkey.rsa))
			{
			al = SSL_AD_DECRYPT_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_cert_verify, SSL_R_BAD_RSA_SIGNATURE);
			goto f_err;
			}
		}
	else
#ifndef OPENSSL_NO_ECDSA
		if (pkey->type == EVP_PKEY_EC)
		{
		if (!ECDSA_verify(pkey->save_type,
				&(s->s3->tmp.cert_verify_md[MD5_DIGEST_LENGTH]),
				SHA_DIGEST_LENGTH,
				CBS_data(&signature), CBS_len(&signature),
				pkey->pkey.ec))
			{
			/* bad signature */
			al = SSL_AD_DECRYPT_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_cert_verify, SSL_R_BAD_ECDSA_SIGNATURE);
			goto f_err;
			}
		}
	else
#endif
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_get_cert_verify, ERR_R_INTERNAL_ERROR);
		al=SSL_AD_UNSUPPORTED_CERTIFICATE;
		goto f_err;
		}


	ret=1;
	if (0)
		{
f_err:
		ssl3_send_alert(s,SSL3_AL_FATAL,al);
		}
done_with_buffer:
	/* There is no more need for the handshake buffer. */
	if (s->s3->handshake_buffer)
		{
		BIO_free(s->s3->handshake_buffer);
		s->s3->handshake_buffer = NULL;
		s->s3->flags &= ~TLS1_FLAGS_KEEP_HANDSHAKE;
		}
done:
	EVP_MD_CTX_cleanup(&mctx);
	EVP_PKEY_free(pkey);
	return(ret);
	}

int ssl3_get_client_certificate(SSL *s)
	{
	int i,ok,al,ret= -1;
	X509 *x=NULL;
	unsigned long n;
	STACK_OF(X509) *sk=NULL;
	SHA256_CTX sha256;
	CBS certificate_msg, certificate_list;
	int is_first_certificate = 1;

	n=s->method->ssl_get_message(s,
		SSL3_ST_SR_CERT_A,
		SSL3_ST_SR_CERT_B,
		-1,
		s->max_cert_list,
		&ok);

	if (!ok) return((int)n);

	if	(s->s3->tmp.message_type == SSL3_MT_CLIENT_KEY_EXCHANGE)
		{
		if (	(s->verify_mode & SSL_VERIFY_PEER) &&
			(s->verify_mode & SSL_VERIFY_FAIL_IF_NO_PEER_CERT))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_PEER_DID_NOT_RETURN_A_CERTIFICATE);
			al=SSL_AD_HANDSHAKE_FAILURE;
			goto f_err;
			}
		/* If tls asked for a client cert, the client must return a 0 list */
		if ((s->version > SSL3_VERSION) && s->s3->tmp.cert_request)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_TLS_PEER_DID_NOT_RESPOND_WITH_CERTIFICATE_LIST);
			al=SSL_AD_UNEXPECTED_MESSAGE;
			goto f_err;
			}
		s->s3->tmp.reuse_message=1;
		return(1);
		}

	if (s->s3->tmp.message_type != SSL3_MT_CERTIFICATE)
		{
		al=SSL_AD_UNEXPECTED_MESSAGE;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_WRONG_MESSAGE_TYPE);
		goto f_err;
		}

	CBS_init(&certificate_msg, s->init_msg, n);

	if ((sk=sk_X509_new_null()) == NULL)
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, ERR_R_MALLOC_FAILURE);
		goto err;
		}

	if (!CBS_get_u24_length_prefixed(&certificate_msg, &certificate_list) ||
		CBS_len(&certificate_msg) != 0)
		{
		al = SSL_AD_DECODE_ERROR;
		OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_DECODE_ERROR);
		goto f_err;
		}

	while (CBS_len(&certificate_list) > 0)
		{
		CBS certificate;
		const uint8_t *data;

		if (!CBS_get_u24_length_prefixed(&certificate_list, &certificate))
			{
			al = SSL_AD_DECODE_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_DECODE_ERROR);
			goto f_err;
			}
		if (is_first_certificate && s->ctx->retain_only_sha256_of_client_certs)
			{
			/* If this is the first certificate, and we don't want
			 * to keep peer certificates in memory, then we hash it
			 * right away. */
			SHA256_Init(&sha256);
			SHA256_Update(&sha256, CBS_data(&certificate), CBS_len(&certificate));
			SHA256_Final(s->session->peer_sha256, &sha256);
			s->session->peer_sha256_valid = 1;
			}
		is_first_certificate = 0;
		data = CBS_data(&certificate);
		x = d2i_X509(NULL, &data, CBS_len(&certificate));
		if (x == NULL)
			{
			al = SSL_AD_BAD_CERTIFICATE;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, ERR_R_ASN1_LIB);
			goto f_err;
			}
		if (!CBS_skip(&certificate, data - CBS_data(&certificate)))
			{
			al = SSL_AD_INTERNAL_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, ERR_R_INTERNAL_ERROR);
			goto f_err;
			}
		if (CBS_len(&certificate) != 0)
			{
			al = SSL_AD_DECODE_ERROR;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_CERT_LENGTH_MISMATCH);
			goto f_err;
			}
		if (!sk_X509_push(sk,x))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, ERR_R_MALLOC_FAILURE);
			goto err;
			}
		x = NULL;
		}

	if (sk_X509_num(sk) <= 0)
		{
		/* TLS does not mind 0 certs returned */
		if (s->version == SSL3_VERSION)
			{
			al=SSL_AD_HANDSHAKE_FAILURE;
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_NO_CERTIFICATES_RETURNED);
			goto f_err;
			}
		/* Fail for TLS only if we required a certificate */
		else if ((s->verify_mode & SSL_VERIFY_PEER) &&
			 (s->verify_mode & SSL_VERIFY_FAIL_IF_NO_PEER_CERT))
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_PEER_DID_NOT_RETURN_A_CERTIFICATE);
			al=SSL_AD_HANDSHAKE_FAILURE;
			goto f_err;
			}
		/* No client certificate so digest cached records */
		if (s->s3->handshake_buffer && !ssl3_digest_cached_records(s))
			{
			al=SSL_AD_INTERNAL_ERROR;
			goto f_err;
			}
		}
	else
		{
		i=ssl_verify_cert_chain(s,sk);
		if (i <= 0)
			{
			al=ssl_verify_alarm_type(s->verify_result);
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, SSL_R_CERTIFICATE_VERIFY_FAILED);
			goto f_err;
			}
		}

	if (s->session->peer != NULL) /* This should not be needed */
		X509_free(s->session->peer);
	s->session->peer=sk_X509_shift(sk);
	s->session->verify_result = s->verify_result;

	/* With the current implementation, sess_cert will always be NULL
	 * when we arrive here. */
	if (s->session->sess_cert == NULL)
		{
		s->session->sess_cert = ssl_sess_cert_new();
		if (s->session->sess_cert == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_get_client_certificate, ERR_R_MALLOC_FAILURE);
			goto err;
			}
		}
	if (s->session->sess_cert->cert_chain != NULL)
		sk_X509_pop_free(s->session->sess_cert->cert_chain, X509_free);
	s->session->sess_cert->cert_chain=sk;
	/* Inconsistency alert: cert_chain does *not* include the
	 * peer's own certificate, while we do include it in s3_clnt.c */

	sk=NULL;

	ret=1;
	if (0)
		{
f_err:
		ssl3_send_alert(s,SSL3_AL_FATAL,al);
		}
err:
	if (x != NULL) X509_free(x);
	if (sk != NULL) sk_X509_pop_free(sk,X509_free);
	return(ret);
	}

int ssl3_send_server_certificate(SSL *s)
	{
	CERT_PKEY *cpk;

	if (s->state == SSL3_ST_SW_CERT_A)
		{
		cpk=ssl_get_server_send_pkey(s);
		if (cpk == NULL)
			{
			OPENSSL_PUT_ERROR(SSL, ssl3_send_server_certificate, ERR_R_INTERNAL_ERROR);
			return(0);
			}

		ssl3_output_cert_chain(s,cpk);
		s->state=SSL3_ST_SW_CERT_B;
		}

	/* SSL3_ST_SW_CERT_B */
	return ssl_do_write(s);
	}

/* send a new session ticket (not necessarily for a new session) */
int ssl3_send_newsession_ticket(SSL *s)
	{
	if (s->state == SSL3_ST_SW_SESSION_TICKET_A)
		{
		unsigned char *p, *senc, *macstart;
		const unsigned char *const_p;
		int len, slen_full, slen;
		SSL_SESSION *sess;
		unsigned int hlen;
		EVP_CIPHER_CTX ctx;
		HMAC_CTX hctx;
		SSL_CTX *tctx = s->initial_ctx;
		unsigned char iv[EVP_MAX_IV_LENGTH];
		unsigned char key_name[16];

		/* get session encoding length */
		slen_full = i2d_SSL_SESSION(s->session, NULL);
		/* Some length values are 16 bits, so forget it if session is
 		 * too long
 		 */
		if (slen_full > 0xFF00)
			return -1;
		senc = OPENSSL_malloc(slen_full);
		if (!senc)
			return -1;
		p = senc;
		i2d_SSL_SESSION(s->session, &p);

		/* create a fresh copy (not shared with other threads) to clean up */
		const_p = senc;
		sess = d2i_SSL_SESSION(NULL, &const_p, slen_full);
		if (sess == NULL)
			{
			OPENSSL_free(senc);
			return -1;
			}
		sess->session_id_length = 0; /* ID is irrelevant for the ticket */

		slen = i2d_SSL_SESSION(sess, NULL);
		if (slen > slen_full) /* shouldn't ever happen */
			{
			OPENSSL_free(senc);
			return -1;
			}
		p = senc;
		i2d_SSL_SESSION(sess, &p);
		SSL_SESSION_free(sess);

		/* Grow buffer if need be: the length calculation is as
 		 * follows handshake_header_length +
 		 * 4 (ticket lifetime hint) + 2 (ticket length) +
 		 * 16 (key name) + max_iv_len (iv length) +
 		 * session_length + max_enc_block_size (max encrypted session
 		 * length) + max_md_size (HMAC).
 		 */
		if (!BUF_MEM_grow(s->init_buf,
			SSL_HM_HEADER_LENGTH(s) + 22 + EVP_MAX_IV_LENGTH +
			EVP_MAX_BLOCK_LENGTH + EVP_MAX_MD_SIZE + slen))
			return -1;
		p = ssl_handshake_start(s);
		EVP_CIPHER_CTX_init(&ctx);
		HMAC_CTX_init(&hctx);
		/* Initialize HMAC and cipher contexts. If callback present
		 * it does all the work otherwise use generated values
		 * from parent ctx.
		 */
		if (tctx->tlsext_ticket_key_cb)
			{
			if (tctx->tlsext_ticket_key_cb(s, key_name, iv, &ctx,
							 &hctx, 1) < 0)
				{
				OPENSSL_free(senc);
				return -1;
				}
			}
		else
			{
			RAND_pseudo_bytes(iv, 16);
			EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL,
					tctx->tlsext_tick_aes_key, iv);
			HMAC_Init_ex(&hctx, tctx->tlsext_tick_hmac_key, 16,
					tlsext_tick_md(), NULL);
			memcpy(key_name, tctx->tlsext_tick_key_name, 16);
			}

		/* Ticket lifetime hint (advisory only):
		 * We leave this unspecified for resumed session (for simplicity),
		 * and guess that tickets for new sessions will live as long
		 * as their sessions. */
		l2n(s->hit ? 0 : s->session->timeout, p);

		/* Skip ticket length for now */
		p += 2;
		/* Output key name */
		macstart = p;
		memcpy(p, key_name, 16);
		p += 16;
		/* output IV */
		memcpy(p, iv, EVP_CIPHER_CTX_iv_length(&ctx));
		p += EVP_CIPHER_CTX_iv_length(&ctx);
		/* Encrypt session data */
		EVP_EncryptUpdate(&ctx, p, &len, senc, slen);
		p += len;
		EVP_EncryptFinal_ex(&ctx, p, &len);
		p += len;
		EVP_CIPHER_CTX_cleanup(&ctx);

		HMAC_Update(&hctx, macstart, p - macstart);
		HMAC_Final(&hctx, p, &hlen);
		HMAC_CTX_cleanup(&hctx);

		p += hlen;
		/* Now write out lengths: p points to end of data written */
		/* Total length */
		len = p - ssl_handshake_start(s);
		ssl_set_handshake_header(s, SSL3_MT_NEWSESSION_TICKET, len);
		/* Skip ticket lifetime hint */
		p = ssl_handshake_start(s) + 4;
		s2n(len - 6, p);
		s->state=SSL3_ST_SW_SESSION_TICKET_B;
		OPENSSL_free(senc);
		}

	/* SSL3_ST_SW_SESSION_TICKET_B */
	return ssl_do_write(s);
	}

int ssl3_send_cert_status(SSL *s)
	{
	if (s->state == SSL3_ST_SW_CERT_STATUS_A)
		{
		unsigned char *p;
		/* Grow buffer if need be: the length calculation is as
 		 * follows 1 (message type) + 3 (message length) +
 		 * 1 (ocsp response type) + 3 (ocsp response length)
 		 * + (ocsp response)
 		 */
		if (!BUF_MEM_grow(s->init_buf, 8 + s->tlsext_ocsp_resplen))
			return -1;

		p=(unsigned char *)s->init_buf->data;

		/* do the header */
		*(p++)=SSL3_MT_CERTIFICATE_STATUS;
		/* message length */
		l2n3(s->tlsext_ocsp_resplen + 4, p);
		/* status type */
		*(p++)= s->tlsext_status_type;
		/* length of OCSP response */
		l2n3(s->tlsext_ocsp_resplen, p);
		/* actual response */
		memcpy(p, s->tlsext_ocsp_resp, s->tlsext_ocsp_resplen);
		/* number of bytes to write */
		s->init_num = 8 + s->tlsext_ocsp_resplen;
		s->state=SSL3_ST_SW_CERT_STATUS_B;
		s->init_off = 0;
		}

	/* SSL3_ST_SW_CERT_STATUS_B */
	return(ssl3_do_write(s,SSL3_RT_HANDSHAKE));
	}

# ifndef OPENSSL_NO_NEXTPROTONEG
/* ssl3_get_next_proto reads a Next Protocol Negotiation handshake message. It
 * sets the next_proto member in s if found */
int ssl3_get_next_proto(SSL *s)
	{
	int ok;
	long n;
	CBS next_protocol, selected_protocol, padding;

	/* Clients cannot send a NextProtocol message if we didn't see the
	 * extension in their ClientHello */
	if (!s->s3->next_proto_neg_seen)
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_get_next_proto, SSL_R_GOT_NEXT_PROTO_WITHOUT_EXTENSION);
		return -1;
		}

	n=s->method->ssl_get_message(s,
		SSL3_ST_SR_NEXT_PROTO_A,
		SSL3_ST_SR_NEXT_PROTO_B,
		SSL3_MT_NEXT_PROTO,
		514,  /* See the payload format below */
		&ok);

	if (!ok)
		return((int)n);

	/* s->state doesn't reflect whether ChangeCipherSpec has been received
	 * in this handshake, but s->s3->change_cipher_spec does (will be reset
	 * by ssl3_get_finished).
	 * TODO(davidben): Is this check now redundant with
	 * SSL3_FLAGS_EXPECT_CCS? */
	if (!s->s3->change_cipher_spec)
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_get_next_proto, SSL_R_GOT_NEXT_PROTO_BEFORE_A_CCS);
		return -1;
		}

	CBS_init(&next_protocol, s->init_msg, n);

	/* The payload looks like:
	 *   uint8 proto_len;
	 *   uint8 proto[proto_len];
	 *   uint8 padding_len;
	 *   uint8 padding[padding_len];
	 */
	if (!CBS_get_u8_length_prefixed(&next_protocol, &selected_protocol) ||
		!CBS_get_u8_length_prefixed(&next_protocol, &padding) ||
		CBS_len(&next_protocol) != 0)
		return 0;

	if (!CBS_stow(&selected_protocol,
			&s->next_proto_negotiated,
			&s->next_proto_negotiated_len))
		return 0;

	return 1;
	}
# endif

/* ssl3_get_channel_id reads and verifies a ClientID handshake message. */
int ssl3_get_channel_id(SSL *s)
	{
	int ret = -1, ok;
	long n;
	const uint8_t *p;
	uint16_t extension_type, expected_extension_type;
	EC_GROUP* p256 = NULL;
	EC_KEY* key = NULL;
	EC_POINT* point = NULL;
	ECDSA_SIG sig;
	BIGNUM x, y;
	CBS encrypted_extensions, extension;

	if (s->state == SSL3_ST_SR_CHANNEL_ID_A && s->init_num == 0)
		{
		/* The first time that we're called we take the current
		 * handshake hash and store it. */
		EVP_MD_CTX md_ctx;
		unsigned int len;

		EVP_MD_CTX_init(&md_ctx);
		EVP_DigestInit_ex(&md_ctx, EVP_sha256(), NULL);
		if (!tls1_channel_id_hash(&md_ctx, s))
			return -1;
		len = sizeof(s->s3->tlsext_channel_id);
		EVP_DigestFinal(&md_ctx, s->s3->tlsext_channel_id, &len);
		EVP_MD_CTX_cleanup(&md_ctx);
		}

	n = s->method->ssl_get_message(s,
		SSL3_ST_SR_CHANNEL_ID_A,
		SSL3_ST_SR_CHANNEL_ID_B,
		SSL3_MT_ENCRYPTED_EXTENSIONS,
		2 + 2 + TLSEXT_CHANNEL_ID_SIZE,
		&ok);

	if (!ok)
		return((int)n);

	ssl3_finish_mac(s, (unsigned char*)s->init_buf->data, s->init_num + 4);

	/* s->state doesn't reflect whether ChangeCipherSpec has been received
	 * in this handshake, but s->s3->change_cipher_spec does (will be reset
	 * by ssl3_get_finished).
	 * TODO(davidben): Is this check now redundant with
	 * SSL3_FLAGS_EXPECT_CCS? */
	if (!s->s3->change_cipher_spec)
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_get_channel_id, SSL_R_GOT_CHANNEL_ID_BEFORE_A_CCS);
		return -1;
		}

	CBS_init(&encrypted_extensions, s->init_msg, n);

	/* EncryptedExtensions could include multiple extensions, but
	 * the only extension that could be negotiated is ChannelID,
	 * so there can only be one entry.
	 *
	 * The payload looks like:
	 *   uint16 extension_type
	 *   uint16 extension_len;
	 *   uint8 x[32];
	 *   uint8 y[32];
	 *   uint8 r[32];
	 *   uint8 s[32];
	 */
	expected_extension_type = TLSEXT_TYPE_channel_id;
	if (s->s3->tlsext_channel_id_new)
		expected_extension_type = TLSEXT_TYPE_channel_id_new;

	if (!CBS_get_u16(&encrypted_extensions, &extension_type) ||
		!CBS_get_u16_length_prefixed(&encrypted_extensions, &extension) ||
		CBS_len(&encrypted_extensions) != 0 ||
		extension_type != expected_extension_type ||
		CBS_len(&extension) != TLSEXT_CHANNEL_ID_SIZE)
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_get_channel_id, SSL_R_INVALID_MESSAGE);
		return -1;
		}

	p256 = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
	if (!p256)
		{
		OPENSSL_PUT_ERROR(SSL, ssl3_get_channel_id, SSL_R_NO_P256_SUPPORT);
		return -1;
		}

	BN_init(&x);
	BN_init(&y);
	sig.r = BN_new();
	sig.s = BN_new();

	p = CBS_data(&extension);
	if (BN_bin2bn(p +  0, 32, &x) == NULL ||
	    BN_bin2bn(p + 32, 32, &y) == NULL ||
	    BN_bin2bn(p + 64, 32, sig.r) == NULL ||
	    BN_bin2bn(p + 96, 32, sig.s) == NULL)
		goto err;

	point = EC_POINT_new(p256);
	if (!point ||
	    !EC_POINT_set_affine_coordinates_GFp(p256, point, &x, &y, NULL))
		goto err;

	key = EC_KEY_new();
	if (!key ||
	    !EC_KEY_set_group(key, p256) ||
	    !EC_KEY_set_public_key(key, point))
		goto err;

	/* We stored the handshake hash in |tlsext_channel_id| the first time
	 * that we were called. */
	switch (ECDSA_do_verify(s->s3->tlsext_channel_id, SHA256_DIGEST_LENGTH, &sig, key)) {
	case 1:
		break;
	case 0:
		OPENSSL_PUT_ERROR(SSL, ssl3_get_channel_id, SSL_R_CHANNEL_ID_SIGNATURE_INVALID);
		s->s3->tlsext_channel_id_valid = 0;
		goto err;
	default:
		s->s3->tlsext_channel_id_valid = 0;
		goto err;
	}

	memcpy(s->s3->tlsext_channel_id, p, 64);
	ret = 1;

err:
	BN_free(&x);
	BN_free(&y);
	BN_free(sig.r);
	BN_free(sig.s);
	if (key)
		EC_KEY_free(key);
	if (point)
		EC_POINT_free(point);
	if (p256)
		EC_GROUP_free(p256);
	return ret;
	}

