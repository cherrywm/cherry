#ifndef CHERRY_CONTAINERSH
    #define CHERRY_CONTAINERSH

    #include <xcb/xcb.h>
    #include "cherry.h"

    // A wrapper struct around an X Window.
    // Used as a linked list structure.
    typedef struct node_t {
        xcb_window_t *window;
        struct node_t *previous;
        struct node_t *next;
    } node_t;

    // Note that this refers to a single screen.
    // A single physical monitor can have many desktops, all of which contain their own list of windows.
    typedef struct desktop_t {
        cherry_state_t *state;
        node_t *head;
        node_t *focused;
    } desktop_t;

    // Creates a wrapper node struct around an X window.
    // This does not modify the layout in any way. It just creates a node.
    // The node list will be modified.
    // Other parts of cherry are responsible for integrating this.
    node_t* create_node(desktop_t *desktop, xcb_window_t *window);

    // Destroys a node (and the corresponding window).
    // This, again, does not modify the layout in any way.
    // The node list will be modified though.
    // Automatically frees any memory allocated for the node.
    void destroy_node(desktop_t *desktop, node_t* node);

    // Creates a desktop struct.
    desktop_t* create_desktop(cherry_state_t *state);

    // Closes a desktop and frees the memory.
    // This will also close all the X windows this desktop manages.
    void destroy_desktop(desktop_t *desktop);
#endif