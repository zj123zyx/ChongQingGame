#ifndef _DATA_HELPER_H_
#define _DATA_HELPER_H_

#include <iostream>

class DataHelper
{
public:
	static int toByte(char c);

	static int stringToBytes(std::string s, char * * out, unsigned int inSize=0);

	//should unsigned char *, not char * bytes
	static char* bytesToString(unsigned char * bytes, unsigned int size);

	static char* hexStringToBytes(std::string s);

	static std::string bytesTohexString(char* bytes, int bytelength);
};
#endif
