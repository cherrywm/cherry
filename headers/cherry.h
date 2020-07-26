#ifndef CHERRY_CHERRY_H
    #define CHERRY_CHERRY_H
    #define WM_NAME "cherry"

    #include <xcb/xcb.h>
    #include <xcb/xcb_atom.h>
    #include <xcb/xcb_ewmh.h>
    
    #include <lua.h>
    #include "config.h"

    // Cherry state struct.
    // One instance of this is created and referred to throughout cherry.
    typedef struct cherry_state_t {
        int keep_running;
        xcb_connection_t *connection;
        xcb_ewmh_connection_t *ewmh_connection;
        const xcb_setup_t *setup;
        xcb_screen_t *screen;
        lua_State *lua_state;
        cherry_config_t *config;
    } cherry_state_t;

    // Flips run check, so that the loop stops.
    // Once the loop stops, the rest of the application gets cleaned up.
    void stop_running(int _unused);

    // Responsible for setting up cherry if all the preconditions are met.
    // This is effectively the true entry point of cherry.
    void setup(const char *config_file_location);

    // Sets up XCB, EWMH and any other X stuff.
    xcb_ewmh_connection_t* setup_xcb_ewmh(xcb_connection_t *connection, xcb_window_t root_window);
#endif