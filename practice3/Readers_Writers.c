#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define WRITER_COUNT 3
#define READER_COUNT 5

sem_t mutex;
sem_t wrt;
int readcount = 0;

void *writer(void *writer_id) {
    int id = *(int *)writer_id;

    while (1) {
        sem_wait(&wrt);
        printf("Writer %d is writing\n", id);
        sem_post(&wrt);
        sleep(1); 
    }
    return NULL;
}

void *reader(void *reader_id) {
    int id = *(int *)reader_id;

    while (1) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);
        printf("Reader %d is reading\n", id);
        sem_wait(&mutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);
        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t writers[WRITER_COUNT];
    pthread_t readers[READER_COUNT];
    int writers_id[WRITER_COUNT];
    int readers_id[READER_COUNT];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < WRITER_COUNT; i++) {
        writers_id[i] = i;
        pthread_create(&writers[i], NULL, writer, &writers_id[i]);
    }
    printf("\n");
    for (int i = 0; i < READER_COUNT; i++) {
        readers_id[i] = i;
        pthread_create(&readers[i], NULL, reader, &readers_id[i]);
    }

    for (int i = 0; i < WRITER_COUNT; i++) {
        pthread_join(writers[i], NULL);
    }

    for (int i = 0; i < READER_COUNT; i++) {
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
