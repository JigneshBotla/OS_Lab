#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 

int main() { 
    int fd; 

    fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
    if (fd == -1) { 
        perror("open"); 
        return 1; 
    } 
    write(fd, "Hello, World!", 13); 
    close(fd); 

    fd = creat("file2.txt", 0644); 
    if (fd == -1) { 
        perror("creat"); 
        return 1; 
    } 
    write(fd, "This is the creat() system call.", 30); 
    close(fd); 

    int new_fd = dup(fd); 
    if (new_fd == -1) { 
        perror("dup"); 
        return 1; 
    } 
    printf("Original FD: %d, Duplicated FD: %d\n", fd, new_fd); 

    int new_fd2 = dup2(fd, new_fd); 
    if (new_fd2 == -1) { 
        perror("dup2"); 
        return 1; 
    } 
    printf("Original FD: %d, Duplicated FD: %d\n", fd, new_fd2); 

    int pipe_fd[2]; 
    if (pipe(pipe_fd) == -1) { 
        perror("pipe"); 
        return 1; 
    } 
    write(pipe_fd[1], "Data sent through pipe", 22); 
    char buffer[50]; 
    read(pipe_fd[0], buffer, sizeof(buffer)); 
    printf("Data received from pipe: %s\n", buffer); 
    return 0;
     
}