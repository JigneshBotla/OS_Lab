#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

jmp_buf env;

void handler(int signo) {
    fprintf(stderr, "Received signal %d\n", signo);
    longjmp(env, 1);
    exit(1);
}

void count() {
    int nonAlphaCount = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (!isalpha(ch) || ch == '\n') {
            nonAlphaCount++;
        }

        putchar(ch);
    }

    fprintf(stdout, "Final non-alphabetic count: %d\n", nonAlphaCount - 1);
    exit(0);
}

void convert() {
    int ch;

    while ((ch = getchar()) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            putchar(ch - 32);
        } else if (ch >= 'A' && ch <= 'Z') {
            putchar(ch + 32);
        } else {
            putchar(ch);
        }
    }

    exit(0);
}

int main(int argc, char *argv[]) {
    pid_t pid, count_pid, convert_pid;
    int status;
    signal(SIGALRM, handler);

    if (setjmp(env) != 0) {
        fprintf(stderr, "Exiting due to signal\n");
        exit(1);
    }


    alarm(15);

    while ((pid = wait(&status)) > 0) {
        fprintf(stderr, "Child pid=%d reaped with exit status=%d\n", pid, WEXITSTATUS(status));
        if (pid == count_pid && WEXITSTATUS(status) == 2) {
            kill(convert_pid, SIGTERM);
        }
    }

    alarm(0);
    fprintf(stderr, "All child process count and convert ran successfully\n");
    exit(0);
}

