#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <lauxlib.h>
#include <lualib.h>
#include <unistd.h>
#include <fcntl.h>

#include "cherry.h"
#include "config.h"
#include "update.h"
#include "ewmh.h"

void stop_running(int _unused) {
    keep_running = 0;
    (void)(_unused);
}

int keep_running;
int fifo_file_descriptor;
xcb_connection_t *connection;
xcb_ewmh_connection_t *ewmh_connection;
xcb_screen_t *screen;
lua_State *lua_state;

void setup_xcb_ewmh(void) {
    ewmh_connection = get_ewmh_connection();
    xcb_window_t root_window = screen->root;
    xcb_window_t child_window = create_child_window(&root_window);
    xcb_generic_error_t *support_error = set_supporting_wm(&root_window, &child_window);

    if (support_error) {
        fprintf(stderr, "Failed to set supporting WM check! (%d)", support_error->error_code);
        free(support_error);
        exit(EXIT_FAILURE);
    }
    
    xcb_generic_error_t *name_error = set_wm_name(&child_window, strlen(WM_NAME), WM_NAME);

    if (name_error) {
        fprintf(stderr, "Failed to set WM name/supp check! (%d)", name_error->error_code);
        free(name_error);
        exit(EXIT_FAILURE);
    }

    xcb_generic_error_t *redirect_error = substructure_redirect(&root_window);

    if (redirect_error) {
        fprintf(stderr, "Failed to set substructure redirect! (%d)", redirect_error->error_code);
        free(redirect_error);
        exit(EXIT_FAILURE);
    }

    xcb_flush(connection);
}

void setup(const char *config_file_location) {
    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
    run_config_file(config_file_location);
    connection = xcb_connect(NULL, NULL);

    if (xcb_connection_has_error(connection)) {
        fputs("Failed to connect to X.", stderr);
        exit(EXIT_FAILURE);
    }

    const xcb_setup_t *setup = xcb_get_setup(connection);
    screen = xcb_setup_roots_iterator(setup).data;

    if (signal(SIGTERM, stop_running) == SIG_ERR) {
        fputs("failed to set SIGTERM handler.", stderr);
        exit(EXIT_FAILURE);
    }

    unlink(fifo_path);
    fifo_file_descriptor = open(fifo_path, O_RDONLY, O_NONBLOCK);

    setup_xcb_ewmh();
    start_loop();
}

int main(int argc, char *argv[]) {
    int option = getopt(argc, argv, "c:");
    const char *config_file_location;

    switch (option) {
        case 'c':
            config_file_location = optarg;
            break;

        case '?':
            exit(EXIT_FAILURE);

        default:
            config_file_location = default_config_file_location();
    };

    setup(config_file_location);
}