//
//  luabuf.c
//  IMDiors
//
//  Created by 李 战平 on 13-8-16.
//
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <endian.h>
#include <stdlib.h>

#define IOSTRING_META "diors.IOBuffer"

#define ntohll(x)	__DARWIN_OSSwapInt64(x)
#define htonll(x)	__DARWIN_OSSwapInt64(x)

#define checkiobuffer(L) \
(IOBuffer*) luaL_checkudata(L, 1, IOSTRING_META)

#define IOBUFFER_LEN 4096

typedef struct{
    size_t read_idx;
    size_t size;
    char buf[IOBUFFER_LEN];
} IOBuffer;

//创建一个新的IOBuffer
static int iobuffer_new(lua_State* L)
{
    IOBuffer* io = (IOBuffer*)lua_newuserdata(L, sizeof(IOBuffer));
    io->size = 0;
    io->read_idx = 0;
    luaL_getmetatable(L, IOSTRING_META);
    lua_setmetatable(L, -2);
     
    return 1;
}

//获得buffer的字符串
static int iobuffer_str(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    lua_pushlstring(L, io->buf, io->size);
    return 1;
}

static int iobuffer_write_short(lua_State* L){
    IOBuffer *io = checkiobuffer(L);
    short paraint = luaL_checkint(L,2);
    int writesize=sizeof(paraint);
    //判断当前设备int大小端存储方式：
    int para=htons(paraint);
    memcpy(io->buf + io->size,(char*)&para,writesize);
    io->size += writesize;
    return 0;
    
};

static int iobuffer_read_short(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    short num;
    int readsizes=sizeof(short);
    memcpy(&num,&io->buf[io->read_idx],readsizes);
    io->read_idx+=readsizes;
    //大小端
    short para=ntohs(num);
    lua_pushnumber(L,para);
    return 1;
}

//内部使用，不暴露
static void write_short(lua_State* L,short paraint){
    IOBuffer *io = checkiobuffer(L);
    int writesize=sizeof(paraint);
    //判断当前设备int大小端存储方式：
    int para=htons(paraint);
    memcpy(io->buf + io->size,(char*)&para,writesize);
    io->size += writesize;
    
}


static int iobuffer_write_int32(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    int paraint = luaL_checkint(L,2);
    int writesize=sizeof(paraint);
    //判断当前设备int大小端存储方式：
    int para=htonl(paraint);
    memcpy(io->buf + io->size,(char*)&para,writesize);
    io->size += writesize;
    return 0;
}

static int iobuffer_read_int32(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    int num;
    int readsizes=sizeof(int);
    memcpy(&num,&io->buf[io->read_idx],readsizes);
    io->read_idx+=readsizes;
    //大小端
    int para=ntohl(num);
    lua_pushnumber(L,para);
    return 1;
}

unsigned long long SwapInt64(unsigned long long arg) {
    union Swap {
        unsigned long long sv;
        unsigned int ul[2];
    } tmp, result;
    tmp.sv = arg;
    result.ul[0] = ntohl(tmp.ul[1]);
    result.ul[1] = ntohl(tmp.ul[0]);
    return result.sv;
}

static int iobuffer_write_int64(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    int64_t paraint = luaL_checknumber(L,2);
    //printf("aaa=%lld\n",paraint);
    int writesize=sizeof(paraint);
    //printf("bbb=%d\n",writesize);
    //int64_t para=htonll(paraint);
    int64_t para=SwapInt64(paraint);
    memcpy(io->buf + io->size,(char*)&para,writesize);
    io->size += writesize;
    return 0;
}

static int iobuffer_read_int64(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    int64_t num;
    int readsizes=sizeof(long long);
    memcpy(&num,&io->buf[io->read_idx],readsizes);
    io->read_idx+=readsizes;
    //大小端
    //int64_t para=ntohll(num);
    int64_t para=SwapInt64(num);
    lua_pushnumber(L,para);
    return 1;
}

static short _readShort(IOBuffer *io){
    short num;
    int readsizes=sizeof(short);
    memcpy(&num,&io->buf[io->read_idx],readsizes);
    io->read_idx+=readsizes;
    //大小端
    short para=ntohs(num);
    
	return para;
}

static int iobuffer_read_len_str(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    short readsizes=_readShort(io);
    printf("aaaa=%d",(int)readsizes);
    char* str;
    memcpy(&str,&io->buf[io->read_idx],readsizes);
    io->read_idx+=readsizes;
    lua_pushlstring(L, str, readsizes);
    return 1;
}

static int iobuffer_write_double(lua_State* L){
    IOBuffer *io = checkiobuffer(L);
    double paradouble = luaL_checknumber(L,2);
    int writesize=sizeof(paradouble);
    memcpy(io->buf + io->size,(char*)&paradouble,writesize);
    io->size += writesize;
    return 0;
};

