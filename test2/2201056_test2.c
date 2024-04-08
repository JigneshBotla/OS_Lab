#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <setjmp.h>
#include<time.h>

clock_t start,end;

jmp_buf env;

void handle_alarm(int signal) {
    printf("\nCalculation is taking too much time\n");
    longjmp(env, 1);
}

int is_prime(int n) {
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    
    for (int i = 5;  i*i<= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}


int main(){
    int x,y,z;
    printf("Enter the value of 'x' :");
    scanf("%d",&x);
    printf("Enter the value of 'y' :");
    scanf("%d",&y);
    printf("Enter the time for the alarm to wait :");
    scanf("%d",&z);

    pid_t pid = fork();
    float t_start = (float)clock() / CLOCKS_PER_SEC;

    if (pid < 0 || z<=0) {
        perror("Fork failed");
        exit(1);
    }
    
    
    else if (pid == 0) { 
        for (int i=x;i<=y;i++){
            if(is_prime(i)){
            printf("%d ",i);
            }
        }
        printf("\n");
        exit(0);
    }

    else {  
        if (setjmp(env) == 0) {
            signal(SIGALRM, handle_alarm);
            alarm(z);
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                printf("All the prime numbers printed\n");
            }
            float t_end = (float)clock() / CLOCKS_PER_SEC;
            printf("Time taken to complete the process : %f\n",t_end-t_start);
        } 
        else {

            kill(pid, SIGKILL);
        } 
    }

    return 0;
}

