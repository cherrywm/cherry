#include <stdio.h>
#include <signal.h>
#include <getopt.h>

#include "loop.h"
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>

// I immensely dislike storing global state :(
static struct cherry_state_t *state;

void stop_running(int _unused) {
    state->keep_running = 0;
    (void)(_unused);
}

// Executed if no options are passed to cherry.
// No --config/-c option makes cherry assume a config file location of $XDG_CONFIG_HOME/cherry/cherry.lua.
void setup() {
    // skeleton.
}

int main(int argc, char *argv[]) {
    int option_index = getopt(argc, argv, "c:");
    if (option_index == -1) {
        exit(1); // skeleton.
    }

    getopt(argc, argv, "c::");

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

    luaL_openlibs(lua_state);

    // We're not going to be reading before writing, so malloc instead of calloc.
    state = (cherry_state_t*) malloc(sizeof(cherry_state_t));
    state->connection = connection;
    state->screen = screen;
    state->setup = setup;
    state->lua_state = lua_state;

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