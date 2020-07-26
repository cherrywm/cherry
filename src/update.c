#include "update.h"
#include <stdlib.h>

void map_request(xcb_connection_t *connection, xcb_window_t *window) {
    node_t *node = create_node(window);
    xcb_map_window(connection, window);
    xcb_flush(connection);
    // Update containers.
}

void destroy_notify(xcb_connection_t *connection, node_t *node) {
    destroy_node(connection, node);
    xcb_flush(connection);
    // Update containers.
}