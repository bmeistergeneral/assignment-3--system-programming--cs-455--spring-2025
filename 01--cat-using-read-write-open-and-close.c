#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 8192

int main(int argc, char *argv[]) {
    int input_fd = STDIN_FILENO; // Standard input by default
    int output_fd = STDOUT_FILENO; // Standard output
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    int i;

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            input_fd = open(argv[i], O_RDONLY);
            if (input_fd == -1) {
                perror("Error opening file");
                continue; // Try the next file
            }

            while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
                bytes_written = write(output_fd, buffer, bytes_read);
                if (bytes_written == -1) {
                    perror("Error writing to stdout");
                    close(input_fd);
                    return 1;
                }
            }

            if (bytes_read == -1) {
                perror("Error reading file");
            }

            if (close(input_fd) == -1) {
                perror("Error closing file");
                return 1;
            }
        }
    } else {
        // Read from standard input
        while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
            bytes_written = write(output_fd, buffer, bytes_read);
            if (bytes_written == -1) {
                perror("Error writing to stdout");
                return 1;
            }
        }

        if (bytes_read == -1) {
            perror("Error reading from stdin");
            return 1;
        }
    }

    return 0;
}