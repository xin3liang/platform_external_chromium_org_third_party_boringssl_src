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
 * ECC cipher suite support in OpenSSL originally developed by 
 * SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
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

#include <stdio.h>
#include <assert.h>

#include <openssl/engine.h>
#include <openssl/mem.h>
#include <openssl/obj.h>

#include "ssl_locl.h"

#define SSL_ENC_3DES_IDX	0
#define SSL_ENC_RC4_IDX		1
#define SSL_ENC_AES128_IDX	2
#define SSL_ENC_AES256_IDX	3
#define SSL_ENC_NUM_IDX		4


static const EVP_CIPHER *ssl_cipher_methods[SSL_ENC_NUM_IDX]= { 0 };

#define SSL_MD_MD5_IDX	0
#define SSL_MD_SHA1_IDX	1
#define SSL_MD_SHA256_IDX 2
#define SSL_MD_SHA384_IDX 3
/*Constant SSL_MAX_DIGEST equal to size of digests array should be 
 * defined in the
 * ssl_locl.h */
#define SSL_MD_NUM_IDX	SSL_MAX_DIGEST 
static const EVP_MD *ssl_digest_methods[SSL_MD_NUM_IDX] = { 0 };
static const int ssl_mac_pkey_id[SSL_MD_NUM_IDX]={
	EVP_PKEY_HMAC, EVP_PKEY_HMAC, EVP_PKEY_HMAC, EVP_PKEY_HMAC,
	};

static int ssl_mac_secret_size[SSL_MD_NUM_IDX] = { 0 };

static const int ssl_handshake_digest_flag[SSL_MD_NUM_IDX]={
	SSL_HANDSHAKE_MAC_MD5, SSL_HANDSHAKE_MAC_SHA,
	SSL_HANDSHAKE_MAC_SHA256, SSL_HANDSHAKE_MAC_SHA384,
	};

#define CIPHER_ADD	1
#define CIPHER_KILL	2
#define CIPHER_DEL	3
#define CIPHER_ORD	4
#define CIPHER_SPECIAL	5

typedef struct cipher_order_st
	{
	const SSL_CIPHER *cipher;
	int active;
	int dead;
	int in_group;
	struct cipher_order_st *next,*prev;
	} CIPHER_ORDER;

static const SSL_CIPHER cipher_aliases[]={
	{0,SSL_TXT_ALL,0,     0,0,0,0,0,0,0,0,0},

	/* "COMPLEMENTOFDEFAULT" (does *not* include ciphersuites not found in ALL!) */
	{0,SSL_TXT_CMPDEF,0,  SSL_kEDH|SSL_kEECDH,SSL_aNULL,0,0,0,0,0,0,0},

	/* key exchange aliases
	 * (some of those using only a single bit here combine
	 * multiple key exchange algs according to the RFCs,
	 * e.g. kEDH combines DHE_DSS and DHE_RSA) */
	{0,SSL_TXT_kRSA,0,    SSL_kRSA,  0,0,0,0,0,0,0,0},

	{0,SSL_TXT_kEDH,0,    SSL_kEDH,  0,0,0,0,0,0,0,0},
	{0,SSL_TXT_DH,0,      SSL_kEDH,0,0,0,0,0,0,0,0},

	{0,SSL_TXT_kEECDH,0,  SSL_kEECDH,0,0,0,0,0,0,0,0},
	{0,SSL_TXT_ECDH,0,    SSL_kEECDH,0,0,0,0,0,0,0,0},

        {0,SSL_TXT_kPSK,0,    SSL_kPSK,  0,0,0,0,0,0,0,0},

	/* server authentication aliases */
	{0,SSL_TXT_aRSA,0,    0,SSL_aRSA,  0,0,0,0,0,0,0},
	{0,SSL_TXT_aNULL,0,   0,SSL_aNULL, 0,0,0,0,0,0,0},
	{0,SSL_TXT_aECDSA,0,  0,SSL_aECDSA,0,0,0,0,0,0,0},
	{0,SSL_TXT_ECDSA,0,   0,SSL_aECDSA, 0,0,0,0,0,0,0},
        {0,SSL_TXT_aPSK,0,    0,SSL_aPSK,  0,0,0,0,0,0,0},

	/* aliases combining key exchange and server authentication */
	{0,SSL_TXT_EDH,0,     SSL_kEDH,~SSL_aNULL,0,0,0,0,0,0,0},
	{0,SSL_TXT_EECDH,0,   SSL_kEECDH,~SSL_aNULL,0,0,0,0,0,0,0},
	{0,SSL_TXT_RSA,0,     SSL_kRSA,SSL_aRSA,0,0,0,0,0,0,0},
	{0,SSL_TXT_ADH,0,     SSL_kEDH,SSL_aNULL,0,0,0,0,0,0,0},
	{0,SSL_TXT_AECDH,0,   SSL_kEECDH,SSL_aNULL,0,0,0,0,0,0,0},
        {0,SSL_TXT_PSK,0,     SSL_kPSK,SSL_aPSK,0,0,0,0,0,0,0},


	/* symmetric encryption aliases */
	{0,SSL_TXT_3DES,0,    0,0,SSL_3DES,  0,0,0,0,0,0},
	{0,SSL_TXT_RC4,0,     0,0,SSL_RC4,   0,0,0,0,0,0},
	{0,SSL_TXT_AES128,0,  0,0,SSL_AES128|SSL_AES128GCM,0,0,0,0,0,0},
	{0,SSL_TXT_AES256,0,  0,0,SSL_AES256|SSL_AES256GCM,0,0,0,0,0,0},
	{0,SSL_TXT_AES,0,     0,0,SSL_AES,0,0,0,0,0,0},
	{0,SSL_TXT_AES_GCM,0, 0,0,SSL_AES128GCM|SSL_AES256GCM,0,0,0,0,0,0},
	{0,SSL_TXT_CHACHA20   ,0,0,0,SSL_CHACHA20POLY1305,0,0,0,0,0,0},

	/* MAC aliases */	
	{0,SSL_TXT_MD5,0,     0,0,0,SSL_MD5,   0,0,0,0,0},
	{0,SSL_TXT_SHA1,0,    0,0,0,SSL_SHA1,  0,0,0,0,0},
	{0,SSL_TXT_SHA,0,     0,0,0,SSL_SHA1,  0,0,0,0,0},
	{0,SSL_TXT_SHA256,0,    0,0,0,SSL_SHA256,  0,0,0,0,0},
	{0,SSL_TXT_SHA384,0,    0,0,0,SSL_SHA384,  0,0,0,0,0},

	/* protocol version aliases */
	{0,SSL_TXT_SSLV3,0,   0,0,0,0,SSL_SSLV3, 0,0,0,0},
	{0,SSL_TXT_TLSV1,0,   0,0,0,0,SSL_TLSV1, 0,0,0,0},
	{0,SSL_TXT_TLSV1_2,0, 0,0,0,0,SSL_TLSV1_2, 0,0,0,0},

	/* strength classes */
	{0,SSL_TXT_MEDIUM,0,  0,0,0,0,0,SSL_MEDIUM,0,0,0},
	{0,SSL_TXT_HIGH,0,    0,0,0,0,0,SSL_HIGH,  0,0,0},
	/* FIPS 140-2 approved ciphersuite */
	{0,SSL_TXT_FIPS,0,    0,0,0,0,0,SSL_FIPS,  0,0,0},
	};

