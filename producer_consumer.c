#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

// Shared buffer and associated variables
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Semaphores and mutex for synchronization
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

// Producer function
void *producer(void *arg) {
    while (1) {
        int item = rand() % 100; // Produce an item

        // Wait if the buffer is full (no empty slots)
        sem_wait(&empty);

        // Lock the mutex for safe access to the buffer
        pthread_mutex_lock(&mutex);

        // Place the item in the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        fflush(stdout); // Flush output immediately
        in = (in + 1) % BUFFER_SIZE; // Move the pointer

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Signal the consumer that the buffer is not empty
        sem_post(&full);

        // Reduce sleep time to increase output speed
        usleep(200000); // Sleep for 200 milliseconds (0.2 seconds)
    }

    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    while (1) {
        // Wait if the buffer is empty (no full slots)
        sem_wait(&full);

        // Lock the mutex for safe access to the buffer
        pthread_mutex_lock(&mutex);

        // Remove an item from the buffer
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        fflush(stdout); // Flush output immediately
        out = (out + 1) % BUFFER_SIZE; // Move the pointer

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Signal the producer that the buffer is not full
        sem_post(&empty);

        // Reduce sleep time to increase output speed
        usleep(200000); // Sleep for 200 milliseconds (0.2 seconds)
    }

    return NULL;
}

int main() {
    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (in this case, they run indefinitely)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
