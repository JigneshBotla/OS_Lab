#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_LIMIT 10

sem_t mutex;
sem_t full;
sem_t empty;
pthread_mutex_t producer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t consumer_mutex = PTHREAD_MUTEX_INITIALIZER;

int buffer[MAX_LIMIT];
int items_produced = 0;
int items_consumed = 0;

void *producer(void *producer_id) {
    int id = *(int *)producer_id;
    while (1) {
        pthread_mutex_lock(&producer_mutex);
        if (buffer[id] == 0) {
            sem_wait(&empty);
            sem_wait(&mutex);
            printf("produced item: %d\n", id);
            buffer[id] = 1;
            items_produced++;
            sem_post(&mutex);
            sem_post(&full);
        }
        pthread_mutex_unlock(&producer_mutex);
        if (items_produced == MAX_LIMIT)
            break; 
        sleep(1); 
    }
    pthread_exit(NULL);
}

void *consumer(void *consumer_id) {
    int id = *(int *)consumer_id;
    while (1) {
        pthread_mutex_lock(&consumer_mutex);
        if (buffer[id] == 1) {
            sem_wait(&full);
            sem_wait(&mutex);
            printf("consumed item: %d\n", id);
            buffer[id] = 0;
            items_consumed++;
            sem_post(&mutex);
            sem_post(&empty);
        }
        pthread_mutex_unlock(&consumer_mutex);
        if (items_consumed == MAX_LIMIT)
            break; 
        sleep(1); 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producers[MAX_LIMIT];
    pthread_t consumers[MAX_LIMIT];
    int id[MAX_LIMIT];

    for (int i = 0; i < MAX_LIMIT; i++) {
        buffer[i] = 0; 
    }

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, MAX_LIMIT);

    for (int i = 0; i < MAX_LIMIT; i++) {
        id[i] = i;
        pthread_create(&producers[i], NULL, producer, &id[i]);
        pthread_create(&consumers[i], NULL, consumer, &id[i]);

    }

    for (int i = 0; i < MAX_LIMIT; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    printf("All items produced and consumed.\n");

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
