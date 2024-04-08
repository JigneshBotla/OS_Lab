#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int arg,char *argc[]){
    for(int i=1;i<arg;i++){
        if(argc[i][0]!='-'){
            printf("%s ",argc[i]);
        }
    }
    printf("\n");
    exit(0);
    
}