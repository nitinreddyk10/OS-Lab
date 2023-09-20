#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd_send, fd_receive;
    int A = 42; // The integer value to be sent
    int B1; // Received one's complement value

    // Create the FIFO (Named Pipe) for sending and receiving if they don't exist
    if (access("sendfifo", F_OK) == -1) {
        if (mkfifo("sendfifo", 0666) == -1) {
            perror("mkfifo sendfifo");
            exit(EXIT_FAILURE);
        }
    }

    if (access("receivefifo", F_OK) == -1) {
        if (mkfifo("receivefifo", 0666) == -1) {
            perror("mkfifo receivefifo");
            exit(EXIT_FAILURE);
        }
    }

    // Open the FIFO for sending
    fd_send = open("sendfifo", O_WRONLY);
    if (fd_send == -1) {
        perror("open sendfifo");
        exit(EXIT_FAILURE);
    }

    // Write the integer value A to the FIFO for sending
    if (write(fd_send, &A, sizeof(int)) == -1) {
        perror("write sendfifo");
        exit(EXIT_FAILURE);
    }

    printf("Sender: Sent value A = %d\n", A);

    // Close the FIFO for sending
    close(fd_send);

    // Open the FIFO for receiving
    fd_receive = open("receivefifo", O_RDONLY);
    if (fd_receive == -1) {
        perror("open receivefifo");
        exit(EXIT_FAILURE);
    }

    // Read the one's complement B1 from the FIFO for receiving
    if (read(fd_receive, &B1, sizeof(int)) == -1) {
        perror("read receivefifo");
        exit(EXIT_FAILURE);
    }

    printf("Sender: Received one's complement B1 = %d\n", B1);

    // Close the FIFO for receiving
    close(fd_receive);

    return 0;
}