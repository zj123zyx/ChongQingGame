#ifndef _DES_H_
#define _DES_H_


class Des
{
public:
	static int des_ecb( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key, int enc);
	static int encrypt( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key);
	static int decrypt( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key);

};

#endif