void ssl_load_ciphers(void)
	{
	ssl_cipher_methods[SSL_ENC_3DES_IDX]= EVP_des_ede3_cbc();
	ssl_cipher_methods[SSL_ENC_RC4_IDX]= EVP_rc4();
	ssl_cipher_methods[SSL_ENC_AES128_IDX]= EVP_aes_128_cbc();
	ssl_cipher_methods[SSL_ENC_AES256_IDX]= EVP_aes_256_cbc();

	ssl_digest_methods[SSL_MD_MD5_IDX]= EVP_md5();
	ssl_mac_secret_size[SSL_MD_MD5_IDX]= EVP_MD_size(EVP_md5());
	assert(ssl_mac_secret_size[SSL_MD_MD5_IDX] >= 0);
	ssl_digest_methods[SSL_MD_SHA1_IDX]=EVP_sha1();
	ssl_mac_secret_size[SSL_MD_SHA1_IDX]= EVP_MD_size(EVP_sha1());
	assert(ssl_mac_secret_size[SSL_MD_SHA1_IDX] >= 0);

	ssl_digest_methods[SSL_MD_SHA256_IDX]= EVP_sha256();
	ssl_mac_secret_size[SSL_MD_SHA256_IDX]= EVP_MD_size(EVP_sha256());
	ssl_digest_methods[SSL_MD_SHA384_IDX]= EVP_sha384();
	ssl_mac_secret_size[SSL_MD_SHA384_IDX]= EVP_MD_size(EVP_sha384());
	}

/* ssl_cipher_get_evp_aead sets |*aead| to point to the correct EVP_AEAD object
 * for |s->cipher|. It returns 1 on success and 0 on error. */
int ssl_cipher_get_evp_aead(const SSL_SESSION *s, const EVP_AEAD **aead)
	{
	const SSL_CIPHER *c = s->cipher;

	*aead = NULL;

	if (c == NULL)
		return 0;
	if ((c->algorithm2 & SSL_CIPHER_ALGORITHM2_AEAD) == 0 &&
	    (c->algorithm2 & SSL_CIPHER_ALGORITHM2_STATEFUL_AEAD) == 0)
		return 0;

#ifndef OPENSSL_NO_AES
	switch (c->algorithm_enc)
		{
	case SSL_AES128GCM:
		*aead = EVP_aead_aes_128_gcm();
		return 1;
	case SSL_AES256GCM:
		*aead = EVP_aead_aes_256_gcm();
		return 1;
	case SSL_CHACHA20POLY1305:
		*aead = EVP_aead_chacha20_poly1305();
		return 1;
	case SSL_RC4:
		if (c->algorithm_mac == SSL_MD5)
			*aead = EVP_aead_rc4_md5_tls();
		else
			return 0;
		return 1;
	}
#endif

	return 0;
	}

int ssl_cipher_get_evp(const SSL_SESSION *s, const EVP_CIPHER **enc,
	     const EVP_MD **md, int *mac_pkey_type, int *mac_secret_size)
	{
	int i;
	const SSL_CIPHER *c;

	c=s->cipher;
	if (c == NULL) return(0);

	/* This function doesn't deal with EVP_AEAD. See
	 * |ssl_cipher_get_aead_evp|. */
	if (c->algorithm2 & SSL_CIPHER_ALGORITHM2_AEAD)
		return(0);

	if ((enc == NULL) || (md == NULL)) return(0);

	switch (c->algorithm_enc)
		{
	case SSL_3DES:
		i=SSL_ENC_3DES_IDX;
		break;
	case SSL_RC4:
		i=SSL_ENC_RC4_IDX;
		break;
	case SSL_AES128:
		i=SSL_ENC_AES128_IDX;
		break;
	case SSL_AES256:
		i=SSL_ENC_AES256_IDX;
		break;
	default:
		i= -1;
		break;
		}

	if ((i < 0) || (i >= SSL_ENC_NUM_IDX))
		*enc=NULL;
	else
		*enc=ssl_cipher_methods[i];

	if (!ssl_cipher_get_mac(s, md, mac_pkey_type, mac_secret_size))
		return 0;

	if ((*enc != NULL) &&
	    (*md != NULL || (EVP_CIPHER_flags(*enc)&EVP_CIPH_FLAG_AEAD_CIPHER)) &&
	    (!mac_pkey_type||*mac_pkey_type != NID_undef))
		{
		if (s->ssl_version>>8 != TLS1_VERSION_MAJOR ||
		    s->ssl_version < TLS1_VERSION)
			return 1;

		/* TODO(fork): enable the stitched cipher modes. */
#if 0
		if	(c->algorithm_enc == SSL_RC4 &&
			 c->algorithm_mac == SSL_MD5 &&
			 (evp=EVP_get_cipherbyname("RC4-HMAC-MD5")))
			*enc = evp, *md = NULL;
		else if (c->algorithm_enc == SSL_AES128 &&
			 c->algorithm_mac == SSL_SHA1 &&
			 (evp=EVP_get_cipherbyname("AES-128-CBC-HMAC-SHA1")))
			*enc = evp, *md = NULL;
		else if (c->algorithm_enc == SSL_AES256 &&
			 c->algorithm_mac == SSL_SHA1 &&
			 (evp=EVP_get_cipherbyname("AES-256-CBC-HMAC-SHA1")))
			*enc = evp, *md = NULL;
#endif
		return(1);
		}
	else
		return(0);
	}

int ssl_cipher_get_mac(const SSL_SESSION *s, const EVP_MD **md, int *mac_pkey_type, int *mac_secret_size)
	{
	int i;
	const SSL_CIPHER *c;

	c=s->cipher;
	if (c == NULL) return(0);

	switch (c->algorithm_mac)
		{
	case SSL_MD5:
		i=SSL_MD_MD5_IDX;
		break;
	case SSL_SHA1:
		i=SSL_MD_SHA1_IDX;
		break;
	case SSL_SHA256:
		i=SSL_MD_SHA256_IDX;
		break;
	case SSL_SHA384:
		i=SSL_MD_SHA384_IDX;
		break;
	default:
		i= -1;
		break;
		}

	if ((i < 0) || (i >= SSL_MD_NUM_IDX))
		{
		*md=NULL; 
		if (mac_pkey_type!=NULL) *mac_pkey_type = NID_undef;
		if (mac_secret_size!=NULL) *mac_secret_size = 0;
		}
	else
		{
		*md=ssl_digest_methods[i];
		if (mac_pkey_type!=NULL) *mac_pkey_type = ssl_mac_pkey_id[i];
		if (mac_secret_size!=NULL) *mac_secret_size = ssl_mac_secret_size[i];
		}

	return 1;
	}

