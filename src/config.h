#ifndef CHERRY_CONFIGH
    #define CHERRY_CONFIGH

    #define CHERRY_DEFAULT_FIFO_LOCATION "/tmp/cherry"
    #define CHERRY_DEFAULT_DESKTOP_COUNT 1
    #define CHERRY_DEFAULT_BORDER_WIDTH 1
    #define CHERRY_DEFAULT_WINDOW_GAP 20
    #define CHERRY_DEFAULT_TOP_PADDING 10
    #define CHERRY_DEFAULT_BOTTOM_PADDING 10
    #define CHERRY_DEFAULT_RIGHT_PADDING 10
    #define CHERRY_DEFAULT_LEFT_PADDING 10

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
        int border_width;
        int window_gap;
        int top_padding;
        int bottom_padding;
        int right_padding;
        int left_padding;
    } cherry_config_t;

    // Assumes Lua has already been setup.
    cherry_config_t* run_config_file(lua_State *lua_state, const char *file_location);

    // Helper functions.
    int int_from_config(lua_State *lua_state, const char *key, int default_value);
    int boolean_from_config(lua_State *lua_state, const char *key, int default_value);
    const char* string_from_config(lua_State *lua_state, const char *key, const char *default_value);

    // Defaults to $XDG_CONFIG_HOME/cherry/cherry.lua, or $HOME/.config/cherry/cherry.lua
    const char* default_config_file_location(void);

    // Application exits if config file does not exist.
    void assert_config_file_exists(const char *file_location);
#endif