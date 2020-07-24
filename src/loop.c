#include "loop.h"

const struct timespec delay = {0, 50000000L}; // Prevents the loop from consuming 100% of its respective core all the time.

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

        nanosleep(&delay, NULL);
    } while (state->keep_running);

    // TODO: Iterate through desktops & free them.

    // Close connection to X server.
    xcb_disconnect(state->connection);

    // Exit with a successful status code.
    exit(0);
}