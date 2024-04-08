#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while (1) {
        int fd1[2];
        int fd2[2];

        if (pipe(fd1) == -1 || pipe(fd2) == -1) {
            perror("pipe");
            return 1;
        }

        pid_t id = fork();
        if (id == -1) {
            perror("fork");
            return 1;
        } else if (id == 0) {
            pid_t id1 = fork();
            if (id1 == -1) {
                perror("fork");
                return 1;
            } else if (id1 == 0) {
                char c;
                printf("Enter any character in the first child process: ");
                scanf(" %c", &c);
                close(fd1[0]);
                if (write(fd1[1], &c, sizeof(char)) == -1) {
                    perror("write");
                    return 1;
                }
                printf("Writing character '%c' into pipe1 successful!\n", c);
                close(fd1[1]);
                exit(EXIT_SUCCESS);
            } else {
                wait(NULL);
                char c1;
                close(fd1[1]);
                if (read(fd1[0], &c1, sizeof(char)) == -1) {
                    perror("read");
                    return 1;
                }
                printf("Got character '%c' from pipe1!\n", c1);
                c1++;
                printf("Character is incremented to: '%c'\n", c1);
                close(fd1[0]);

                close(fd2[0]);
                c1 = c1 - 1;
                if (write(fd2[1], &c1, sizeof(char)) == -1) {
                    perror("write");
                    return 1;
                }
                printf("Writing of decremented character '%c' into pipe2 successful!\n", c1);
                close(fd2[1]);
                exit(EXIT_SUCCESS);
            }
        } else {
            wait(NULL);
            char c2;
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            if (read(fd2[0], &c2, sizeof(char)) == -1) {
                perror("read");
                return 1;
            }

            printf("Reading from pipe2 successful! Character decremented to :%c\n", c2);
            printf("Parent process terminated.\n");
        }
    }

    return 0;
}
