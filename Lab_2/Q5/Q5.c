#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include<ctype.h>

void count() {
    int nonAlphaCount = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (!isalpha(ch) || ch == '\n') {
            nonAlphaCount++;
        }
        
	putchar(ch);
	
    }

    fprintf(stdout ,"Final non-alphabetic count: %d\n", nonAlphaCount-1);
    exit(0);
}

void convert() {
    int ch;

    while ((ch = getchar()) != EOF) {
        if (ch>='a' && ch<='z' ) {
            putchar(ch-32);
        }
	else if(ch>='A' && ch<='Z'){
	    putchar(ch+32);
	}
	else{
	    putchar(ch);
	}
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    int fd_in, fd_out, pipe_fd[2], status;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s temp1 temp2\n", argv[0]);
        exit(1);
    }

    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        perror("Error opening input file");
        exit(1);
    }

    fd_out = creat(argv[2], 0644);
    if (fd_out == -1) {
        perror("Error creating output file");
        close(fd_in);
        exit(1);
    }

    close(0);
    dup(fd_in);
    close(fd_in);

    close(1);
    dup(fd_out);
    close(fd_out);

    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        exit(1);
    }

    if (fork() != 0) {  
        if (fork() != 0) {  
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            wait(&status);
            wait(&status);
        } else {  
            close(pipe_fd[0]); 
            close(1);
            dup(pipe_fd[1]); 
            close(pipe_fd[1]); 
            execl("./convert", "convert", (char *)0);
        }
    } else {  
        close(pipe_fd[1]);
        close(0);
        dup(pipe_fd[0]); 
        close(pipe_fd[0]);  
        execl("./count", "count", (char *)0);
    }

    exit(0);
}
