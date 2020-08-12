#pragma once

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "win32-specific/zlib/include/zlib.h" 
class GzipUtil
{
public:
	GzipUtil(void);
	~GzipUtil(void);

	static int zcompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata);
	static int gzcompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata);

	static int gzdecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
	static int httpgzdecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
	static int zdecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);

	//OK
	static int gzipCompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata);
	static int gzipDecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
};

