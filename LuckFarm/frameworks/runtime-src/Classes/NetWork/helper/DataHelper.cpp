#include "DataHelper.h"

int DataHelper::toByte(char c)
{
	if (c >= '0' && c <= '9') return (c - '0');
    if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
	return 0;
}

int DataHelper::stringToBytes(std::string input, char * * out, unsigned int inSize)
{         
    int size;
    if(inSize == 0)
    {
        size = input.length()/2;
    }
    else
    {
        size = inSize/2;
    }
        
	char* ret = new char[size];
    *out = new char[size];
	int i;
    for (i = 0 ; i < size; i++) {
		int pos = i*2;
        ret[i] = (char) ((toByte(input.at(pos)) << 4) | toByte(input.at(pos+1)));
    }
	memcpy( * out , ret , size);
	delete []ret;
	return size;
}

char* DataHelper::bytesToString(unsigned char * bytes, unsigned int size)
{
	char* dst = new char[size*2 + 1];
	for (int i = 0; i < size; i++) {		
		sprintf(&dst[i*2], "%02X", bytes[i]);
	}
	return dst;
}

char* DataHelper::hexStringToBytes(std::string s)
{         
    int sz = s.length();
    char *ret = new char[sz/2];
    for (int i=0 ; i <sz ; i+=2) {
        ret[i/2] = (char) ((toByte(s.at(i)) << 4) | toByte(s.at(i+1)));
    }
	return ret;
}

std::string DataHelper::bytesTohexString(char* bytes, int bytelength)
{
     std::string str("");
     std::string str2("0123456789abcdef"); 
     for (int i=0;i<bytelength;i++) {
         int b;
		 b = 0x0f&(bytes[i]>>4);
		 char s1 = str2.at(b);
		 str.append(1,str2.at(b));    
		 b = 0x0f & bytes[i];
		 str.append(1,str2.at(b));
		 char s2 = str2.at(b);
    }
    return str;
}
