#include "config.h"

cherry_config_t run_config_file(lua_State *lua_state, const char *file_name) {
    // If file_name is null, run again with default config file location
    if (!file_name)
        return run_config_file(lua_state, default_config_file_location());

    // Assert that the corresponding file exists, exiting if it doesn't.
    assert_config_file_exists(file_name);

    // Loads Lua file, executes it. If there was an error, exit.
    int status = luaL_dofile(lua_state, file_name);
    if (status) {
        fprintf(stderr, "error loading config file: %s | status: %d", file_name, status);
        exit(EXIT_FAILURE);
    }

    // Get global config variables.
    lua_getglobal(lua_state, "fifo_path");
    lua_getglobal(lua_state, "desktop_count");

    // Retrieve variables from Lua stack, create config object.
    // Note that in the case of missing data, defaults are provided.
    struct cherry_config_t config = {
        lua_state,
        lua_isnoneornil(lua_state, -2) ? CHERRY_DEFAULT_FIFO_PATH : lua_tostring(lua_state, -2),
        lua_isnoneornil(lua_state, -1) ? 1 : lua_tonumber(lua_state, -1)
    };

    return config;
}

// Exits application if the file does not exist.
void assert_config_file_exists(const char *file_name) {
    if (access(file_name, F_OK) == -1) {
        fprintf(stderr, "config file: %s does not exist.", file_name);
        exit(EXIT_FAILURE);
    }
}

// Attempts to rely on XDG_CONFIG_HOME, otherwise HOME.
// In first case: $XDG_CONFIG_HOME/cherry/cherry.lua.
// Else: $HOME/.config/cherry/cherry.lua.
const char* default_config_file_location(void) {
    char *xdg_config_home_env = getenv("XDG_CONFIG_HOME");
    
    return xdg_config_home_env
        ? strcat(xdg_config_home_env, "/cherry/cherry.lua")
        : strcat(getenv("HOME"), "/.config/cherry/cherry.lua");
}
