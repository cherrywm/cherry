#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#include "cherry.h"

#include <lauxlib.h>
#include <lualib.h>

static struct cherry_state_t *state;

const struct timespec delay = {0, 50000000L}; // Prevents the loop from consuming 100% of its respective core all the time.

void stop_running(int _unused) {
    state->keep_running = 0;
    (void)(_unused);
}

void start_loop(void) {
    state->keep_running = 1;
    xcb_generic_event_t *ev;

    do {
        if ((ev = xcb_poll_for_event(state->connection))) {
            uint8_t response_type = ev->response_type & ~0x80;

            switch (response_type) {
                default:
                    break; // Skeleton loop.
            }
        }

        nanosleep(&delay, NULL);
    } while (state->keep_running);

    // TODO: Iterate through desktops & free them.

    // Close connection to X server.
    xcb_disconnect(state->connection);

    // Exit with a successful status code.
    exit(0);
}

int main(void) {
    // Establish connection to DISPLAY X server, first available screen.
    // TODO: Support multple monitors.
    xcb_connection_t *connection = xcb_connect(NULL, NULL);
    
    // Check if we failed to establish a connection to the specified X server.
    if (xcb_connection_has_error(connection))
        return 1; // todo: actual error logging.

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

    signal(SIGTERM, stop_running);

    // Starts loop. Keeps WM running until killed.
    start_loop();
}