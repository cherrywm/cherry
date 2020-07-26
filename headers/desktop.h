#ifndef CHERRY_DESKTOP_H
    #define CHERRY_DESKTOP_H

    #include "node.h"
    #include <xcb/xcb.h>

    // Represents a single workspace, which can contain any number of nodes.
    // A single monitor can contain multiple desktops.
    typedef struct desktop_t {
        struct desktop_t *previous;
        struct desktop_t *next;
        node_t *focused;
        node_t *head;
    } desktop_t;

    // Creates a desktop. Note that this is just a constructor.
    // The desktop is not integrated.
    desktop_t* create_desktop(void);

    // Destroys a desktop, closing and freeing any resources of the desktop and the nodes it contains.
    void destroy_desktop(xcb_connection_t *connection, desktop_t *desktop);
#endif