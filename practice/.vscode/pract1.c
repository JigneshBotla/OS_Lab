#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char *argv[]) {
    int fd[2];
    int fd1[2];
    
    
    if (pipe(fd) == -1 || pipe(fd1)==-1) {
        perror("pipe");
        return 1;
    }
    
    pid_t id = fork();
    if (id == -1) {
        perror("fork");
        return 1;
    }
    else if (id == 0) { 
        int x;
        close(fd[1]); 
        read(fd[0], &x, sizeof(int));
        printf("Received number from parent process: %d\n", x); 
        close(fd[0]); 
        int y = x * x;
        printf("Sending squared number to parent process: %d\n", y);
        write(fd1[1], &y, sizeof(int));
    }
    else { 
        int x = rand()%10;
        close(fd[0]);
        printf("Generated number in parent process: %d\n", x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]); 
        wait(NULL); 
        int y;
        read(fd1[0], &y, sizeof(int));
        printf("Received squared number from child process: %d\n", y);
    }

    return 0;
}
