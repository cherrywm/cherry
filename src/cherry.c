#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <xcb/xcb.h>

#include "lua.h"
#include "lauxlib.h"
#include <lualib.h>

static volatile int keep_running;      // Used to keep loop running.
static xcb_connection_t *connection;   // The connection pointer.
static const xcb_setup_t *setup;       // xcb setup pointer.
static xcb_screen_t *screen;           // First screen. todo: multiple monitor support.
static lua_State *lua_state;           // Lua state. Used for configuration.

const struct timespec delay = {0, 50000000L}; // Prevents the loop from consuming 100% of its respective core all the time.

void stop_running(int _unused) {
    keep_running = 0;
    (void)(_unused);
}

void start_loop(void) {
    keep_running = 1;
    xcb_generic_event_t *ev;

    do {
        if ((ev = xcb_poll_for_event(connection))) {
            switch (ev->response_type & ~0x80) {
                default:
                    break; // Skeleton loop.
            }
        }

        nanosleep(&delay, NULL);
    } while (keep_running);

    // TODO: Iterate through desktops & free them.

    // Close connection to X server.
    xcb_disconnect(connection);

    // Exit with a successful status code.
    exit(0);
}

int main(void) {
    // Establish connection to DISPLAY X server, first available screen.
    // TODO: Support multple monitors.
    connection = xcb_connect(NULL, NULL);
    
    // Check if we failed to establish a connection to the specified X server.
    if (xcb_connection_has_error(connection))
        return 1; // todo: actual error logging.

    setup = xcb_get_setup(connection); // Display environment properties.
    screen = xcb_setup_roots_iterator(setup).data; // First available screen.
    lua_state = luaL_newstate(); // Lua state. Used for configuration and scripting.

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