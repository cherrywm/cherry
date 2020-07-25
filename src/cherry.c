#include <stdio.h>
#include <signal.h>
#include <getopt.h>

#include "loop.h"
#include "config.h"
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>

// I immensely dislike storing global state :(
static struct cherry_state_t *state;

void stop_running(int _unused) {
    state->keep_running = 0;
    (void)(_unused);
}

void setup(const char *config_file_location) {
    lua_State *lua_state = luaL_newstate();
    luaL_openlibs(lua_state);

    cherry_config_t *config = run_config_file(lua_state, config_file_location);
    xcb_connection_t *connection = xcb_connect(NULL, NULL);

    if (xcb_connection_has_error(connection)) {
        fputs("Failed to connect to X.", stderr);
        exit(EXIT_FAILURE);
    }

    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_t *screen = xcb_setup_roots_iterator(setup).data;
    
    uint32_t substructure_mask[1] = {
        XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT |
        XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY
    };

    xcb_change_window_attributes(connection, screen->root, XCB_CW_EVENT_MASK, substructure_mask);
    xcb_flush(connection);

    if (signal(SIGTERM, stop_running) == SIG_ERR) {
        fputs("failed to set SIGTERM handler.", stderr);
        return EXIT_FAILURE;
    }

    state = (cherry_state_t*) malloc(sizeof(cherry_state_t));
    state->connection = connection;
    state->screen = screen;
    state->setup = setup;
    state->lua_state = lua_state;

    // Starts loop. Keeps WM running until killed.
    start_loop(state);
}

int main(int argc, char *argv[]) {
    int option = getopt(argc, argv, "c:");
    const char *config_file_location;

    switch (option) {
        case 'c':
            config_file_location = optarg;
            break;
        case '?':
            fputs("You must specify a file location for the -c option.", stderr);
            exit(EXIT_FAILURE); // No break; as this exits application already.
        default:
            config_file_location = default_config_file_location(); // No break; as this is the last case.
    };

    setup(config_file_location);
}