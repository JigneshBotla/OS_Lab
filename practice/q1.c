#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>


int main(){
    int ch;
    int nonalpha=0;
    FILE *file = fopen("abc.txt", "r+");
    if(file==NULL){
        printf("Error in opening the file %s!\n", "abc.txt");
        return 0;
    }

    FILE *out = fopen("output.txt", "w+");
    if(out==NULL){
        fclose(file);
        printf("Error in creating the file %s!\n", "output.txt");
    }

    while((ch = fgetc(file)) != EOF){
        if(!isalpha(ch) || ch=='\n') {
            nonalpha++;
        }
        ch == islower(ch) ? toupper(ch) : tolower(ch);
        fputc(ch, out);
    }

    printf("non alpha count is :%d\n", nonalpha);

    fclose(out);
    fclose(file);

    return 0;
}