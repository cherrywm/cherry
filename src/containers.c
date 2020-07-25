#include "containers.h"

node_t* create_node(desktop_t *desktop, xcb_window_t *window) {
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->previous = NULL;
    node->next = NULL;
    node->window = window;

    if (!desktop->head) {
        desktop->head = node;
        return node;
    }

    node_t *head  = desktop->head;
    while (head->next)
        head = head->next;

    head->next = node;
    return node;
}

void destroy_node(desktop_t *desktop, node_t *node) {
    // Destroy the actual X window.
    xcb_destroy_window(desktop->state->connection, *node->window);

    // If the focused node is this one, set focused node to NULL.
    // If the head of the node list is this one, set head to the next node (which may be NULL).
    // If the next node is NOT NULL, make next node's previous point to this node's previous (which may be NULL).

    if (desktop->focused == node)
        desktop->focused = NULL;
    
    if (desktop->head == node) 
        desktop->head = node->next;

    if (!node->next)
        node->next->previous = node->previous;

    // Free memory allocated for the node.
    free(node);
}

desktop_t* create_desktop(cherry_state_t *state) {
    desktop_t *desktop = (desktop_t*) malloc(sizeof(desktop_t));
    desktop->state = state;
    desktop->focused = NULL;
    desktop->head = NULL;

    return desktop;
}

void destroy_desktop(desktop_t *desktop) {
    node_t *head = desktop->head;
    
    while (head->next) {
        head = head->next;
        free(head);
    }

    free(desktop);
}