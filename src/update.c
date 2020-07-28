#include "update.h"
#include "cherry.h"
#include <time.h>

struct timespec delay = {0, 50000000L};

void start_loop() {
    keep_running = 1;

    do {
        xcb_generic_event_t *event = xcb_poll_for_event(connection);

        if (event) {
            uint8_t response_type = event->response_type & ~0x80;
            switch (response_type) {
                case XCB_MAP_REQUEST:
                    // replace NULL with actual tags later.
                    map_request(NULL, &((xcb_map_request_event_t *) event)->window);
                    break;

                case XCB_DESTROY_NOTIFY:
                    break;

                default:
                    break;
            }
            free(event);
        }

        nanosleep(&delay, NULL);

    } while (keep_running);

    xcb_disconnect(connection);
    lua_close(lua_state);
    free(ewmh_connection);
}

void map_request(tag_t *tag, xcb_window_t *window) {
    node_t *node = create_node(tag, window);
    xcb_map_window(connection, *window);
    xcb_flush(connection);
    // Update containers.
}

void destroy_notify(node_t *node) {
    // destroy node
    xcb_flush(connection);
    // Update containers.
}