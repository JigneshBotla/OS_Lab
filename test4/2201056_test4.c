#include <stdio.h>
#include <pthread.h>
#include <ctype.h>

#define SIZE 50

char Input[SIZE];
char Output[SIZE];
int n;
int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *convert_Alphabets(void *arg) {
    int index;
    char str = (char )arg;

    pthread_mutex_lock(&mutex);
    index = counter++;
    pthread_mutex_unlock(&mutex);

    if (index < SIZE) {
       if (islower(str))
            Output[index] = str-32;
        else if (isupper(str))
            Output[index] = str+32;
    }
    
    return NULL;
}

int main() {
    printf("Enter the no of threads you want to generate: ");
    scanf("%d", &n);

    printf("Enter the Input string: ");
    scanf("%s", Input);

    pthread_t threadset[n];

    for (int i = 0; i < SIZE; i++)
        Output[i] = Input[i];

    for (int i = 0; i < n; i++)
        pthread_create(&threadset[i], NULL, convert_Alphabets, Input[i]);

    for (int i = 0; i < n; i++)
        pthread_join(threadset[i], NULL);

    printf("Converted string: %s\n", Output);

    return 0;
}
