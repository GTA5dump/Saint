#pragma once

#include <iostream>
#include <lua/lua.hpp>
#include "Logger.hpp"

namespace Saint {

    const char* lua_path;
    bool lua_loaded = false;

    void LogMessage(const std::string& message) {
        getLogger()->Info(message.c_str());
    }

    int LuaLogMessage(lua_State* L) {
        const char* message = lua_tostring(L, -1);
        LogMessage(message);
        return 0;
    }
    void load_lua() {
        if (lua_loaded) {
            lua_State* L = luaL_newstate();
            luaL_openlibs(L);

            lua_pushcfunction(L, LuaLogMessage);
            lua_setglobal(L, "Log");

            const char* luaFilePath = lua_path;

            if (luaL_dofile(L, luaFilePath) != LUA_OK) {
                const char* errorMsg = lua_tostring(L, -1);
                getLogger()->Error(errorMsg);
            }

            lua_close(L);

        }

    }
   
}
