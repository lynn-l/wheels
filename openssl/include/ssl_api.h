/*my_ssl_api.h*/
/*
 *This file implement some modules that the TLS server or client need sometimes.
 */

#ifndef _MT_SSL_API_H_
#define _MT_SSL_API_H_

#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/pkcs12.h>
#include <openssl/err.h>

#define SSL_OK								0

#define SSL_PARA_ERROR						-10
#define SSL_MALLOC_FAIL						-11
#define SSL_NO_API							-12

#define SSL_MAX_PASSPHRASE_REACH 			-100
#define SSL_MAX_CERT_REACH 					-101
#define SSL_MAX_KEY_REACH 					-102
#define SSL_MAX_CERTPATH_REACH 				-103
#define SSL_MAX_CRL_REACH 					-104
#define SSL_MAX_DOT1X_REACH 				-105

#define SSL_BAD_CERT 						-110
#define SSL_BAD_CRL 						-111
#define SSL_BAD_PKCS12 						-112
#define SSL_BAD_PKCS8 						-113
#define SSL_BAD_KEY 						-114

#define SSL_INVALID_PASSPHRASEID 			-120
#define SSL_INVALID_KEYSTATUS 				-121
#define SSL_INVALID_KEYID 					-122
#define SSL_INVALID_CERTID 					-123
#define SSL_INVALID_CERTPATHID 				-124
#define SSL_INVALID_CRLID 					-125
#define SSL_INVALID_SUBJECT 				-126
#define SSL_INVALID_ATTR					-127
#define SSL_INVALID_CERTPATH				-128
#define SSL_INVALID_DOT1XMETHOD				-129
#define SSL_INVALID_DOT1XMETHODCOMBINATION	-130
#define SSL_INVALID_DOT1XID					-131
#define SSL_INVALID_NETINTERFACE			-132

#define SSL_DEL_PASSPHRASE_FAIL 			-140
#define SSL_DEL_KEY_FAIL 					-141
#define SSL_DEL_CERT_FAIL 					-142
#define SSL_DEL_CERTPATH_FAIL 				-143

#define SSL_CREATE_CSR_FAIL 				-150
#define SSL_CREATE_CERTPATH_FAIL 			-151

#define SSL_UNSUPPORT_PUBKEYALG 			-160
#define SSL_UNSUPPORT_SIGNALG 				-161

#define SSL_KEY_MISMATCH 					-170
#define SSL_REFERENCE_EXIST					-171
#define SSL_NO_MATCH_PRIVKEY				-172
#define SSL_DECRY_FAIL 						-173
#define SSL_KEY_EXIST						-174

#define SSL_NO_PRIVKEY 						-180
#define SSL_MAX_TLSCERTPATH_REACH 			-181
#define SSL_OLD_CERTPATHID 					-182
#define SSL_NEW_CERTPATHID 					-183


SSL_CTX * my_ctx_new();

void my_locking_callback(int mode, int type, const char * file, int line);

void my_threadid_callback(CRYPTO_THREADID *id);

void INIT_SSL();

int parsePKCS8FromBuf(unsigned char *buf, int buflen, char *pass, int passlen, EVP_PKEY **priKey, EVP_PKEY **pubKey);

int saveKeyPKCS8(EVP_PKEY *pkey, char *pass, char *file);

#endif
