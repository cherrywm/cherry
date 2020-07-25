#include "containers.h"

node_t* create_node(desktop_t *desktop, xcb_window_t *window) {
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->window = window;
    node->desktop = desktop;
    
    if (!desktop->head) {
        desktop->head = node;
        return node;
    }

    node_t *current = desktop->head;
    while (current->next)
        current = current->next;

    current->next = node;
    return node;
}

void destroy_node(node_t *node) {
    // Destroy the actual X window.
    xcb_destroy_window(node->desktop->state->connection, node->window);

    // If the focused node is this one, set focused node to NULL.
    // If the head of the node list is this one, set head to the next node (which may be NULL).
    // If the next node is NOT NULL, make next node's previous point to this node's previous (which may be NULL).

    if (node->desktop->focused == node)
        node->desktop->focused = NULL;
    
    if (node->desktop->head == node) 
        node->desktop->head = node->next;

    if (!node->next)
        node->next->previous = node->previous;

    // Free memory allocated for the node.
    free(node);
}