#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>

int main() {
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

