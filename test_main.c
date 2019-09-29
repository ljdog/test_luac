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
static void stackDump (lua_State *L) {
	int i=lua_gettop(L);
	printf("-------- Stack Dump start--------\r\n" );
	while( i ) {
		int t = lua_type(L, i);
		switch (t) {
			case LUA_TSTRING:
				printf("%d:`%s' \r\n", i, lua_tostring(L, i));
				break;
			case LUA_TBOOLEAN:
				printf("%d: %s \r\n",i,lua_toboolean(L, i) ? "true" : "false");
				break;
			case LUA_TNUMBER:
				printf("%d: %g \r\n",  i, lua_tonumber(L, i));
				break;
			default: 
				printf("%d: %s \r\n", i, lua_typename(L, t)); 
				break;
		}
		i--;
	}
	printf("-------- Stack Dump end  --------\r\n" );
}

int main(int argc, const char *argv[])
{
	lua_State *L;
	if(NULL == (L = luaL_newstate()))
	{
		perror("luaL_newstate failed");
		return -1;
	}
	luaL_openlibs(L);
	if (1< 2){
		if(luaL_loadfile(L, "./test.lua"))
		{
			perror("loadfile failed");
			return -1;
		}
		stackDump(L);
		lua_pcall(L, 0, 0, 0); //一直这样用，但是一直不明白为什么一定要加这一句话
	
		lua_getglobal(L, "printmsg");
		lua_pcall(L, 0, 0, 0);
	}
	
	if (1<2){
		stackDump(L);
		lua_getglobal(L, "add");
		lua_pushnumber(L,10);
		lua_pushnumber(L,40.5);
		stackDump(L);

		if(lua_pcall(L, 2, 1, 0) != 0){
			printf("error calling");
		}
		printf("%f \r\n",lua_tonumber(L,-1));
	}
	if(1<2){
		
		lua_getglobal(L, "add_tb");
		lua_newtable(L);
		lua_pushnumber(L,10.10);
		lua_setfield(L,-2,"a");
		lua_pushnumber(L,20.12);
		lua_setfield(L,-2,"b");
		lua_pcall(L,1,1,0);
		float rst= lua_tonumber(L, -1);
		printf("%f \r\n",rst);
		
	}
	lua_close(L);
	return 0;
}
