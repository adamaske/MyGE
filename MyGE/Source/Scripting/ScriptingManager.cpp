#include "pch.h"
#include "ScriptingManager.h"

#include "../Script.h"



ScriptingManager::ScriptingManager()
{
	Init();
}

void ScriptingManager::Init()
{
	//Find all the scripts and load them
    //Command we want to do
    std::string command = "a = 7 + 11 + math.sin(23.7)";
    //Instance of lua machine
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    //CheckLua checks for "syntax" errors
    if (CheckLua(L, luaL_dofile(L, "Resources/Scripts/LuaExample.lua"))) {
        //Try to find a AddStuff thing, if its found puts it on top of the stack
        lua_getglobal(L, "AddStuff");
        //Chcecks if the top of the stacks is a function
        if (lua_isfunction(L, -1)) {
            //We want to use the AddStuff function, which takes two numbers
            //We push them onto the stack
            lua_pushnumber(L, 3.4f);
            lua_pushnumber(L, 3.4f);
            //Check lua chekfs if its a valid call or not
            //lua_pcall takes in the context L, how many arguments we are passing, how many do we expcet in return, error(dont mind now) 
            //and executes the function 
            if (CheckLua(L, lua_pcall(L, 2, 1, 0))) {               //The return of the pcall function should now be on top of the stack
                std::cout << "MyGE : Called in Lua the functio 'AddStuff(3.4, 3.4)', got " << (float)lua_tonumber(L, -1) << std::endl;
            }
        }
    
        //Is there a 'object' in this file
        lua_getglobal(L, "object");
        //the object is a table of variables, check is table
        if (lua_istable(L, -1)) {
            //This pushes the string "ObjectID" onto the stack
            lua_pushstring(L, "ObjectID");
            //Because "ObjectID" now lies on top of the "object", calling gettable
            //Gettable looks at the l machine, and finds the "object"(-2 because -1 is "ObjectID") and then uses the "ObjectID" as a key
            lua_gettable(L, -2);
            //This now returned whatever it was
            std::cout << "MyGE : ObjectId Lua print : " << lua_tonumber(L, -1) << std::endl;
            //The stack now has the value which was retrived from the table on top, to proceed we want to pop it so we can do otherstuff with the top element
            lua_pop(L, 1);
            //This can now be repeated
        }
    
        lua_getglobal(L, "ScriptID");
        if (lua_isstring(L, -1)) {
            std::string scriptID = (std::string)lua_tostring(L, -1);
            std::cout << "ScriptingManager: Found script id, creating Script!" << std::endl;
            AddScript(std::stoi(scriptID));
        }
    }
    
    lua_close(L);
    return;
}

void ScriptingManager::AddScript(int id) {
    Script script = Script(id, "");
    mScripts.push_back(&script);
}
bool ScriptingManager::CheckLua(lua_State* L, int r) {
    if (r != LUA_OK) {
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}
