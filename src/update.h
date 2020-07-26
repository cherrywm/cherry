#ifndef CHERRY_UPDATEH
    #define CHERRY_UPDATE_H

    #include <xcb/xcb.h>
    #include "node.h"
    #include "desktop.h"
    #include "cherry.h"

    void update_desktop(desktop_t *desktop);
    void map_request(cherry_state_t *state, xcb_map_request_event_t *request_event);
    void destroy_notify(xcb_destroy_notify_event_t *destroy_notify_event);
#endif