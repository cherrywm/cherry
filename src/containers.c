#include "containers.h"
#include <stdlib.h>

tag_t* create_tag(const char *name) {
    tag_t *tag = (tag_t *) malloc(sizeof(tag_t));
    tag->name = name;
    tag->next = NULL;

    return tag;
}

node_t* create_node(tag_t *tag, xcb_connection_t *connection) {
    node_t *node = (node_t *) malloc(sizeof(node_t));
    node->connection = connection;
    node->tag = tag;
    node->next = NULL;

    return node;
}

desktop_t* create_desktop(void) {
    desktop_t *desktop = (desktop_t *) malloc(sizeof(desktop_t));
    desktop->head = NULL;
    desktop->focused = NULL;

    return desktop;
}

void add_tag_to_desktop(tag_t *tag, desktop_t *desktop) {
    if (!desktop->head) {
        desktop->head = tag;
        return;
    }

    tag_t *head;
    for (head = desktop->head->next; head && head->next; head = head->next);

    head->next = tag;
}

void add_node(node_t *node) {
    // head declared in containers.h
    if (!head) {
        head = node;
        return;
    }

    node_t *current;
    for (current = head->next; current && current->next; current = current->next);

    current->next = node;
}
 