int ssl_get_handshake_digest(int idx, long *mask, const EVP_MD **md) 
{
	if (idx <0||idx>=SSL_MD_NUM_IDX) 
		{
		return 0;
		}
	*mask = ssl_handshake_digest_flag[idx];
	if (*mask)
		*md = ssl_digest_methods[idx];
	else
		*md = NULL;
	return 1;
}

#define ITEM_SEP(a) \
	(((a) == ':') || ((a) == ' ') || ((a) == ';') || ((a) == ','))

static void ll_append_tail(CIPHER_ORDER **head, CIPHER_ORDER *curr,
	     CIPHER_ORDER **tail)
	{
	if (curr == *tail) return;
	if (curr == *head)
		*head=curr->next;
	if (curr->prev != NULL)
		curr->prev->next=curr->next;
	if (curr->next != NULL)
		curr->next->prev=curr->prev;
	(*tail)->next=curr;
	curr->prev= *tail;
	curr->next=NULL;
	*tail=curr;
	}

static void ll_append_head(CIPHER_ORDER **head, CIPHER_ORDER *curr,
	     CIPHER_ORDER **tail)
	{
	if (curr == *head) return;
	if (curr == *tail)
		*tail=curr->prev;
	if (curr->next != NULL)
		curr->next->prev=curr->prev;
	if (curr->prev != NULL)
		curr->prev->next=curr->next;
	(*head)->prev=curr;
	curr->next= *head;
	curr->prev=NULL;
	*head=curr;
	}

static void ssl_cipher_get_disabled(unsigned long *mkey, unsigned long *auth, unsigned long *enc, unsigned long *mac, unsigned long *ssl)
	{
	*mkey = 0;
	*auth = 0;
	*enc = 0;
	*mac = 0;
	*ssl = 0;

	*enc |= (ssl_cipher_methods[SSL_ENC_3DES_IDX] == NULL) ? SSL_3DES:0;
	*enc |= (ssl_cipher_methods[SSL_ENC_RC4_IDX ] == NULL) ? SSL_RC4 :0;
	*enc |= (ssl_cipher_methods[SSL_ENC_AES128_IDX] == NULL) ? SSL_AES128:0;
	*enc |= (ssl_cipher_methods[SSL_ENC_AES256_IDX] == NULL) ? SSL_AES256:0;

	*mac |= (ssl_digest_methods[SSL_MD_MD5_IDX ] == NULL) ? SSL_MD5 :0;
	*mac |= (ssl_digest_methods[SSL_MD_SHA1_IDX] == NULL) ? SSL_SHA1:0;
	*mac |= (ssl_digest_methods[SSL_MD_SHA256_IDX] == NULL) ? SSL_SHA256:0;
	*mac |= (ssl_digest_methods[SSL_MD_SHA384_IDX] == NULL) ? SSL_SHA384:0;

	}

static void ssl_cipher_collect_ciphers(const SSL_METHOD *ssl_method,
                int num_of_ciphers,
                unsigned long disabled_mkey, unsigned long disabled_auth,
                unsigned long disabled_enc, unsigned long disabled_mac,
                unsigned long disabled_ssl,
                CIPHER_ORDER *co_list,
                CIPHER_ORDER **head_p, CIPHER_ORDER **tail_p)
	{
	int i, co_list_num;
	const SSL_CIPHER *c;

	/*
	 * We have num_of_ciphers descriptions compiled in, depending on the
	 * method selected (SSLv2 and/or SSLv3, TLSv1 etc).
	 * These will later be sorted in a linked list with at most num
	 * entries.
	 */

	/* Get the initial list of ciphers */
	co_list_num = 0;	/* actual count of ciphers */
	for (i = 0; i < num_of_ciphers; i++)
		{
		c = ssl_method->get_cipher(i);
		/* drop those that use any of that is not available */
		if ((c != NULL) && c->valid &&
		    !(c->algorithm_mkey & disabled_mkey) &&
		    !(c->algorithm_auth & disabled_auth) &&
		    !(c->algorithm_enc & disabled_enc) &&
		    !(c->algorithm_mac & disabled_mac) &&
		    !(c->algorithm_ssl & disabled_ssl))
			{
			co_list[co_list_num].cipher = c;
			co_list[co_list_num].next = NULL;
			co_list[co_list_num].prev = NULL;
			co_list[co_list_num].active = 0;
			co_list[co_list_num].in_group = 0;
			co_list_num++;
#ifdef KSSL_DEBUG
			printf("\t%d: %s %lx %lx %lx\n",i,c->name,c->id,c->algorithm_mkey,c->algorithm_auth);
#endif	/* KSSL_DEBUG */
			/*
			if (!sk_push(ca_list,(char *)c)) goto err;
			*/
			}
		}

	/*
	 * Prepare linked list from list entries
	 */	
	if (co_list_num > 0)
		{
		co_list[0].prev = NULL;

		if (co_list_num > 1)
			{
			co_list[0].next = &co_list[1];
			
			for (i = 1; i < co_list_num - 1; i++)
				{
				co_list[i].prev = &co_list[i - 1];
				co_list[i].next = &co_list[i + 1];
				}

			co_list[co_list_num - 1].prev = &co_list[co_list_num - 2];
			}
		
		co_list[co_list_num - 1].next = NULL;

		*head_p = &co_list[0];
		*tail_p = &co_list[co_list_num - 1];
		}
	}

static void ssl_cipher_collect_aliases(const SSL_CIPHER **ca_list,
                        int num_of_group_aliases,
                        unsigned long disabled_mkey, unsigned long disabled_auth,
                        unsigned long disabled_enc, unsigned long disabled_mac,
                        unsigned long disabled_ssl,
			CIPHER_ORDER *head)
	{
	CIPHER_ORDER *ciph_curr;
	const SSL_CIPHER **ca_curr;
	int i;
	unsigned long mask_mkey = ~disabled_mkey;
	unsigned long mask_auth = ~disabled_auth;
	unsigned long mask_enc = ~disabled_enc;
	unsigned long mask_mac = ~disabled_mac;
	unsigned long mask_ssl = ~disabled_ssl;

	/*
	 * First, add the real ciphers as already collected
	 */
	ciph_curr = head;
	ca_curr = ca_list;
	while (ciph_curr != NULL)
		{
		*ca_curr = ciph_curr->cipher;
		ca_curr++;
		ciph_curr = ciph_curr->next;
		}

	/*
	 * Now we add the available ones from the cipher_aliases[] table.
	 * They represent either one or more algorithms, some of which
	 * in any affected category must be supported (set in enabled_mask),
	 * or represent a cipher strength value (will be added in any case because algorithms=0).
	 */
	for (i = 0; i < num_of_group_aliases; i++)
		{
		unsigned long algorithm_mkey = cipher_aliases[i].algorithm_mkey;
		unsigned long algorithm_auth = cipher_aliases[i].algorithm_auth;
		unsigned long algorithm_enc = cipher_aliases[i].algorithm_enc;
		unsigned long algorithm_mac = cipher_aliases[i].algorithm_mac;
		unsigned long algorithm_ssl = cipher_aliases[i].algorithm_ssl;

		if (algorithm_mkey)
			if ((algorithm_mkey & mask_mkey) == 0)
				continue;
	
		if (algorithm_auth)
			if ((algorithm_auth & mask_auth) == 0)
				continue;
		
		if (algorithm_enc)
			if ((algorithm_enc & mask_enc) == 0)
				continue;
		
		if (algorithm_mac)
			if ((algorithm_mac & mask_mac) == 0)
				continue;
		
		if (algorithm_ssl)
			if ((algorithm_ssl & mask_ssl) == 0)
				continue;
		
		*ca_curr = cipher_aliases + i;
		ca_curr++;
		}

	*ca_curr = NULL;	/* end of list */
	}

