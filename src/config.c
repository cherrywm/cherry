#include "config.h"

cherry_config_t* run_config_file(lua_State *lua_state, const char *file_location) {
    // If file_location is null, run again with default config file location
    if (!file_location)
        return run_config_file(lua_state, default_config_file_location());

    // Assert that the corresponding file exists, exiting if it doesn't.
    assert_config_file_exists(file_location);

    // Loads Lua file, executes it. If there was an error, exit.
    int status = luaL_dofile(lua_state, file_location);
    if (status) {
        fprintf(stderr, "error loading config file: %s | status: %d\n", file_location, status);
        exit(EXIT_FAILURE);
    }

    // Get global config variables.
    lua_getglobal(lua_state, "fifo_location");
    lua_getglobal(lua_state, "desktop_count");

    // Retrieve variables from Lua stack, create config object.
    // Note that in the case of missing data, defaults are provided.

    cherry_config_t *config = (cherry_config_t*) malloc(sizeof(cherry_config_t));
    
    config->lua_state = lua_state;
    config->fifo_path = string_from_config(lua_state, "fifo_location", CHERRY_DEFAULT_FIFO_LOCATION);
    config->desktop_count = int_from_config(lua_state, "desktop_count", CHERRY_DEFAULT_DESKTOP_COUNT);
    config->border_width = int_from_config(lua_state, "border_width", CHERRY_DEFAULT_BORDER_WIDTH);
    config->window_gap = int_from_config(lua_state, "window_gap", CHERRY_DEFAULT_WINDOW_GAP);
    config->top_padding = int_from_config(lua_state, "top_padding", CHERRY_DEFAULT_TOP_PADDING);
    config->bottom_padding = int_from_config(lua_state, "bottom_padding", CHERRY_DEFAULT_BOTTOM_PADDING);
    config->right_padding = int_from_config(lua_state, "right_padding", CHERRY_DEFAULT_RIGHT_PADDING);
    config->left_padding = int_from_config(lua_state, "left_padding", CHERRY_DEFAULT_LEFT_PADDING);

    return config;
}

int int_from_config(lua_State *lua_state, const char *key, int default_value) {
    lua_getglobal(lua_state, key);
    
    return lua_isnoneornil(lua_state, -1) ? default_value : lua_tonumber(lua_state, -1);
}

int boolean_from_config(lua_State *lua_state, const char *key, int default_value) {
    lua_getglobal(lua_state, key);
    
    return lua_isnoneornil(lua_state, -1) ? default_value : lua_toboolean(lua_state, -1);
}

const char* string_from_config(lua_State *lua_state, const char *key, const char *default_value) {
    lua_getglobal(lua_state, key);
    
    return lua_isnoneornil(lua_state, -1) ? default_value : lua_tostring(lua_state, -1);
}

// Exits application if the file does not exist.
void assert_config_file_exists(const char *file_location) {
    if (access(file_location, F_OK) == -1) {
        fprintf(stderr, "config file: %s does not exist.\n", file_location);
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
