#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

/*
 * Creates a file and writes content into it.
 */
int create_and_write_file(const char *filename, const char *content) {
    int fd;                  // file descriptor 
    ssize_t bytes_written;   // number of bytes successfully written

    printf("Creating file: %s\n", filename);
    printf("Writing content: \"%s\"\n", content);

    // Open the file for writing. Create if it doesn’t exist. Wipe it if it does.
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {  // -1 means error
        perror("Error opening file");
        return -1;
    }
    printf("File opened successfully! (fd = %d)\n", fd);

    // Write the content into the file
    bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return -1;
    }
    printf("Wrote %zd bytes to %s\n", bytes_written, filename);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }
    printf("File closed successfully!\n");

    return 0;
}

/*
 * Reads a file and prints its contents to the screen.
 */
int read_file_contents(const char *filename) {
    int fd;                  // file descriptor
    char buffer[1024];       // temporary storage for what we read
    ssize_t bytes_read;      // number of bytes read each time

    printf("Reading file: %s\n", filename);

    // Open the file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }
    printf("File opened successfully! (fd = %d)\n", fd);
    printf("----- File Contents -----\n");

    // Read in chunks until there’s nothing left
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';   // add string terminator
        printf("%s", buffer);        // print what we read
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return -1;
    }

    printf("\n----- End of File -----\n");

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }
    printf("File closed successfully!\n");

    return 0;
}

