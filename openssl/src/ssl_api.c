/*my_ssl_api.c*/
/*
 *This file implement some modules that the TLS server or client need sometimes.
 *NOTE:The version of openssl lib is 1.0.2o. Some APIs may be unavailable in diffrent vervion.
 */
#include "general_api.h"
#include "ssl_api.h"
#include <pthread.h>

pthread_mutex_t my_ssl_locks[CRYPTO_NUM_LOCKS];

SSL_CTX * my_ctx_new(const char *certFile, const char *keyFile)
{
	SSL_CTX *ctx = SSL_CTX_new(TLSv1_method());
	if(NULL == ctx) {
		DEBUG(LEVEL_ERROR, "SSL_CTX_new failed\n");
		return NULL;
	}

	if(NULL == certFile || NULL == keyFile)
		return ctx;
	
	if(SSL_CTX_use_certificate_file(ctx, certFile, SSL_FILETYPE_PEM) <= 0) {
		DEBUG(LEVEL_ERROR, "SSL_CTX_use_certificate failed\n");
		ERR_print_errors_fp(stderr);
		SSL_CTX_free(ctx);
		return NULL;
	}
	
	if(SSL_CTX_use_PrivateKey_file(ctx, keyFile, SSL_FILETYPE_PEM) <= 0) {
		DEBUG(LEVEL_ERROR, "SSL_CTX_use_PrivateKey failed\n");
		ERR_print_errors_fp(stderr);
		SSL_CTX_free(ctx);
		return NULL;
	}
	
	if(SSL_CTX_check_private_key(ctx) <= 0) {
		DEBUG(LEVEL_ERROR, "SSL_CTX_check_private_key failed\n");
		ERR_print_errors_fp(stderr);
		SSL_CTX_free(ctx);
		return NULL;
	}
		
	return ctx;
}

void my_locking_callback(int mode, int type, const char * file, int line)
{
	if(type < 0 || type >= CRYPTO_NUM_LOCKS)
		return;
	
	if (mode & CRYPTO_LOCK) {
		//DEBUG(LEVEL_DEBUG, "pthread_mutex_lock %d\n", type);
		pthread_mutex_lock(&my_ssl_locks[type - 1]);
	}
	else if (mode & CRYPTO_UNLOCK) {
		//DEBUG(LEVEL_DEBUG, "pthread_mutex_unlock %d\n", type);
		pthread_mutex_unlock(&my_ssl_locks[type - 1]);
	}

	return;
}

void my_threadid_callback(CRYPTO_THREADID *id)
{
	if(id) {
		id->ptr = NULL;
		id->val = pthread_self();
	}
	
	return;
}

void INIT_SSL()
{
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	OpenSSL_add_all_ciphers();
	SSL_load_error_strings();

	int i = 0;
	for(i=0; i<CRYPTO_NUM_LOCKS; i++)
		pthread_mutex_init(&my_ssl_locks[i], NULL);

	CRYPTO_set_locking_callback(my_locking_callback);
	CRYPTO_THREADID_set_callback(my_threadid_callback);
}

EVP_PKEY *getPubKeyFromPriKey(EVP_PKEY *priKey)
{
	if(NULL == priKey)
		return NULL;
	
	RSA *rsa = EVP_PKEY_get1_RSA(priKey);
	if(NULL == rsa) {
		DEBUG(LEVEL_ERROR, "EVP_PKEY_get1_RSA failed\n");
		return NULL;
	}
	
	EVP_PKEY *pubKey = EVP_PKEY_new();
    if(NULL == pubKey) {		
		DEBUG(LEVEL_ERROR, "EVP_PKEY_new failed\n");
		return NULL;
    }
    EVP_PKEY_set1_RSA(pubKey, rsa);

	return pubKey;
}

int parsePKCS8FromBuf(unsigned char *buf, int buflen, char *pass, int passlen, EVP_PKEY **priKey, EVP_PKEY **pubKey)
{
	if(NULL == buf || NULL == priKey)
		return SSL_PARA_ERROR;

	int ret = SSL_OK;
	X509_SIG *p8 = NULL;
	PKCS8_PRIV_KEY_INFO *pkcs8 = NULL;

	*priKey = NULL;
	if(NULL != pubKey)
		*pubKey = NULL;
	
	if(NULL != pass) {
		//PEM
		//p8 = PEM_read_bio_PKCS8(in, NULL, NULL, NULL);
		//DER
        p8 = d2i_X509_SIG(NULL, (const unsigned char **)&buf, buflen);
		if(NULL == p8) {
			DEBUG(LEVEL_ERROR, "d2i_X509_SIG error\n");
			ret = SSL_DECRY_FAIL;
			goto RETURN;
		}
		
		/*BIO *bp = BIO_new(BIO_s_file());
		BIO_set_fp(bp, stdout, BIO_NOCLOSE);
		X509_SIG_print(bp, p8);
		BIO_free(bp);*/
		
		pkcs8 = PKCS8_decrypt(p8, pass, passlen);
		if(NULL == pkcs8){
			DEBUG(LEVEL_ERROR, "PKCS8_decrypt error, pass = %s, len = %d\n", pass, passlen);
			ret = SSL_DECRY_FAIL;
			goto RETURN;
		}
	} else {
		pkcs8 = d2i_PKCS8_PRIV_KEY_INFO(NULL, (const unsigned char **)&buf, buflen);
		if(NULL == pkcs8){
			DEBUG(LEVEL_ERROR, "d2i_PKCS8_PRIV_KEY_INFO failed\n");
			ret = SSL_DECRY_FAIL;
			goto RETURN;
		}
	}
	
	*priKey = EVP_PKCS82PKEY(pkcs8);
	if(NULL == *priKey){
		DEBUG(LEVEL_ERROR, "EVP_PKCS82PKEY failed\n");
		ret = SSL_DECRY_FAIL;
		goto RETURN;
	}

	if(NULL != pubKey) {
		*pubKey = getPubKeyFromPriKey(*priKey);
		if(NULL == *pubKey) {		
			DEBUG(LEVEL_ERROR, "getPubKeyFromPriKey failed\n");
			ret = SSL_KEY_MISMATCH;
			goto RETURN;
	    }

		int ret = EVP_PKEY_cmp(*priKey, *pubKey);
		if(ret != 1) {
			DEBUG(LEVEL_ERROR, "EVP_PKEY_cmp failed, ret = %d\n", ret);
			ret = SSL_KEY_MISMATCH;
			goto RETURN;
		}		
	}

	if(pkcs8)
		PKCS8_PRIV_KEY_INFO_free(pkcs8);
	if(p8)
		X509_SIG_free(p8);
	return SSL_OK;
	
RETURN:
	if(pkcs8)
		PKCS8_PRIV_KEY_INFO_free(pkcs8);
	if(p8)
		X509_SIG_free(p8);
	if(*priKey) {
		EVP_PKEY_free(*priKey);
		*priKey = NULL;
	}
	if(pubKey && *pubKey) {
		EVP_PKEY_free(*pubKey);
		*pubKey = NULL;
	}

	return ret;
}

