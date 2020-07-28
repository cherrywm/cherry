#ifndef CHERRY_UPDATE_H
    #define CHERRY_UPDATE_H

    #include <xcb/xcb.h>
    #include "containers.h"

    void start_loop();

    void map_request(tag_t *tag, xcb_window_t *window);

    void destroy_notify(node_t *node);
#endif