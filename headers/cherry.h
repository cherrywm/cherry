#ifndef CHERRY_CHERRY_H
    #define CHERRY_CHERRY_H
    #define WM_NAME "🍒"

    #include <xcb/xcb.h>
    #include <xcb/xcb_ewmh.h>
    #include <lua.h>

    extern int keep_running;
    extern xcb_connection_t *connection;
    extern xcb_ewmh_connection_t *ewmh_connection;
    extern xcb_screen_t *screen;
    extern lua_State *lua_state;

    // Flips run check, so that the loop stops.
    // Once the loop stops, the rest of the application gets cleaned up.
    void stop_running(int _unused);

    // Responsible for setting up cherry if all the preconditions are met.
    // This is effectively the true entry point of cherry.
    void setup(const char *config_file_location);

    // Sets up XCB, EWMH and any other X stuff.
    void setup_xcb_ewmh(void);
#endif