#include "ewmh.h"
#include <stdio.h>

xcb_window_t* create_child_window(xcb_connection_t *connection, xcb_window_t *root) {
    xcb_window_t *child_window = xcb_generate_id(connection);

    xcb_create_window(connection, XCB_COPY_FROM_PARENT, child_window, root, -1, -1, 1, 1, 0,
        XCB_WINDOW_CLASS_INPUT_ONLY, XCB_COPY_FROM_PARENT, XCB_NONE, NULL);

    return child_window;
}

xcb_ewmh_connection_t* get_ewmh_connection(xcb_connection_t *connection) {
    xcb_ewmh_connection_t *ewmh_connection = (xcb_ewmh_connection_t *) malloc(sizeof(xcb_ewmh_connection_t));
    xcb_intern_atom_cookie_t *cookies = xcb_ewmh_init_atoms(connection, ewmh_connection);

    if (!xcb_ewmh_init_atoms_replies(ewmh_connection, cookies, NULL)) {
        fputs("Error when initializing screen.", stderr);
        return NULL;
    }

    return ewmh_connection;
}

xcb_generic_error_t* set_supporting_wm(xcb_connection_t *connection, xcb_ewmh_connection_t *ewmh_connection,
    xcb_window_t *root_window, xcb_window_t *child_window)
{
    xcb_void_cookie_t cookie = xcb_ewmh_set_supporting_wm_check_checked(ewmh_connection, root_window, child_window);
    return xcb_request_check(connection, cookie);
}

xcb_generic_error_t* set_wm_name(xcb_connection_t *connection, xcb_ewmh_connection_t *ewmh_connection,
    xcb_window_t *window, size_t length, const char* name)
{
    xcb_void_cookie_t cookie = xcb_ewmh_set_wm_name_checked(ewmh_connection, window, length, name);
    return xcb_request_check(connection, cookie);
}