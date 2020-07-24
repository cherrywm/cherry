#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "loop.h"
#include <lauxlib.h>
#include <lualib.h>

// I immensely dislike storing global state :(
static struct cherry_state_t *state;

void stop_running(int _unused) {
    state->keep_running = 0;
    (void)(_unused);
}

int main(void) {
    // Establish connection to DISPLAY X server, first available screen.
    // TODO: Support multple monitors.
    xcb_connection_t *connection = xcb_connect(NULL, NULL);
    
    // Check if we failed to establish a connection to the specified X server.
    if (xcb_connection_has_error(connection)) {
        // TODO: syslog possibly?
        fputs("Failure to open display!", stderr);
        return EXIT_FAILURE;
    }

    const xcb_setup_t *setup = xcb_get_setup(connection); // Display environment properties.
    xcb_screen_t *screen = xcb_setup_roots_iterator(setup).data; // First available screen.
    lua_State *lua_state = luaL_newstate(); // Lua state. Used for configuration and scripting.

    struct cherry_state_t _state = { 1, connection, setup, screen, lua_state };
    state = &_state;

    uint32_t mask[1] = {
        XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT |
        XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY
    };

    // Sends substructure redirect.
    xcb_change_window_attributes(connection, screen->root, XCB_CW_EVENT_MASK, mask);
    xcb_flush(connection);

    // Attempt to set a SIGTERM handler (so we can gracefully exit).
    if (signal(SIGTERM, stop_running) == SIG_ERR) {
        fputs("failed to set SIGTERM handler.", stderr);
        return EXIT_FAILURE;
    }

    // Starts loop. Keeps WM running until killed.
    start_loop(state);
}