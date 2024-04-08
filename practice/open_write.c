#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(){
    FILE *file;
    char *filename="abc.txt";
    int nonalpha=0;
    int ch;

    file=fopen(filename,"r+");
    if(file==NULL){
        perror("Error in opening file!!");
        return 0;
    }

    while((ch = fgetc(file)) != EOF){
        if(isalpha(ch)) {
            if(isupper(ch)) {
                ch = tolower(ch);
            } 
            else if(islower(ch)) {
                ch = toupper(ch);
            }
        } 
        else if(ch == '\n' || !isalpha(ch)) {
            nonalpha++;
        }
        putchar(ch);
    }

    printf("\nNon-alpha count is: %d\n", nonalpha-1);

    fclose(file);
    return 0;
}