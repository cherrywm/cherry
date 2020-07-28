#ifndef CHERRY_CONTAINERS_H
    #define CHERRY_CONTAINERS_H

    #include <xcb/xcb.h>

    // Responsible for nodes (wrappers around windows), tags (similar to workspaces)
    // Tags are represented as a linked list of strings.
    // A node will only be rendered if it points to a tag that is currently focused.

    typedef struct tag_t {
        struct tag_t *next;
        const char *name;
    } tag_t;

    // Wrapper around a window.
    typedef struct node_t {
        struct node_t *next;
        xcb_connection_t *connection;
        tag_t *tag; // TODO: multiple tag support?
    } node_t;

    typedef struct desktop_t {
        tag_t *head;
        tag_t *focused;
    } desktop_t;

    // The first node in cherry.
    // A node can be moved to a different desktop, hence why this is outside the scope of desktop_t.
    // This is a pretty hacky solution. Will change later if problems arise.
    extern node_t *head;

    // Creates a tag_t struct.
    tag_t* create_tag(const char *name);

    // Creates a node_t struct.
    node_t* create_node(tag_t *tag, xcb_window_t *window);

    // Creates a desktop_t struct.
    desktop_t* create_desktop(void);

    // Appends a tag to the desktop.
    void add_tag_to_desktop(tag_t *tag, desktop_t *desktop);

    // Inserts a node at tail of list.
    void add_node(node_t *node);
#endif