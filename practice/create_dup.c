#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<ctype.h>

int main(){
    int *file=creat("jignesh.txt",0644);
    if(file==-1){
        printf("Error in opening the file %s!\n", "abc.txt");
        return 0;
    }
    else{
        printf("file creation successful!!");
    }
}