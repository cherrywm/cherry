#ifndef CHERRY_CONFIGH
    #define CHERRY_CONFIGH
    #define CHERRY_DEFAULT_FIFO_LOCATION "/tmp/cherry"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

    typedef struct cherry_config_t {
        lua_State *lua_state;
        const char *fifo_path;
        int desktop_count;
    } cherry_config_t;

    // Assumes Lua has already been setup.
    cherry_config_t* run_config_file(lua_State *lua_state, const char *file_location);

    // Defaults to $XDG_CONFIG_HOME/cherry/cherry.lua, or $HOME/.config/cherry/cherry.lua
    const char* default_config_file_location(void);

    // Application exits if config file does not exist.
    void assert_config_file_exists(const char *file_name);
#endif