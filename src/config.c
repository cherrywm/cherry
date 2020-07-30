#include "config.h"
#include "cherry.h"

#include <stdio.h>
#include <unistd.h>
#include <lauxlib.h>
#include <string.h>

const char *fifo_path;
int desktop_count;
int border_width;
int window_gap;
int top_padding;
int bottom_padding;
int right_padding;
int left_padding;

void run_config_file(const char *file_location) {
    if (!file_location) {
        run_config_file(default_config_file_location());
        return;
    }

    assert_config_file_exists(file_location);
    int status = luaL_dofile(lua_state, file_location);
    
    if (status) {
        fprintf(stderr, "error loading config file: %s | status: %d\n", file_location, status);
        exit(EXIT_FAILURE);
    }

    fifo_path = string_from_config("fifo_path", CHERRY_DEFAULT_FIFO_LOCATION);
    desktop_count = int_from_config("desktop_count", CHERRY_DEFAULT_DESKTOP_COUNT);
    border_width = int_from_config("border_width", CHERRY_DEFAULT_BORDER_WIDTH);
    window_gap = int_from_config("window_gap", CHERRY_DEFAULT_WINDOW_GAP);
    top_padding = int_from_config("top_padding", CHERRY_DEFAULT_TOP_PADDING);
    bottom_padding = int_from_config("bottom_padding", CHERRY_DEFAULT_BOTTOM_PADDING);
    right_padding = int_from_config("right_padding", CHERRY_DEFAULT_RIGHT_PADDING);
    left_padding = int_from_config("left_padding", CHERRY_DEFAULT_LEFT_PADDING);
}

int int_from_config(const char *key, int default_value) {
    lua_getglobal(lua_state, key);
    return lua_isnoneornil(lua_state, -1) ? default_value : lua_tonumber(lua_state, -1);
}

int boolean_from_config(const char *key, int default_value) {
    lua_getglobal(lua_state, key);
    return lua_isnoneornil(lua_state, -1) ? default_value : lua_toboolean(lua_state, -1);
}

const char* string_from_config(const char *key, const char *default_value) {
    lua_getglobal(lua_state, key);
    return lua_isnoneornil(lua_state, -1) ? default_value : lua_tostring(lua_state, -1);
}

void assert_config_file_exists(const char *file_location) {
    if (access(file_location, F_OK) == -1) {
        fprintf(stderr, "config file: %s does not exist.\n", file_location);
        exit(EXIT_FAILURE);
    }
}

const char* default_config_file_location(void) {
    char *xdg_config_home_env = getenv("XDG_CONFIG_HOME");
    
    return xdg_config_home_env
        ? strcat(xdg_config_home_env, "/cherry/cherry.lua")
        : strcat(getenv("HOME"), "/.config/cherry/cherry.lua");
}