static int iobuffer_write_float(lua_State* L){
    IOBuffer *io = checkiobuffer(L);
    float paraf = luaL_checknumber(L,2);
    int writesize=sizeof(paraf);
    memcpy(io->buf + io->size,(char*)&paraf,writesize);
    io->size += writesize;
    return 0;
};


static int iobuffer_write_str(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    size_t size;
    const char* str = luaL_checklstring(L, 2, &size);
    if(io->size + size > IOBUFFER_LEN){
        luaL_error(L, "Out of range");
    }
    memcpy(io->buf + io->size, str, size);
    io->size += size;
    return 0;
}

static int iobuffer_write_len_str(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    size_t size;
    const char* str = luaL_checklstring(L, 2, &size);
    
    //接着写字符串
    if(io->size + size > IOBUFFER_LEN){
        luaL_error(L, "Out of range");
    }
    
    //写入字符串长度
    write_short(L,size);
    
    memcpy(io->buf + io->size, str, size);
    io->size += size;
    return 0;
}

static int iobuffer_len(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    lua_pushinteger(L, io->size);
    return 1;
}

static int iobuffer_clear(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    io->size = 0;
    io->read_idx = 0;
    return 0;
}

static int iobuffer_free(lua_State* L)
{
    printf("释放");
    IOBuffer *io = checkiobuffer(L);
    if (!io) {
         return 0;
    }
    io=NULL;
    return 0;
}

//TODO 添加的方法
static int iobuffer_read_buffer(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    // 读取长度
    int readsizes = luaL_checknumber(L,2);
    
    if(io->size < readsizes){
        printf("rang of size");
        return 0;
    }
    
    lua_pushlstring(L, io->buf, readsizes);

    // 移位
    int remainLen = io->size - readsizes;
    int i=0;
    for(i=0;i<remainLen;i++){
        io->buf[i] = io->buf[i+readsizes];
    }
    
    io->size = remainLen;
    io->read_idx = 0;
    return 1;
}
static int iobuffer_write_buffer(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    size_t size;
    const char* str = luaL_checklstring(L, 2, &size);
    if(io->size + size > IOBUFFER_LEN){
        luaL_error(L, "iobuffer_write_buffer Out of range");
    }
    memcpy(io->buf + io->size, str, size);
    io->size += size;
    return 0;
}
static int iobuffer_read_int32_nopos(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    int num;
    int readsizes=sizeof(int);
    memcpy(&num,&io->buf[io->read_idx],readsizes);
    //大小端
    int para=ntohl(num);
    lua_pushnumber(L,para);
    return 1;
}
static int iobuffer_read_short_nopos(lua_State* L)
{
    IOBuffer *io = checkiobuffer(L);
    short num;
    int readsizes=sizeof(short);
    memcpy(&num,&io->buf[io->read_idx],readsizes);

    //大小端
    short para=ntohs(num);
    lua_pushnumber(L,para);
    return 1;
}




static luaL_Reg iobuffer_f [] = {
    {"iobuffer_new", iobuffer_new},
    {NULL, NULL}
};

static luaL_Reg iobuffer_m [] = {
    {"iobuffer_str", iobuffer_str},
    {"iobuffer_write_str", iobuffer_write_str},
    {"iobuffer_write_len_str", iobuffer_write_len_str},
    {"iobuffer_clear", iobuffer_clear},
    {"iobuffer_len", iobuffer_len},
    {"iobuffer_write_int32", iobuffer_write_int32},
    {"iobuffer_write_short", iobuffer_write_short},
    {"iobuffer_write_double", iobuffer_write_double},
    {"iobuffer_write_float", iobuffer_write_float},
    {"iobuffer_read_short", iobuffer_read_short},
    {"iobuffer_read_int32", iobuffer_read_int32},
    {"iobuffer_write_int64", iobuffer_write_int64},
    {"iobuffer_read_len_str", iobuffer_read_len_str},
    {"iobuffer_free", iobuffer_free},
    {"iobuffer_read_buffer", iobuffer_read_buffer},
    {"iobuffer_read_int32_nopos", iobuffer_read_int32_nopos},
    {"iobuffer_write_buffer", iobuffer_write_buffer},
    {"iobuffer_read_short_nopos", iobuffer_read_short_nopos},
    {NULL, NULL}
};



int luaopen_iobuffer (lua_State *L)
{
    luaL_newmetatable(L, IOSTRING_META);
    /* 元表.--index=元表 */
    lua_pushvalue(L, -1);
    /* 复制元表 */
    lua_setfield(L, -2, "__index");
    
    //lua_pushstring(L, "__gc");
    //lua_pushcfunction(L, iobuffer_free);
    //lua_settable(L, -3);
    
    luaL_register(L, NULL, iobuffer_m);
    luaL_register(L, "luabuf", iobuffer_f);
    return 1;
}
