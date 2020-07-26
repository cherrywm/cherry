#include "loop.h"

const struct timespec delay = {0, 50000000L};

void start_loop(cherry_state_t *state) {
    state->keep_running = 1;
    xcb_generic_event_t *event;

    do {
        if ((event = xcb_poll_for_event(state->connection))) {
            uint8_t response_type = event->response_type & ~0x80;

            switch (response_type) {
                case XCB_MAP_REQUEST:
                    map_request(state->connection, &((xcb_map_request_event_t *) event)->window);
                    break;

                case XCB_DESTROY_NOTIFY:
                    // nothing right now
                    // destroy_notify requires node_t, no system in place for it right now
                    break;

                default:
                    break; // Skeleton loop.
            }
        }

        // Free the memory allocated for event struct.
        free(event);

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