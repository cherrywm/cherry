#include "loop.h"
#include "lua.h"

const struct timespec delay = {0, 50000000L};

void start_loop(cherry_state_t *state) {
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

        // Free the memory allocated for event struct.
        free(ev);

        // Add in a 0.05s sleep, so that this loop doesn't eat up all the CPU.
        nanosleep(&delay, NULL);
    } while (state->keep_running);

    // TODO: Iterate through desktops & free them.

    // Close connection to X server.
    xcb_disconnect(state->connection);

    // Close Lua.
    lua_close(state->lua_state);

    // Free memory allocated for config struct.
    free(state->config);

    // Free the memory allocated for the state struct.
    free(state);

    // Exit with a successful status code.
    exit(0);
}