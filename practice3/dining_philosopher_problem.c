#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

#define PHILOSOPHER_COUNT 5
int RICE_AVAILABLE;

sem_t chopstick[PHILOSOPHER_COUNT];
sem_t max_philosophers;
pthread_mutex_t rice_mutex = PTHREAD_MUTEX_INITIALIZER;


void *philosopher(void *id){
    int philosopher_id=*(int*)id;
    int left=philosopher_id;
    int right=(philosopher_id+1)%PHILOSOPHER_COUNT;
    while(RICE_AVAILABLE>0){
        sem_wait(&max_philosophers);
        sem_wait(&chopstick[left]);
        sem_wait(&chopstick[right]);

        pthread_mutex_lock(&rice_mutex);
        if (RICE_AVAILABLE > 0) {
            printf("Philosopher %d is eating\n", philosopher_id);
            sleep(1); 
            RICE_AVAILABLE--;
            printf("Available rice: %d\n", RICE_AVAILABLE);
        }
        pthread_mutex_unlock(&rice_mutex);

        sem_post(&chopstick[left]);
        sem_post(&chopstick[right]);
        sem_post(&max_philosophers); 
        printf("Philosopher %d is thinking\n", philosopher_id);
        sleep(1); 

    }
    return NULL;
}



int main(){
    pthread_t philosophers[PHILOSOPHER_COUNT];
    int ids[PHILOSOPHER_COUNT];
    sem_init(&max_philosophers, 0, PHILOSOPHER_COUNT - 1);
    printf("Enter the quantity of rice available in the dining room :");
    scanf("%d",&RICE_AVAILABLE);

    for (int i = 0; i < PHILOSOPHER_COUNT; i++) {
            sem_init(&chopstick[i], 0, 1); 
        }

    for (int i = 0; i < PHILOSOPHER_COUNT; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < PHILOSOPHER_COUNT; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;

}