#define FORMAT_PEM 3
#define FORMAT_ASN1 1

int saveKeyPKCS8(EVP_PKEY *pkey, char *pass, char *file)
{
	if(NULL == pkey || NULL == file)
		return SSL_PARA_ERROR;

	int outformat = FORMAT_ASN1;//FORMAT_PEM
	
	PKCS8_PRIV_KEY_INFO *pkcs8 = EVP_PKEY2PKCS8(pkey);
	if(NULL == pkcs8) {
		DEBUG(LEVEL_ERROR, "EVP_PKEY2PKCS8 failed\n");
		return SSL_BAD_KEY;
	}
	
	BIO *out = BIO_new_file(file, "w+");
	if(NULL == out) {
		DEBUG(LEVEL_ERROR, "BIO_new_file failed\n");
		return SSL_BAD_KEY;
	}

	if(NULL == pass || strlen(pass) <= 0) {
		if (outformat == FORMAT_PEM)
			PEM_write_bio_PKCS8_PRIV_KEY_INFO(out, pkcs8);
		else if (outformat == FORMAT_ASN1)
			i2d_PKCS8_PRIV_KEY_INFO_bio(out, pkcs8);
	} else {
		EVP_CIPHER *cipher = EVP_get_cipherbyname((const char *)"RC4-MD5");
		if(NULL == cipher) {
			DEBUG(LEVEL_ERROR, "EVP_get_cipherbyname failed\n");
			BIO_free(out);
			return SSL_BAD_KEY;
		}
		X509_SIG *p8 = PKCS8_encrypt(NID_pbeWithMD5AndDES_CBC, cipher, pass, strlen(pass), NULL, 0, 2048, pkcs8);
		if(NULL == p8) {
			DEBUG(LEVEL_ERROR, "PKCS8_encrypt failed\n");
			BIO_free(out);
			return SSL_BAD_KEY;
		}

		if (outformat == FORMAT_PEM)
			PEM_write_bio_PKCS8(out, p8);
		else if (outformat == FORMAT_ASN1)
			i2d_PKCS8_bio(out, p8);
		
		X509_SIG_free(p8);
	}

	BIO_free(out);
	PKCS8_PRIV_KEY_INFO_free(pkcs8);
	
	return SSL_OK;
}

int parsePKCS12FromBuf(unsigned char *buf, int buflen, char *pass, EVP_PKEY **pkey, X509 **cert,STACK_OF(X509) **ocerts)
{
	int ret = SSL_OK;
	
	PKCS12 *p12 = d2i_PKCS12(NULL, (const unsigned char **)&buf, buflen);
	if(NULL == p12)
		return SSL_BAD_PKCS12;

	//mac verify
	if(PKCS12_verify_mac(p12, pass, strlen(pass)) != 1 && PKCS12_verify_mac(p12, "", 0) != 1 && PKCS12_verify_mac(p12, NULL, 0) != 1) {
		ret = SSL_BAD_PKCS12;
		goto RETURN;
	}
	
	EVP_PKEY *pkeyTmp = NULL;
	X509 *x = NULL;
	STACK_OF(X509) *ca = sk_X509_new_null();
	if(NULL == ca){
		DEBUG(LEVEL_ERROR, "sk_X509_new_null error\n");
		ret = SSL_DECRY_FAIL;
		goto RETURN;
	}
	
	if(PKCS12_parse(p12, pass, &pkeyTmp, &x, &ca) != 1) {
		DEBUG(LEVEL_ERROR, "onvif_parse_pk12 error\n");
        sk_X509_pop_free(ca, X509_free);
		ret = SSL_DECRY_FAIL;
		goto RETURN;
	}

	*pkey = pkeyTmp;
	*ocerts = ca;
	*cert = x;
	ret = SSL_OK;
	
RETURN:
	if(p12)
		PKCS12_free(p12);
	return ret;
}
