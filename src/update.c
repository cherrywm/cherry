#include "update.h"
#include <stdlib.h>

const uint32_t map_mask[2] = { 1, XCB_STACK_MODE_ABOVE };

void map_request(cherry_state_t *state, xcb_map_request_event_t *event) {
    node_t *node = create_node(&event->window);
    xcb_configure_window(state->connection, event->window,
        XCB_CONFIG_WINDOW_BORDER_WIDTH | XCB_CONFIG_WINDOW_STACK_MODE, map_mask);
    xcb_map_window(state->connection, event->window);
}

void destroy_notify(xcb_destroy_notify_event_t *event) {
    // destroy window
    // update containers
}