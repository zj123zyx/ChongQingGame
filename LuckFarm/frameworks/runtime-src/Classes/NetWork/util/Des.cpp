#include "Des.h"

#include <iostream>
#include <openssl/bio.h>
#include <openssl/evp.h>

int Des::encrypt( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key) 
{
	return des_ecb(inbuf, outbuf, inlen, key, 1);
}

int Des::decrypt( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key) 
{
	return des_ecb(inbuf, outbuf, inlen, key, 0);
}

int Des::des_ecb( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key, int enc)
{
	unsigned char iv[9] = {0};
    BIO *bio, *mbio, *cbio;
    unsigned char *dst;
    int outlen;

    mbio = BIO_new( BIO_s_mem( ) );
    cbio = BIO_new( BIO_f_cipher( ) );
    BIO_set_cipher( cbio , EVP_des_ecb( ) , key , iv , enc );

    bio = BIO_push( cbio , mbio );
    BIO_write( bio , inbuf , inlen );
    BIO_flush( bio );

    outlen = BIO_get_mem_data( mbio , (unsigned char **) & dst );
    * outbuf = ( unsigned char * ) malloc( outlen );
    memcpy( * outbuf , dst , outlen );
    BIO_free_all( bio );
	
    return outlen;
}