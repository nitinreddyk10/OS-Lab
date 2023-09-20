#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd_send, fd_receive;
    int A, B1; // Received values

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

    // Open the FIFO for receiving
    fd_receive = open("sendfifo", O_RDONLY);
    if (fd_receive == -1) {
        perror("open sendfifo");
        exit(EXIT_FAILURE);
    }

    // Read the integer value A from the FIFO for receiving
    if (read(fd_receive, &A, sizeof(int)) == -1) {
        perror("read sendfifo");
        exit(EXIT_FAILURE);
    }

    printf("Receiver: Received value A = %d\n", A);

    // Calculate the one's complement B1
    B1 = ~A;

    // Close the FIFO for receiving
    close(fd_receive);

    // Open the FIFO for sending
    fd_send = open("receivefifo", O_WRONLY);
    if (fd_send == -1) {
        perror("open receivefifo");
        exit(EXIT_FAILURE);
    }

    // Write the one's complement B1 to the FIFO for sending
    if (write(fd_send, &B1, sizeof(int)) == -1) {
        perror("write receivefifo");
        exit(EXIT_FAILURE);
    }

    printf("Receiver: Sent one's complement B1 = %d\n", B1);

    // Close the FIFO for sending
    close(fd_send);

    return 0;
}