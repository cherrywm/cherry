#ifndef CHERRY_CONFIG_H
    #define CHERRY_CONFIG_H

    #define CHERRY_DEFAULT_FIFO_LOCATION "/tmp/cherry"
    #define CHERRY_DEFAULT_DESKTOP_COUNT 1
    #define CHERRY_DEFAULT_BORDER_WIDTH 1
    #define CHERRY_DEFAULT_WINDOW_GAP 20
    #define CHERRY_DEFAULT_TOP_PADDING 10
    #define CHERRY_DEFAULT_BOTTOM_PADDING 10
    #define CHERRY_DEFAULT_RIGHT_PADDING 10
    #define CHERRY_DEFAULT_LEFT_PADDING 10

    extern const char *fifo_path;
    extern int desktop_count;
    extern int border_width;
    extern int window_gap;
    extern int top_padding;
    extern int bottom_padding;
    extern int right_padding;
    extern int left_padding;

    // Assumes Lua has already been setup.
    void run_config_file(void);

    // Helper functions.
    int int_from_config(const char *key, int default_value);
    const char* string_from_config(const char *key, const char *default_value);

    // Defaults to $XDG_CONFIG_HOME/cherry/cherry.lua, or $HOME/.config/cherry/cherry.lua
    const char* default_config_file_location(void);
#endif