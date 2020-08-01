#include "update.h"
#include "cherry.h"
#include "config.h"
#include "ewmh.h"

#include <time.h>
#include <unistd.h>
#include <stdio.h> // remove after finished draft
#include <string.h>

struct timespec delay = {0, 50000000L};

void start_loop() {
    keep_running = 1;
    int bytes_read;
    char buffer[CHERRY_BUFFER_SIZE];

    do {
        xcb_generic_event_t *event = xcb_poll_for_event(connection);
        
        if (event) {
            uint8_t response_type = event->response_type & ~0x80;
            switch (response_type) {
                case XCB_MAP_REQUEST: ;
                    xcb_map_request_event_t *map_event = (xcb_map_request_event_t *) event;
                    // replace NULL with actual tags later.
                    map_request(NULL, &map_event->window);
                    break;

                case XCB_DESTROY_NOTIFY:
                    break;

                default:
                    break;
            }

            free(event);
        }

        if ((bytes_read = read(fifo_file_descriptor, buffer, CHERRY_BUFFER_SIZE))) {
            for (int index = 0; index < bytes_read; index++) {
                if (buffer[index] == 'r') {
                    run_config_file();
                } else if (buffer[index] == 't') {
                    int _i;
                    for (_i = index + 2; _i < bytes_read && buffer[_i]; _i++);
                    char tag[_i - index + 2];

                    memcpy(tag, buffer + index + 2, sizeof(tag));
                    create_tag(tag);
                }
            }
        }

        nanosleep(&delay, NULL);

    } while (keep_running);

    xcb_disconnect(connection);
    lua_close(lua_state);
    free(ewmh_connection);
}

void map_request(tag_t *tag, xcb_window_t *window) {
    node_t *node = create_node(tag, window);
    xcb_map_window(connection, *window);
    xcb_flush(connection);
    // Update containers.
}

void destroy_notify(node_t *node) {
    // destroy node
    xcb_flush(connection);
    // Update containers.
}