static void ssl_cipher_apply_rule(unsigned long cipher_id,
                unsigned long alg_mkey, unsigned long alg_auth,
                unsigned long alg_enc, unsigned long alg_mac,
                unsigned long alg_ssl,
		unsigned long algo_strength,
		int rule, int strength_bits, int in_group,
		CIPHER_ORDER **head_p, CIPHER_ORDER **tail_p)
	{
	CIPHER_ORDER *head, *tail, *curr, *next, *last;
	const SSL_CIPHER *cp;
	int reverse = 0;

#ifdef CIPHER_DEBUG
	printf("Applying rule %d with %08lx/%08lx/%08lx/%08lx/%08lx %08lx (%d) in_group:%d\n",
		rule, alg_mkey, alg_auth, alg_enc, alg_mac, alg_ssl, algo_strength, strength_bits, in_group);
#endif

	if (rule == CIPHER_DEL)
		reverse = 1; /* needed to maintain sorting between currently deleted ciphers */

	head = *head_p;
	tail = *tail_p;

	if (reverse)
		{
		next = tail;
		last = head;
		}
	else
		{
		next = head;
		last = tail;
		}

	curr = NULL;
	for (;;)
		{
		if (curr == last) break;

		curr = next;

		if (curr == NULL) break;

		next = reverse ? curr->prev : curr->next;

		cp = curr->cipher;

		/*
		 * Selection criteria is either the value of strength_bits
		 * or the algorithms used.
		 */
		if (strength_bits >= 0)
			{
			if (strength_bits != cp->strength_bits)
				continue;
			}
		else
			{
#ifdef CIPHER_DEBUG
			printf("\nName: %s:\nAlgo = %08lx/%08lx/%08lx/%08lx/%08lx Algo_strength = %08lx\n", cp->name, cp->algorithm_mkey, cp->algorithm_auth, cp->algorithm_enc, cp->algorithm_mac, cp->algorithm_ssl, cp->algo_strength);
#endif
#ifdef OPENSSL_SSL_DEBUG_BROKEN_PROTOCOL
			if (cipher_id && cipher_id != cp->id)
				continue;
#endif
			if (alg_mkey && !(alg_mkey & cp->algorithm_mkey))
				continue;
			if (alg_auth && !(alg_auth & cp->algorithm_auth))
				continue;
			if (alg_enc && !(alg_enc & cp->algorithm_enc))
				continue;
			if (alg_mac && !(alg_mac & cp->algorithm_mac))
				continue;
			if (alg_ssl && !(alg_ssl & cp->algorithm_ssl))
				continue;
			if ((algo_strength & SSL_EXP_MASK) && !(algo_strength & SSL_EXP_MASK & cp->algo_strength))
				continue;
			if ((algo_strength & SSL_STRONG_MASK) && !(algo_strength & SSL_STRONG_MASK & cp->algo_strength))
				continue;
			}

#ifdef CIPHER_DEBUG
		printf("Action = %d\n", rule);
#endif

		/* add the cipher if it has not been added yet. */
		if (rule == CIPHER_ADD)
			{
			/* reverse == 0 */
			if (!curr->active)
				{
				ll_append_tail(&head, curr, &tail);
				curr->active = 1;
				curr->in_group = in_group;
				}
			}
		/* Move the added cipher to this location */
		else if (rule == CIPHER_ORD)
			{
			/* reverse == 0 */
			if (curr->active)
				{
				ll_append_tail(&head, curr, &tail);
				curr->in_group = 0;
				}
			}
		else if	(rule == CIPHER_DEL)
			{
			/* reverse == 1 */
			if (curr->active)
				{
				/* most recently deleted ciphersuites get best positions
				 * for any future CIPHER_ADD (note that the CIPHER_DEL loop
				 * works in reverse to maintain the order) */
				ll_append_head(&head, curr, &tail);
				curr->active = 0;
				curr->in_group = 0;
				}
			}
		else if (rule == CIPHER_KILL)
			{
			/* reverse == 0 */
			if (head == curr)
				head = curr->next;
			else
				curr->prev->next = curr->next;
			if (tail == curr)
				tail = curr->prev;
			curr->active = 0;
			if (curr->next != NULL)
				curr->next->prev = curr->prev;
			if (curr->prev != NULL)
				curr->prev->next = curr->next;
			curr->next = NULL;
			curr->prev = NULL;
			}
		}

	*head_p = head;
	*tail_p = tail;
	}

static int ssl_cipher_strength_sort(CIPHER_ORDER **head_p,
				    CIPHER_ORDER **tail_p)
	{
	int max_strength_bits, i, *number_uses;
	CIPHER_ORDER *curr;

	/*
	 * This routine sorts the ciphers with descending strength. The sorting
	 * must keep the pre-sorted sequence, so we apply the normal sorting
	 * routine as '+' movement to the end of the list.
	 */
	max_strength_bits = 0;
	curr = *head_p;
	while (curr != NULL)
		{
		if (curr->active &&
		    (curr->cipher->strength_bits > max_strength_bits))
		    max_strength_bits = curr->cipher->strength_bits;
		curr = curr->next;
		}

	number_uses = OPENSSL_malloc((max_strength_bits + 1) * sizeof(int));
	if (!number_uses)
		{
		OPENSSL_PUT_ERROR(SSL, ssl_cipher_strength_sort, ERR_R_MALLOC_FAILURE);
		return(0);
		}
	memset(number_uses, 0, (max_strength_bits + 1) * sizeof(int));

	/*
	 * Now find the strength_bits values actually used
	 */
	curr = *head_p;
	while (curr != NULL)
		{
		if (curr->active)
			number_uses[curr->cipher->strength_bits]++;
		curr = curr->next;
		}
	/*
	 * Go through the list of used strength_bits values in descending
	 * order.
	 */
	for (i = max_strength_bits; i >= 0; i--)
		if (number_uses[i] > 0)
			ssl_cipher_apply_rule(0, 0, 0, 0, 0, 0, 0, CIPHER_ORD, i, 0, head_p, tail_p);

	OPENSSL_free(number_uses);
	return(1);
	}

