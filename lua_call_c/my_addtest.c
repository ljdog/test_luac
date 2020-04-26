//加载lua头文件
#include <lauxlib.h>
#include <string.h>

// Lua可以调用C函数的能力将极大的提高Lua的可扩展性和可用性。对于有些和操作系统相关的功能，或者是对效率要求较高的模块，我们完全可以通过C函数来实现，之后再通过Lua调用指定的C函数。
//对于那些可被Lua调用的C函数而言，其接口必须遵循Lua要求的形式，

// 即typedef int (*lua_CFunction)(lua_State* L)。

//简单说明一下，该函数类型仅仅包含一个表示Lua环境的指针作为其唯一的参数，实现者可以通过该指针进一步获取Lua代码中实际传入的参数。返回值是整型，表示该C函数将返回给Lua代码的返回值数量，如果没有返回值，则return 0即可。需要说明的是，C函数无法直接将真正的返回值返回给Lua代码，而是通过虚拟栈来传递Lua代码和C函数之间的调用参数和返回值的。这里我们将介绍两种Lua调用C函数的规则
// 原文链接：https://blog.csdn.net/xiaoluoshan/java/article/details/79501126

static int add(lua_State *L) //int 为必须
{
    float a,b;
    a = lua_tonumber(L, 1);//第一个加数，函数的第一个参数总是索引1
    b = lua_tonumber(L, 2);
    lua_pushnumber(L, a + b);
    return 1;   //返回1表示该方法只有一个返回值
}
static int printf_str(lua_State *L)
{
    const char *m = lua_tolstring(L,-1,NULL);
    lua_pushlstring(L,m,strlen(m));
    return 1;
}

//luaL_Reg结构体的第一个字段为字符串，在注册时用于通知Lua该函数的名字。
//第一个字段为C函数指针。
//结构体数组中的最后一个元素的两个字段均为NULL，用于提示Lua注册函数已经到达数组的末尾。

static const struct luaL_Reg mylib_funcs[] = {
    {"add_c",add}, //add_c  为导出到lua 用的函数名
    {"printf_str",printf_str},
    {NULL,NULL}
};

//该C库的唯一入口函数。其函数签名等同于上面的注册函数。见如下几点说明：
//1. 我们可以将该函数简单的理解为模块的工厂函数。
//2. 其函数名必须为luaopen_xxx，其中xxx表示library名称。Lua代码require "xxx"需要与之对应。
//3. 在luaL_register的调用中，其第一个字符串参数为模块名"xxx"，第二个参数为待注册函数的数组。
//4. 需要强调的是，所有需要用到"xxx"的代码，不论C还是Lua，都必须保持一致，这是Lua的约定，
//   否则将无法调用。
int luaopen_mylib (lua_State *L) // mylib so的名称
{
    luaL_newlib(L,mylib_funcs);
    return 1;
}

//gcc  -o my_addtest.o -c my_addtest.c ; gcc -O2 -bundle -undefined dynamic_lookup -o mylib.so my_addtest.o 