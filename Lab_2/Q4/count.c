#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>
int main() {
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

