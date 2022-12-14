#pragma once
extern "C" {
#include "../../Lua/include/lua.h"
#include "../../Lua/include/lauxlib.h"
#include "../../Lua/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "../Lua/liblua54.a")
#endif
#include <vector>

class ScriptingManager
{
public:
	ScriptingManager();
	void Init();

	bool CheckLua(lua_State* L, int r);

	void AddScript(int id);
private:
	std::vector<class Script*> mScripts;

};
