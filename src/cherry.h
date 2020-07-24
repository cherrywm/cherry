#include <xcb/xcb.h>
#include <lua.h>

typedef struct cherry_state_t {
    int keep_running;
    xcb_connection_t *connection;
    const xcb_setup_t *setup;
    xcb_screen_t *screen;
    lua_State *lua_state;
} cherry_state_t;