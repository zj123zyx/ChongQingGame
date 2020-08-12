#ifndef _DMSUTIL_H
#define _DMSUTIL_H

/* F, G, H and I are basic MD5 functions. */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
/* ROTATE_LEFT rotates x left n bits. */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
/*
* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
* Rotation is separate from addition to prevent recomputation.
*/
#define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + (unsigned int)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + (unsigned int)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + (unsigned int)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + (unsigned int)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

class CppMd5
{
public:
	/*MD5 context*/
	typedef struct MD5_CTX_S{
		unsigned int state[4];
		unsigned int count[2];
		char buffer[64];
	}MD5_CTX;

	static unsigned char digest[16];
	/*MD5 initialization*/
	static void MD5Init(MD5_CTX *);
	/*MD5 block update operation*/
	static void MD5Update(MD5_CTX *, unsigned char *, unsigned int);
	/*Ends an MD5 message-digest operation*/
	static void MD5Final(unsigned char [16], MD5_CTX *);
	/*MD5 padding*/
	static void   __md5_Pad (MD5_CTX *);
	/*MD5 basic transformation*/
	static void   __md5_Transform (unsigned int [4], unsigned char [64]);
	static void EncryptMD5(unsigned char *output, unsigned char *input);
	static void EncryptMD5str(char *output, unsigned char *input, int len);

};

#endif