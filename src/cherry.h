#ifndef CHERRY_CHERRYH
    #define CHERRY_CHERRYH

    #include <xcb/xcb.h>
    #include <lua.h>

    // Cherry state struct.
    // One instance of this is created and referred to throughout cherry.
    typedef struct cherry_state_t {
        int keep_running;
        xcb_connection_t *connection;
        const xcb_setup_t *setup;
        xcb_screen_t *screen;
        lua_State *lua_state;
    } cherry_state_t;

    // Flips run check, so that the loop stops.
    // Once the loop stops, the rest of the application gets cleaned up.
    void stop_running(int _unused);

    // Responsible for setting up cherry if all the preconditions are met.
    // This is effectively the true entry point of cherry.
    void setup(void);
#endif