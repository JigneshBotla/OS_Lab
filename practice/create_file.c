#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char filename[100]; 
    printf("Enter the name of the file: ");
    scanf("%s", filename);

    int fd = creat(filename, 0644); 

    if (fd == -1) {
        printf("Error in creating the file!\n");
        return 1;
    }

    printf("File created successfully!\n");  

    close(fd);

    return 0;
}