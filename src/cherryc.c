// This file is not part of 🍒.
// It's a separate executable, used to send messages to a named pipe that the actual window manager reads from.
// You'd use this program to reload the configuration file, for example.

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

#include "config.h"

int main(int argc, char *argv[]) {
    int option;
    const char *pipe_location;
    int has_command = 0;

    while ((option = getopt(argc, argv, "f:r")) != -1) {
        switch (option) {
            case 'f':
                pipe_location = optarg;
                break;

            case 'r':
                has_command = 1;
                break;

            case '?':
                exit(EXIT_FAILURE);

            default:
                pipe_location = CHERRY_DEFAULT_FIFO_LOCATION;
        };
    }

    if (!has_command) {
        fputs("You need to specify a command. Right now, cherryc only supports reloading config files (-r).", stderr);
        exit(EXIT_FAILURE);
    }

    if (access(pipe_location, F_OK) == -1) {
        fputs("A file with that path doesn't exist. Make sure 🍒 is running, and that the path is correct.", stderr);
        exit(EXIT_FAILURE);
    }

    int file_descriptor = open(pipe_location, O_NONBLOCK, O_WRONLY);
    char buffer[1] = { 'r' };

    write(file_descriptor, buffer, 1);
    close(file_descriptor);
}