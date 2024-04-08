#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void OPEN_CHECK() {
    int file = open("data2.txt", O_RDONLY);
    if (file != -1) {
        printf("File opened\n");
    } else {
        perror("Error in opening file");
    }
    close(file);
}

void CREATE_CHECK() {
    int file = creat("data3.txt", 0644);
    if (file != -1) {
        printf("File created\n");
    } else {
        perror("Error in creating file");
    }
    close(file);
}

void DUPLICATE_CHECK() {
    int originalFile = open("data2.txt", O_RDONLY);
    if (originalFile == -1) {
        perror("Error in opening file");
        return;
    }

    int copyFile = dup(originalFile);
    if (copyFile != -1) {
        printf("File copy successful\n");
    } else {
        perror("Error in copying file");
    }

    close(originalFile);
    close(copyFile);
}

void DUP2_CHECK() {
    int originalFile = open("data2.txt", O_RDONLY);
    if (originalFile == -1) {
        printf("Error in opening file");
        return;
    }

    int copyFile = open("data2_copy.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (copyFile == -1) {
        printf("Error in opening copy file");
        close(originalFile);
        return;
    }

    if (dup2(copyFile, STDOUT_FILENO) == -1) {
        printf("Error in duplicating file descriptor");
        close(originalFile);
        close(copyFile);
        return;
    }

    printf("\nThis goes to the copy file");

    close(originalFile);
    close(copyFile);
}

void PIPE_CHECK() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("\nError creating pipe");
        return;
    }

    char buffer[100];
    char *message = "Hello, P\n";

    if (write(pipe_fd[1], message, sizeof(message)) == -1) {
        perror("\nError writing to pipe");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return;
    }

    if (read(pipe_fd[0], buffer, sizeof(buffer)) == -1) {
        perror("\nError reading from pipe");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return;
    }

    printf("\nRead from pipe: %s\n", buffer);

    close(pipe_fd[0]);
    close(pipe_fd[1]);
}

int main() {
    OPEN_CHECK();
    CREATE_CHECK();
    DUPLICATE_CHECK();
    DUP2_CHECK();
    PIPE_CHECK();
    return 0;
}

