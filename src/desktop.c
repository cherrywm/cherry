#include "desktop.h"
#include "stdlib.h"

desktop_t* create_desktop(void) {
    desktop_t *desktop = (desktop_t*) malloc(sizeof(desktop_t));
    desktop->focused = NULL;
    desktop->head = NULL;
    desktop->next = NULL;
    desktop->previous = NULL;

    return desktop;
}

void destroy_desktop(xcb_connection_t *connection, desktop_t *desktop) {
    for (node_t *node = desktop->head; node; node = node->next)
        destroy_node(connection, node);
    
    free(desktop);
}