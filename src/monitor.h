#ifndef CHERRY_MONITORH
    #define CHERRY_MONITORH
    #include "cherry.h"
    #include "desktop.h"

    // Note that, in cherry, only one monitor exists.
    // For multiple physical monitor setups, cherry will treat them as one abnormally large virtual monitor.
    // This behaviour will probably be changed soon, so as to allow for multiple virtual monitors.
    typedef struct monitor_t {
        cherry_state_t *state;
        desktop_t *head;
        desktop_t *focused;
    } monitor_t;

    // Creates a monitor but, as with the other container functions, does not integrate it.
    // You can view this as a fancy constructor.
    monitor_t* create_monitor(cherry_state_t *state);

    // Destroys a monitor, closing and freeing all the resources it consumes.
    // This will also invoke the destructors of the desktops a monitor contains, and thus the node ones too.
    // For single-monitor setups, this is effectively the same as nuking cherry.
    void destroy_monitor(monitor_t *monitor);
#endif