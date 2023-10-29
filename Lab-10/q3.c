//Implement the reader-writer problem’s solution using semaphore.
//Use one writer thread and five reader threads. Also, clearly define the reader() function and writer() function that reader and writer thread execute separately.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 1

sem_t mutex, wrt;
int read_count = 0;
int data = 0;

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    while (1) {
        // Reader entry section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Read data
        printf("Reader %d read data: %d\n", reader_id, data);
        sleep(1);  // Simulating some reading time

        // Reader exit section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    while (1) {
        // Writer entry section
        sem_wait(&wrt);

        // Write data
        data++;
        printf("Writer %d wrote data: %d\n", writer_id, data);
        sleep(1);  // Simulating some writing time

        // Writer exit section
        sem_post(&wrt);
    }
}

int main() {
    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];

    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for threads to finish (which they won't because they run indefinitely)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    // Clean up semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}