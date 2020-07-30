#ifndef CHERRY_UPDATE_H
    #define CHERRY_UPDATE_H
    #define CHERRY_BUFFER_SIZE 1
    #define CHERRY_RELOAD_CONFIG "r"

    #include <xcb/xcb.h>
    #include "containers.h"

    void start_loop();

    void map_request(tag_t *tag, xcb_window_t *window);

    void destroy_notify(node_t *node);
#endif