static int ssl_cipher_process_rulestr(const char *rule_str,
                CIPHER_ORDER **head_p, CIPHER_ORDER **tail_p,
                const SSL_CIPHER **ca_list)
	{
	unsigned long alg_mkey, alg_auth, alg_enc, alg_mac, alg_ssl, algo_strength;
	const char *l, *buf;
	int j, multi, found, rule, retval, ok, buflen, in_group = 0,
	    has_group = 0;
	unsigned long cipher_id = 0;
	char ch;

	retval = 1;
	l = rule_str;
	for (;;)
		{
		ch = *l;

		if (ch == '\0')
			break;		/* done */
		if (in_group)
			{
			if (ch == ']')
				{
				if (!in_group)
					{
					OPENSSL_PUT_ERROR(SSL, ssl_cipher_process_rulestr, SSL_R_UNEXPECTED_GROUP_CLOSE);
					retval = found = in_group = 0;
					break;
					}
				if (*tail_p)
					(*tail_p)->in_group = 0;
				in_group = 0;
				l++;
				continue;
				}
			if (ch == '|')
				{ rule = CIPHER_ADD; l++; continue; }
			else if (!(ch >= 'a' && ch <= 'z') &&
				 !(ch >= 'A' && ch <= 'Z') &&
				 !(ch >= '0' && ch <= '9'))
				{
				OPENSSL_PUT_ERROR(SSL, ssl_cipher_process_rulestr, SSL_R_UNEXPECTED_OPERATOR_IN_GROUP);
				retval = found = in_group = 0;
				break;
				}
			else
				rule = CIPHER_ADD;
			}
		else if (ch == '-')
			{ rule = CIPHER_DEL; l++; }
		else if (ch == '+')
			{ rule = CIPHER_ORD; l++; }
		else if (ch == '!' && has_group)
			{
			OPENSSL_PUT_ERROR(SSL, ssl_cipher_process_rulestr, SSL_R_MIXED_SPECIAL_OPERATOR_WITH_GROUPS);
			retval = found = in_group = 0;
			break;
			}
		else if (ch == '!')
			{ rule = CIPHER_KILL; l++; }
		else if (ch == '@' && has_group)
			{
			OPENSSL_PUT_ERROR(SSL, ssl_cipher_process_rulestr, SSL_R_MIXED_SPECIAL_OPERATOR_WITH_GROUPS);
			retval = found = in_group = 0;
			break;
			}
		else if (ch == '@')
			{ rule = CIPHER_SPECIAL; l++; }
		else if (ch == '[')
			{
			if (in_group)
				{
				OPENSSL_PUT_ERROR(SSL, ssl_cipher_process_rulestr, SSL_R_NESTED_GROUP);
				retval = found = in_group = 0;
				break;
				}
			in_group = 1;
			has_group = 1;
			l++;
			continue;
			}
		else
			{ rule = CIPHER_ADD; }

		if (ITEM_SEP(ch))
			{
			l++;
			continue;
			}

		alg_mkey = 0;
		alg_auth = 0;
		alg_enc = 0;
		alg_mac = 0;
		alg_ssl = 0;
		algo_strength = 0;

		for (;;)
			{
			ch = *l;
			buf = l;
			buflen = 0;
			while (	((ch >= 'A') && (ch <= 'Z')) ||
				((ch >= '0') && (ch <= '9')) ||
				((ch >= 'a') && (ch <= 'z')) ||
				 (ch == '-') || (ch == '.'))
				 {
				 ch = *(++l);
				 buflen++;
				 }

			if (buflen == 0)
				{
				/*
				 * We hit something we cannot deal with,
				 * it is no command or separator nor
				 * alphanumeric, so we call this an error.
				 */
				OPENSSL_PUT_ERROR(SSL, ssl_cipher_process_rulestr, SSL_R_INVALID_COMMAND);
				retval = found = in_group = 0;
				l++;
				break;
				}

			if (rule == CIPHER_SPECIAL)
				{
				found = 0; /* unused -- avoid compiler warning */
				break;	/* special treatment */
				}

			/* check for multi-part specification */
			if (ch == '+')
				{
				multi=1;
				l++;
				}
			else
				multi=0;

			/*
			 * Now search for the cipher alias in the ca_list. Be careful
			 * with the strncmp, because the "buflen" limitation
			 * will make the rule "ADH:SOME" and the cipher
			 * "ADH-MY-CIPHER" look like a match for buflen=3.
			 * So additionally check whether the cipher name found
			 * has the correct length. We can save a strlen() call:
			 * just checking for the '\0' at the right place is
			 * sufficient, we have to strncmp() anyway. (We cannot
			 * use strcmp(), because buf is not '\0' terminated.)
			 */
			j = found = 0;
			cipher_id = 0;
			while (ca_list[j])
				{
				if (!strncmp(buf, ca_list[j]->name, buflen) &&
				    (ca_list[j]->name[buflen] == '\0'))
					{
					found = 1;
					break;
					}
				else
					j++;
				}

			if (!found)
				break;	/* ignore this entry */

			if (ca_list[j]->algorithm_mkey)
				{
				if (alg_mkey)
					{
					alg_mkey &= ca_list[j]->algorithm_mkey;
					if (!alg_mkey) { found = 0; break; }
					}
				else
					alg_mkey = ca_list[j]->algorithm_mkey;
				}

			if (ca_list[j]->algorithm_auth)
				{
				if (alg_auth)
					{
					alg_auth &= ca_list[j]->algorithm_auth;
					if (!alg_auth) { found = 0; break; }
					}
				else
					alg_auth = ca_list[j]->algorithm_auth;
				}
			
			if (ca_list[j]->algorithm_enc)
				{
				if (alg_enc)
					{
					alg_enc &= ca_list[j]->algorithm_enc;
					if (!alg_enc) { found = 0; break; }
					}
				else
					alg_enc = ca_list[j]->algorithm_enc;
				}
						
			if (ca_list[j]->algorithm_mac)
				{
				if (alg_mac)
					{
					alg_mac &= ca_list[j]->algorithm_mac;
					if (!alg_mac) { found = 0; break; }
					}
				else
					alg_mac = ca_list[j]->algorithm_mac;
				}
			
			if (ca_list[j]->algo_strength & SSL_EXP_MASK)
				{
				if (algo_strength & SSL_EXP_MASK)
					{
					algo_strength &= (ca_list[j]->algo_strength & SSL_EXP_MASK) | ~SSL_EXP_MASK;
					if (!(algo_strength & SSL_EXP_MASK)) { found = 0; break; }
					}
				else
					algo_strength |= ca_list[j]->algo_strength & SSL_EXP_MASK;
				}

			if (ca_list[j]->algo_strength & SSL_STRONG_MASK)
				{
				if (algo_strength & SSL_STRONG_MASK)
					{
					algo_strength &= (ca_list[j]->algo_strength & SSL_STRONG_MASK) | ~SSL_STRONG_MASK;
					if (!(algo_strength & SSL_STRONG_MASK)) { found = 0; break; }
					}
				else
					algo_strength |= ca_list[j]->algo_strength & SSL_STRONG_MASK;
				}
			
			if (ca_list[j]->valid)
				{
				/* explicit ciphersuite found; its protocol version
				 * does not become part of the search pattern!*/

				cipher_id = ca_list[j]->id;
				}
			else
				{
				/* not an explicit ciphersuite; only in this case, the
				 * protocol version is considered part of the search pattern */

				if (ca_list[j]->algorithm_ssl)
					{
					if (alg_ssl)
						{
						alg_ssl &= ca_list[j]->algorithm_ssl;
						if (!alg_ssl) { found = 0; break; }
						}
					else
						alg_ssl = ca_list[j]->algorithm_ssl;
					}
				}
			
			if (!multi) break;
			}

		/*
		 * Ok, we have the rule, now apply it
		 */
		if (rule == CIPHER_SPECIAL)
			{	/* special command */
			ok = 0;
			if ((buflen == 8) &&
				!strncmp(buf, "STRENGTH", 8))
				ok = ssl_cipher_strength_sort(head_p, tail_p);
			else
				OPENSSL_PUT_ERROR(SSL, ssl_cipher_process_rulestr, SSL_R_INVALID_COMMAND);
			if (ok == 0)
				retval = 0;
			/*
			 * We do not support any "multi" options
			 * together with "@", so throw away the
			 * rest of the command, if any left, until
			 * end or ':' is found.
			 */
			while ((*l != '\0') && !ITEM_SEP(*l))
				l++;
			}
		else if (found)
			{
			ssl_cipher_apply_rule(cipher_id,
				alg_mkey, alg_auth, alg_enc, alg_mac, alg_ssl, algo_strength,
				rule, -1, in_group, head_p, tail_p);
			}
		else
			{
			while ((*l != '\0') && !ITEM_SEP(*l))
				l++;
			}
		if (*l == '\0') break; /* done */
		}

	if (in_group)
		{
		OPENSSL_PUT_ERROR(SSL, ssl_cipher_process_rulestr, SSL_R_INVALID_COMMAND);
		retval = 0;
		}

	return(retval);
	}


