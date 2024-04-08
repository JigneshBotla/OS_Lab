#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE 5

int nums[MAX_SIZE];

void *sort_array(void *arg) {
    
    int *array = (int *)arg;
    int x=sizeof(array)/sizeof(int);
    printf("size:%d\n",x);
    for (int i = 0; i < sizeof(array)/sizeof(int); i++) {
        for (int j = i + 1; j <sizeof(array)/sizeof(int); j++) {
            if (array[j] < array[i]) {
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
    }

    
    return NULL;
}

int main() {
    printf("Enter the numbers of the array of size %d:", MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++) {
        scanf("%d", &nums[i]);
    }
    int mid = MAX_SIZE/2;
    int half1[MAX_SIZE / 2];
    int half2[MAX_SIZE - mid]; 
    for (int i = 0; i < MAX_SIZE / 2; i++) {
        half1[i] = nums[i];
    }

    for (int i = MAX_SIZE / 2; i < MAX_SIZE; i++) {
        half2[i - MAX_SIZE / 2] = nums[i];
    }
    int x=sizeof(half1)/sizeof(int);
    printf("size:%d\n",x);
    int y=sizeof(half2)/sizeof(int);
    printf("size:%d\n",y);
    // for (int i = 0; i < MAX_SIZE/2; i++) {
    //     printf("%d ",half1[i]);
    // }
    // for (int i = 0; i < sizeof(half2)/sizeof(int); i++) {
    //     printf("%d ",half2[i]);
    // }
    
    
    pthread_t sort_firsthalf;
    pthread_t sort_secondhalf;
    
    pthread_create(&sort_firsthalf, NULL, sort_array, half1);
    pthread_create(&sort_secondhalf, NULL, sort_array, half2);


    pthread_join(sort_firsthalf, NULL);
    pthread_join(sort_secondhalf, NULL);

    printf("Sorted First Half: ");
    for (int i = 0; i < MAX_SIZE / 2; i++) {
        printf("%d ", half1[i]);
    }
    printf("\n");

    printf("Sorted Second Half: ");
    for (int i = 0; i < MAX_SIZE - (MAX_SIZE / 2); i++) { 
        printf("%d ", half2[i]);
    }
    printf("\n");

    printf("FINAL Sorted Array: ");
    int FINAL[MAX_SIZE];
    int i = 0, j = 0, k = 0;
    while (i < MAX_SIZE / 2 && j < MAX_SIZE - (MAX_SIZE / 2)) { 
        if (half1[i] <= half2[j]) {
            FINAL[k++] = half1[i++];
        } else {
            FINAL[k++] = half2[j++];
        }
    }
    while (i < MAX_SIZE / 2) {
        FINAL[k++] = half1[i++];
    }
    while (j < MAX_SIZE - (MAX_SIZE / 2)) {
        FINAL[k++] = half2[j++];
    }
    
    for (int i = 0; i < MAX_SIZE ; i++) {
        for (int j = i + 1; j < MAX_SIZE ; j++) {
            if (FINAL[j] < FINAL[i]) {
                int temp = FINAL[j];
                FINAL[j] = FINAL[i];
                FINAL[i] = temp;
            }
        }
    }

    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", FINAL[i]);
    }
    printf("\n");

    return 0;
}
