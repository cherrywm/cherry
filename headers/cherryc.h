#ifndef CHERRYC_H
    #include <fcntl.h>
    #define CHERRYC_OPEN_FLAGS O_NONBLOCK | O_WRONLY
    #define CHERRYC_PIPE_ACCESS_ERR "Pipe doesn't exist, or we don't have write access. Error: %s\n"
    #define CHERRYC_PIPE_OPEN_ERR "Failed to open pipe. Error: %s\n"
    #define CHERRYC_PIPE_WRITE_ERR "Failed to write to pipe. Error: %s\n"

    extern int reload;
    extern const char *path;
    extern const char *tag;

    int main(int argc, char *argv[]);

    void read_args(int argc, char *argv[]);
#endif