#include <stdio.h>
#include <signal.h>
#include <getopt.h>

#include "loop.h"
#include "cherry.h"
#include "ewmh.h"

#include <lauxlib.h>
#include <lualib.h>
#include <string.h>

// I immensely dislike storing global state :(
static struct cherry_state_t *state;

// Necessary for this function. ^
void stop_running(int _unused) {
    state->keep_running = 0;
    (void)(_unused);
}

xcb_ewmh_connection_t* setup_xcb_ewmh(xcb_connection_t *connection, xcb_window_t root_window) {
    xcb_window_t child_window = create_child_window(connection, root_window);
    xcb_ewmh_connection_t *ewmh_connection = get_ewmh_connection(connection);
    xcb_generic_error_t *support_error = set_supporting_wm(connection, ewmh_connection, root_window, child_window);

    if (!support_error) {
        fputs("Failed to initialize cherry!", stderr);
        free(support_error);
        exit(EXIT_FAILURE);
    }
    
    xcb_generic_error_t *name_error = set_wm_name(connection, ewmh_connection, child_window, strlen(WM_NAME), WM_NAME);

    if (!name_error) {
        fputs("Failed to initialize cherry!", stderr);
        free(name_error);
        exit(EXIT_FAILURE);
    }

    xcb_generic_error_t *redirect_error = substructure_redirect(connection, root_window);

    if (!redirect_error) {
        fputs("Failed to initialize cherry!", stderr);
        free(redirect_error);
        exit(EXIT_FAILURE);
    }

    xcb_flush(connection);
    
    return ewmh_connection;
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

    if (signal(SIGTERM, stop_running) == SIG_ERR) {
        fputs("failed to set SIGTERM handler.", stderr);
        exit(EXIT_FAILURE);
    }

    state = (cherry_state_t*) malloc(sizeof(cherry_state_t));
    state->connection = connection;
    state->ewmh_connection = setup_xcb_ewmh(connection, screen->root);
    state->screen = screen;
    state->setup = setup;
    state->lua_state = lua_state;
    state->config = config;

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
            exit(EXIT_FAILURE); // No break; as this exits application already.
        default:
            config_file_location = default_config_file_location(); // No break; as this is the last case.
    };

    setup(config_file_location);
}