STACK_OF(SSL_CIPHER) *ssl_create_cipher_list(const SSL_METHOD *ssl_method,
		struct ssl_cipher_preference_list_st **cipher_list,
		STACK_OF(SSL_CIPHER) **cipher_list_by_id,
		const char *rule_str, CERT *c)
	{
	int ok, num_of_ciphers, num_of_alias_max, num_of_group_aliases;
	unsigned long disabled_mkey, disabled_auth, disabled_enc, disabled_mac, disabled_ssl;
	STACK_OF(SSL_CIPHER) *cipherstack = NULL, *tmp_cipher_list = NULL;
	const char *rule_p;
	CIPHER_ORDER *co_list = NULL, *head = NULL, *tail = NULL, *curr;
	const SSL_CIPHER **ca_list = NULL;
	unsigned char *in_group_flags = NULL;
	unsigned int num_in_group_flags = 0;
	struct ssl_cipher_preference_list_st *pref_list = NULL;

	/*
	 * Return with error if nothing to do.
	 */
	if (rule_str == NULL || cipher_list == NULL)
		return NULL;

	/*
	 * To reduce the work to do we only want to process the compiled
	 * in algorithms, so we first get the mask of disabled ciphers.
	 */
	ssl_cipher_get_disabled(&disabled_mkey, &disabled_auth, &disabled_enc, &disabled_mac, &disabled_ssl);

	/*
	 * Now we have to collect the available ciphers from the compiled
	 * in ciphers. We cannot get more than the number compiled in, so
	 * it is used for allocation.
	 */
	num_of_ciphers = ssl_method->num_ciphers();
#ifdef KSSL_DEBUG
	printf("ssl_create_cipher_list() for %d ciphers\n", num_of_ciphers);
#endif    /* KSSL_DEBUG */
	co_list = (CIPHER_ORDER *)OPENSSL_malloc(sizeof(CIPHER_ORDER) * num_of_ciphers);
	if (co_list == NULL)
		{
		OPENSSL_PUT_ERROR(SSL, ssl_create_cipher_list, ERR_R_MALLOC_FAILURE);
		return(NULL);	/* Failure */
		}

	ssl_cipher_collect_ciphers(ssl_method, num_of_ciphers,
	                           disabled_mkey, disabled_auth, disabled_enc, disabled_mac, disabled_ssl,
	                           co_list, &head, &tail);


	/* Now arrange all ciphers by preference:
	 * TODO(davidben): Compute this order once and copy it. */

	/* Everything else being equal, prefer ephemeral ECDH over other key exchange mechanisms */
	ssl_cipher_apply_rule(0, SSL_kEECDH, 0, 0, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
	ssl_cipher_apply_rule(0, SSL_kEECDH, 0, 0, 0, 0, 0, CIPHER_DEL, -1, 0, &head, &tail);

	/* Order the bulk ciphers. First the preferred AEAD ciphers. We prefer
	 * CHACHA20 unless there is hardware support for fast and constant-time
	 * AES_GCM. */
	if (EVP_has_aes_hardware())
		{
		ssl_cipher_apply_rule(0, 0, 0, SSL_AES256GCM, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
		ssl_cipher_apply_rule(0, 0, 0, SSL_AES128GCM, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
		ssl_cipher_apply_rule(0, 0, 0, SSL_CHACHA20POLY1305, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
		}
	else
		{
		ssl_cipher_apply_rule(0, 0, 0, SSL_CHACHA20POLY1305, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
		ssl_cipher_apply_rule(0, 0, 0, SSL_AES256GCM, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
		ssl_cipher_apply_rule(0, 0, 0, SSL_AES128GCM, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
		}

	/* Then the legacy non-AEAD ciphers: AES_256_CBC, AES-128_CBC,
	 * RC4_128_SHA, RC4_128_MD5, 3DES_EDE_CBC_SHA. */
        ssl_cipher_apply_rule(0, 0, 0, SSL_AES256, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
        ssl_cipher_apply_rule(0, 0, 0, SSL_AES128, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
        ssl_cipher_apply_rule(0, 0, 0, SSL_RC4, ~SSL_MD5, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
        ssl_cipher_apply_rule(0, 0, 0, SSL_RC4, SSL_MD5, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);
        ssl_cipher_apply_rule(0, 0, 0, SSL_3DES, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);

	/* Temporarily enable everything else for sorting */
	ssl_cipher_apply_rule(0, 0, 0, 0, 0, 0, 0, CIPHER_ADD, -1, 0, &head, &tail);

	/* Move ciphers without forward secrecy to the end. */
	ssl_cipher_apply_rule(0, ~(SSL_kEDH|SSL_kEECDH), 0, 0, 0, 0, 0, CIPHER_ORD, -1, 0, &head, &tail);

	/* Move anonymous ciphers to the end.  Usually, these will remain disabled.
	 * (For applications that allow them, they aren't too bad, but we prefer
	 * authenticated ciphers.)
	 * TODO(davidben): Remove them altogether? */
	ssl_cipher_apply_rule(0, 0, SSL_aNULL, 0, 0, 0, 0, CIPHER_ORD, -1, 0, &head, &tail);

	/* Now disable everything (maintaining the ordering!) */
	ssl_cipher_apply_rule(0, 0, 0, 0, 0, 0, 0, CIPHER_DEL, -1, 0, &head, &tail);

	/*
	 * We also need cipher aliases for selecting based on the rule_str.
	 * There might be two types of entries in the rule_str: 1) names
	 * of ciphers themselves 2) aliases for groups of ciphers.
	 * For 1) we need the available ciphers and for 2) the cipher
	 * groups of cipher_aliases added together in one list (otherwise
	 * we would be happy with just the cipher_aliases table).
	 */
	num_of_group_aliases = sizeof(cipher_aliases) / sizeof(SSL_CIPHER);
	num_of_alias_max = num_of_ciphers + num_of_group_aliases + 1;
	ca_list = OPENSSL_malloc(sizeof(SSL_CIPHER *) * num_of_alias_max);
	if (ca_list == NULL)
		{
		OPENSSL_free(co_list);
		OPENSSL_PUT_ERROR(SSL, ssl_create_cipher_list, ERR_R_MALLOC_FAILURE);
		return(NULL);	/* Failure */
		}
	ssl_cipher_collect_aliases(ca_list, num_of_group_aliases,
	                           disabled_mkey, disabled_auth, disabled_enc,
				   disabled_mac, disabled_ssl, head);

	/*
	 * If the rule_string begins with DEFAULT, apply the default rule
	 * before using the (possibly available) additional rules.
	 */
	ok = 1;
	rule_p = rule_str;
	if (strncmp(rule_str,"DEFAULT",7) == 0)
		{
		ok = ssl_cipher_process_rulestr(SSL_DEFAULT_CIPHER_LIST,
			&head, &tail, ca_list);
		rule_p += 7;
		if (*rule_p == ':')
			rule_p++;
		}

	if (ok && (strlen(rule_p) > 0))
		ok = ssl_cipher_process_rulestr(rule_p, &head, &tail, ca_list);

	OPENSSL_free((void *)ca_list);	/* Not needed anymore */

	if (!ok)
		goto err;
	
	/*
	 * Allocate new "cipherstack" for the result, return with error
	 * if we cannot get one.
	 */
	if ((cipherstack = sk_SSL_CIPHER_new_null()) == NULL)
		goto err;

	in_group_flags = OPENSSL_malloc(num_of_ciphers);
	if (!in_group_flags)
		goto err;
	/*
	 * The cipher selection for the list is done. The ciphers are added
	 * to the resulting precedence to the STACK_OF(SSL_CIPHER).
	 */
	for (curr = head; curr != NULL; curr = curr->next)
		{
		if (curr->active)
			{
			sk_SSL_CIPHER_push(cipherstack, curr->cipher);
			in_group_flags[num_in_group_flags++] = curr->in_group;
#ifdef CIPHER_DEBUG
			printf("<%s>\n",curr->cipher->name);
#endif
			}
		}
	OPENSSL_free(co_list);	/* Not needed any longer */
	co_list = NULL;

	tmp_cipher_list = sk_SSL_CIPHER_dup(cipherstack);
	if (tmp_cipher_list == NULL)
		goto err;
	pref_list = OPENSSL_malloc(sizeof(struct ssl_cipher_preference_list_st));
	if (!pref_list)
		goto err;
	pref_list->ciphers = cipherstack;
	pref_list->in_group_flags = OPENSSL_malloc(num_in_group_flags);
	if (!pref_list->in_group_flags)
		goto err;
	memcpy(pref_list->in_group_flags, in_group_flags, num_in_group_flags);
	OPENSSL_free(in_group_flags);
	in_group_flags = NULL;
	if (*cipher_list != NULL)
		ssl_cipher_preference_list_free(*cipher_list);
	*cipher_list = pref_list;
	pref_list = NULL;

	if (cipher_list_by_id != NULL)
		{
		if (*cipher_list_by_id != NULL)
			sk_SSL_CIPHER_free(*cipher_list_by_id);
		*cipher_list_by_id = tmp_cipher_list;
		tmp_cipher_list = NULL;
		(void)sk_SSL_CIPHER_set_cmp_func(*cipher_list_by_id,ssl_cipher_ptr_id_cmp);

		sk_SSL_CIPHER_sort(*cipher_list_by_id);
		}
	else
		{
		sk_SSL_CIPHER_free(tmp_cipher_list);
		tmp_cipher_list = NULL;
		}

	return(cipherstack);

err:
	if (co_list)
		OPENSSL_free(co_list);
	if (in_group_flags)
		OPENSSL_free(in_group_flags);
	if (cipherstack)
		sk_SSL_CIPHER_free(cipherstack);
	if (tmp_cipher_list)
		sk_SSL_CIPHER_free(tmp_cipher_list);
	if (pref_list && pref_list->in_group_flags)
		OPENSSL_free(pref_list->in_group_flags);
	if (pref_list)
		OPENSSL_free(pref_list);
	return NULL;
	}

const char *SSL_CIPHER_description(const SSL_CIPHER *cipher, char *buf, int len)
	{
	const char *ver;
	const char *kx,*au,*enc,*mac;
	unsigned long alg_mkey,alg_auth,alg_enc,alg_mac,alg_ssl;
#ifdef KSSL_DEBUG
	static const char *format="%-23s %s Kx=%-8s Au=%-4s Enc=%-9s Mac=%-4s AL=%lx/%lx/%lx/%lx/%lx\n";
#else
	static const char *format="%-23s %s Kx=%-8s Au=%-4s Enc=%-9s Mac=%-4s\n";
#endif /* KSSL_DEBUG */

	alg_mkey = cipher->algorithm_mkey;
	alg_auth = cipher->algorithm_auth;
	alg_enc = cipher->algorithm_enc;
	alg_mac = cipher->algorithm_mac;
	alg_ssl = cipher->algorithm_ssl;

	if (alg_ssl & SSL_SSLV3)
		ver="SSLv3";
	else if (alg_ssl & SSL_TLSV1_2)
		ver="TLSv1.2";
	else
		ver="unknown";

	switch (alg_mkey)
		{
	case SSL_kRSA:
		kx="RSA";
		break;
	case SSL_kEDH:
		kx="DH";
		break;
	case SSL_kEECDH:
		kx="ECDH";
		break;
	case SSL_kPSK:
		kx="PSK";
		break;
	default:
		kx="unknown";
		}

	switch (alg_auth)
		{
	case SSL_aRSA:
		au="RSA";
		break;
	case SSL_aNULL:
		au="None";
		break;
	case SSL_aECDSA:
		au="ECDSA";
		break;
	case SSL_aPSK:
		au="PSK";
		break;
	default:
		au="unknown";
		break;
		}

	switch (alg_enc)
		{
	case SSL_3DES:
		enc="3DES(168)";
		break;
	case SSL_RC4:
		enc="RC4(128)";
		break;
	case SSL_AES128:
		enc="AES(128)";
		break;
	case SSL_AES256:
		enc="AES(256)";
		break;
	case SSL_AES128GCM:
		enc="AESGCM(128)";
		break;
	case SSL_AES256GCM:
		enc="AESGCM(256)";
		break;
	case SSL_CHACHA20POLY1305:
		enc="ChaCha20-Poly1305";
		break;
	default:
		enc="unknown";
		break;
		}

	switch (alg_mac)
		{
	case SSL_MD5:
		mac="MD5";
		break;
	case SSL_SHA1:
		mac="SHA1";
		break;
	case SSL_SHA256:
		mac="SHA256";
		break;
	case SSL_SHA384:
		mac="SHA384";
		break;
	case SSL_AEAD:
		mac="AEAD";
		break;
	default:
		mac="unknown";
		break;
		}

	if (buf == NULL)
		{
		len=128;
		buf=OPENSSL_malloc(len);
		if (buf == NULL) return("OPENSSL_malloc Error");
		}
	else if (len < 128)
		return("Buffer too small");

#ifdef KSSL_DEBUG
	BIO_snprintf(buf,len,format,cipher->name,ver,kx,au,enc,mac,alg_mkey,alg_auth,alg_enc,alg_mac,alg_ssl);
#else
	BIO_snprintf(buf,len,format,cipher->name,ver,kx,au,enc,mac);
#endif /* KSSL_DEBUG */
	return(buf);
	}

/* Next three functions require non-null cipher */
int SSL_CIPHER_is_AES(const SSL_CIPHER *c)
	{
	return (c->algorithm_enc & SSL_AES) != 0;
	}

int SSL_CIPHER_has_MD5_HMAC(const SSL_CIPHER *c)
	{
	return (c->algorithm_mac & SSL_MD5) != 0;
	}

int SSL_CIPHER_is_AESGCM(const SSL_CIPHER *c)
	{
	return (c->algorithm_mac & (SSL_AES128GCM|SSL_AES256GCM)) != 0;
	}

int SSL_CIPHER_is_CHACHA20POLY1305(const SSL_CIPHER *c)
	{
	return (c->algorithm_enc & SSL_CHACHA20POLY1305) != 0;
	}

const char *SSL_CIPHER_get_version(const SSL_CIPHER *c)
	{
	int i;

	if (c == NULL) return("(NONE)");
	i=(int)(c->id>>24L);
	if (i == 3)
		return("TLSv1/SSLv3");
	else if (i == 2)
		return("SSLv2");
	else
		return("unknown");
	}

/* return the actual cipher being used */
const char *SSL_CIPHER_get_name(const SSL_CIPHER *c)
	{
	if (c != NULL)
		return(c->name);
	return("(NONE)");
	}

const char *SSL_CIPHER_get_kx_name(const SSL_CIPHER *cipher) {
  if (cipher == NULL) {
    return "";
  }

  switch (cipher->algorithm_mkey) {
    case SSL_kRSA:
      return SSL_TXT_RSA;
    case SSL_kEDH:
      switch (cipher->algorithm_auth) {
        case SSL_aRSA:
          return "DHE_" SSL_TXT_RSA;
        case SSL_aNULL:
          return SSL_TXT_DH "_anon";
        default:
          return "UNKNOWN";
      }
    case SSL_kEECDH:
      switch (cipher->algorithm_auth) {
        case SSL_aECDSA:
          return "ECDHE_" SSL_TXT_ECDSA;
        case SSL_aRSA:
          return "ECDHE_" SSL_TXT_RSA;
        case SSL_aNULL:
          return SSL_TXT_ECDH "_anon";
        default:
          return "UNKNOWN";
      }
    default:
      return "UNKNOWN";
  }
}

/* number of bits for symmetric cipher */
int SSL_CIPHER_get_bits(const SSL_CIPHER *c, int *alg_bits)
	{
	int ret=0;

	if (c != NULL)
		{
		if (alg_bits != NULL) *alg_bits = c->alg_bits;
		ret = c->strength_bits;
		}
	return(ret);
	}

unsigned long SSL_CIPHER_get_id(const SSL_CIPHER *c)
	{
	return c->id;
	}

void *SSL_COMP_get_compression_methods(void)
	{
	return NULL;
	}
int SSL_COMP_add_compression_method(int id, void *cm)
	{
	return 1;
	}

const char *SSL_COMP_get_name(const void *comp)
	{
	return NULL;
	}

/* For a cipher return the index corresponding to the certificate type */
int ssl_cipher_get_cert_index(const SSL_CIPHER *c)
	{
	unsigned long alg_a = c->algorithm_auth;

	if (alg_a & SSL_aECDSA)
		return SSL_PKEY_ECC;
	else if (alg_a & SSL_aRSA)
		return SSL_PKEY_RSA_ENC;
	return -1;
	}

/* ssl_cipher_has_server_public_key returns 1 if |cipher| involves a
 * server public key in the key exchange, sent in a server Certificate
 * message. Otherwise it returns 0. */
int ssl_cipher_has_server_public_key(const SSL_CIPHER *cipher)
	{
	/* Anonymous ciphers do not include a server certificate. */
	if (cipher->algorithm_auth & SSL_aNULL)
		return 0;
	/* Neither do PSK ciphers, except for RSA_PSK. */
	if ((cipher->algorithm_auth & SSL_aPSK) &&
		!(cipher->algorithm_mkey & SSL_kRSA))
		return 0;
	/* All other ciphers include it. */
	return 1;
	}

/* ssl_cipher_requires_server_key_exchange returns 1 if |cipher|
 * requires a ServerKeyExchange message. Otherwise it returns 0.
 *
 * Unlike ssl_cipher_has_server_public_key, some ciphers take optional
 * ServerKeyExchanges. PSK and RSA_PSK only use the ServerKeyExchange
 * to communicate a psk_identity_hint, so it is optional.
 *
 * Also, as implemented, the RSA key exchange takes an optional
 * ServerKeyExchange containing a signed ephemeral RSA encryption key.
 *
 * TODO(davidben): Can we remove the RSA one? This is a remnant of
 * RSA_EXPORT ciphers which required this (it was used to generate an
 * ephemeral 512-bit RSA encryption key), but it's allowed for all RSA
 * ciphers. */
int ssl_cipher_requires_server_key_exchange(const SSL_CIPHER *cipher)
	{
	/* Ephemeral Diffie-Hellman key exchanges require a
	 * ServerKeyExchange. */
	if (cipher->algorithm_mkey & SSL_kEDH ||
		cipher->algorithm_mkey & SSL_kEECDH)
		return 1;
	/* It is optional in all others. */
	return 0;
	}
