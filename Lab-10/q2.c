// Implement the producer – consumer problem’s solution using semaphore.
// Use one producer thread and one consumer thread. Also, clearly define the produce_item() function and consume_item() function. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

sem_t empty, full, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void produce_item(int item) {
   
    printf("Produced: %d\n", item);
}

int consume_item() {
 
    int item = buffer[out];
    printf("Consumed: %d\n", item);
    return item;
}

void *producer(void *arg) {
    int item = 1;
    while (1) {
        // Produce an item
        produce_item(item);
       
        sem_wait(&empty);
        sem_wait(&mutex);

        // Add item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        item++;
    }
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = consume_item();
       
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t producer_thread, consumer_thread;

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (which they won't because they run indefinitely)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}