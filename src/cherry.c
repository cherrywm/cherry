#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <xcb/xcb.h>

int main(void) {
    xcb_connection_t *connection = xcb_connect(NULL, NULL);
    
    if (xcb_connection_has_error(connection)) {
        fprintf(stderr, "Error opening display.\n");
        xcb_disconnect(connection); // frees memory.
        exit(1);
    }

    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_t *screen = xcb_setup_roots_iterator(setup).data;

    xcb_disconnect(connection);
}