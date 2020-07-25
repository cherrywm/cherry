#include "monitor.h"
#include <stdlib.h>

monitor_t* create_monitor(cherry_state_t *state) {
    monitor_t *monitor = (monitor_t*) malloc(sizeof(monitor_t));
    monitor->focused = NULL;
    monitor->head = NULL;
    monitor->state = state;

    return monitor;
}

void destroy_monitor(monitor_t *monitor) {
    for (desktop_t *desktop = monitor->head; desktop; desktop = desktop->next)
        destroy_desktop(desktop);
    
    // We don't free the cherry state as it is used elsewhere outside the scope of window containers.
    free(monitor);
}