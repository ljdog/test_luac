//加载lua头文件
#include <lauxlib.h>

static int add(lua_State *L) //int 为必须
{
    float a,b;
    a = lua_tonumber(L, 1);//第一个加数，函数的第一个参数总是索引1
    b = lua_tonumber(L, 2);
    lua_pushnumber(L, a + b);
    return 1;   //返回1表示该方法只有一个返回值
}

static const struct luaL_Reg mylib_funcs[] = {
    {"add_c",add}, //add_c  为导出到lua 用的函数名
    {NULL,NULL}
};

int luaopen_mylib (lua_State *L) // mylib so的名称
{
    luaL_newlib(L,mylib_funcs);
    return 1;
}

//gcc  -o my_addtest.o -c my_addtest.c ; gcc -O2 -bundle -undefined dynamic_lookup -o mylib.so my_addtest.o 