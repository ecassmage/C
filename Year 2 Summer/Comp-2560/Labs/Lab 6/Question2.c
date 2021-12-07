//
// Created by evanm on 2021-07-08.
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void eWrite(FILE *fd, int size, char *message){
    fwrite(message, size, strlen(message), fd);
}

void readFile(FILE *fd){
    char buffer[2] = "\0\0";
    int i = 0;
    while (fread(buffer, 1, 1, fd) > 0) {
        printf("%s", buffer);
        i++;
    }
    printf("\nWe Found %d characters\n", i);
}

int main() {
    int num = 100;
    FILE *fd = fopen("text.txt", "r+");
    printf("The Parent FILE is Located HERE: %p, %p\n", fd, &num);
    readFile(fd);
    fseek(fd, 0, SEEK_SET);
    pid_t Parent = getpid();
    pid_t Child  = fork();
    printf("The Parent FILE is Located HERE: %p, %p\n", fd, &num);
    if (Child < 0) printf("\033[0;31mThis Has Failed Try Again Next Time\n\033[0m");
    if (Parent == getpid()){
        num = 1;
        waitpid(Child, NULL, 0);  // Make sure that the Child Completes its Task before the Parent Does.
        readFile(fd);
        printf("The Parent FILE is Located HERE: %p, %p\n", fd, &num);
        printf("If The Sections above are different then something went wrong\n");
        eWrite(fd, sizeof(char), "This is a Message to No One");
    }
    else {
        sleep(1);
        fclose(fd);
        num = 10;
        printf("The Child FILE is Located HERE: %p, %p\n", fd, &num);
        exit(0);
    }
    fclose(fd);
}