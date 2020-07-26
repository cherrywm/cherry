#ifndef CHERRY_EWMH_H
    #define CHERRY_EWMH_H

    #include <xcb/xcb.h>
    #include <xcb/xcb_ewmh.h>
    #include <xcb/xcb_atom.h>

    // Creates a child/meta window.
    // This is used by cherry for a variety of internal reasons.
    // This is not mapped, and thus cannot be interacted with.
    xcb_window_t* create_child_window(xcb_connection_t *connection, xcb_window_t *root);

    // Allocates an xcb_ewmh_connection_t struct and inits atoms etc.
    // Returns NULL if there was an error.
    // This is not automatically freed.
    xcb_ewmh_connection_t* ewmh_connection(xcb_connection_t *connection);

    // Enables cherry to be compliant with the _NET_SUPPORTING_WM_CHECK part of the EWMH specification.
    // Returns a possibly-NULL error pointer.
    // Note that this is synchronous, but is only called once.
    xcb_generic_error_t* set_supporting_wm(xcb_connection_t *connection, xcb_ewmh_connection_t *ewmh_connection,
        xcb_window_t *root_window, xcb_window_t *child_window);

    // Sets a window's name. Used in conjunction with set_supporting_wm.
    // Returns a possibly-NULL error pointer.
    xcb_generic_error_t* set_wm_name(xcb_connection_t *connection, xcb_ewmh_connection_t *ewmh_connection,
        xcb_window_t *window, size_t length, const char* name);
#endif