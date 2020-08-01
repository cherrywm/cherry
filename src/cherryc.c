#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "config.h"
#include "cherryc.h"

const char *tag = NULL;
const char *path = CHERRY_DEFAULT_FIFO_LOCATION;
int reload = 0;

int main(int argc, char *argv[]) {
    read_args(argc, argv);

    if (access(path, W_OK) != 0) {
        fprintf(stderr, CHERRYC_PIPE_ACCESS_ERR, strerror(errno));
        exit(EXIT_FAILURE);
    }

    int file_descriptor;

    if ((file_descriptor = open(path, CHERRYC_OPEN_FLAGS)) == -1) {
        fprintf(stderr, CHERRYC_PIPE_OPEN_ERR, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // [t\0<tag>\0][r\0]
    int buffer_size = (tag ? strlen(tag) + 3 : 0) + (reload ? 2 : 0);

    if (!buffer_size) {
        // 0 = false = no commands = nothing to do
        puts("Nothing to do.");
        close(file_descriptor);
        exit(EXIT_SUCCESS);
    }

    char buffer[buffer_size];
    if (reload)
        memcpy(buffer, "r", 2);

    if (tag) {
        int _i;
        for (_i = 0; !buffer[_i]; _i++);

        memcpy(buffer + _i + 1, "t", 2);
        memcpy(buffer + _i + 3, tag, strlen(tag) + 1);
    }
    
    int wr = write(file_descriptor, buffer, buffer_size);

    if (wr == -1) {
        fprintf(stderr, CHERRYC_PIPE_WRITE_ERR, strerror(errno));
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }

    close(file_descriptor);
}

void read_args(int argc, char *argv[]) {
    char option;

    while ((option = getopt(argc, argv, "rt:f:")) != -1) {
        switch (option) {
            case 't':
                tag = optarg;
                break;
            
            case 'r':
                reload = 1;
                break;

            case 'f':
                path = optarg;
                break;

            default:
                exit(EXIT_FAILURE);
        }
    }
}