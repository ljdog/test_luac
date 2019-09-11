// #include <stdio.h>
// #include <unistd.h>
 
// #include "lua.h"
// #include "lauxlib.h"
// #include "lualib.h"

// extern "C" {
//     #include "lua.h"
//     #include "lauxlib.h"
//     #include "lualib.h"
// }

#include <stdlib.h>
#include <stdint.h>

#include "lua.h"
#include "lauxlib.h"
 
int main(int argc, const char *argv[])
{
	lua_State *L;
	if(NULL == (L = luaL_newstate()))
	{
		perror("luaL_newstate failed");
		return -1;
	}
	luaL_openlibs(L);
	if(luaL_loadfile(L, "./test.lua"))
	{
		perror("loadfile failed");
		return -1;
	}
	lua_pcall(L, 0, 0, 0); //一直这样用，但是一直不明白为什么一定要加这一句话
 
	lua_getglobal(L, "printmsg");
	lua_pcall(L, 0, 0, 0);
 
	lua_close(L);
	printf("is ok"); 
	return 0;

}
