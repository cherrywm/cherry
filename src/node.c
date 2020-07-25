#include "node.h"
#include "stdlib.h"

node_t *create_node(xcb_window_t *window) {
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->next = NULL;
    node->previous = NULL;
    node->window = window;

    return node;
}

void destroy_window(xcb_connection_t *connection, node_t *node) {
    xcb_destroy_window(connection, *node->window);
}

void destroy_node(node_t *node) {
    free(node);
}