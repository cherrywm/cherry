#ifndef CHERRY_NODEH
    #define CHERRY_NODEH

    #include <xcb/xcb.h>

    // A wrapper around an X window.
    typedef struct node_t {
        xcb_window_t *window;
        struct node_t *previous;
        struct node_t *next;
    } node_t;

    // Creates a node from a window, but does not integrate it. A constructor.
    node_t* create_node(xcb_window_t *window);

    // Destroys a node.
    // All memory is freed.
    void destroy_node(node_t *node);

    // Destroys the underlying X window, but doesn't free the node memory.
    void destroy_window(xcb_connection_t *connection, node_t *node);
#endif