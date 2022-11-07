#include <iostream>

#include "MyGE.h"

extern "C" {
#include "../Lua/include/lua.h"
#include "../Lua/include/lauxlib.h"
#include "../Lua/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "../Lua/liblua54.a")
#endif

int main() {
    //Command we want to do
	std::string command = "a = 7 + 11";
	lua_State* L = luaL_newstate();

	MyGE ge = MyGE();
	ge.run();
	return 0;
}