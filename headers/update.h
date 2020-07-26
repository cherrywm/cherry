#ifndef CHERRY_UPDATE_H
    #define CHERRY_UPDATE_H

    #include <xcb/xcb.h>
    #include "node.h"

    void map_request(xcb_connection_t *connection, xcb_window_t *window);

    void destroy_notify(xcb_connection_t *connection, node_t *node);
#endif