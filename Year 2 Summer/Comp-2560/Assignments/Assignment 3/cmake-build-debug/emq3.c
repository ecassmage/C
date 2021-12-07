//
// Created by evanm on 2021-07-07.
//

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void child(int i, int argc, char *argv[]){
    if (i + 1 >= argc) system(argv[i]);
    else {
        char *handle = (char*) calloc(((strlen(argv[i]) + strlen(argv[i+1])) + 2), sizeof(char));
        strcat(handle, argv[i]);
        strcat(handle, " ");
        strcat(handle, argv[i+1]);
        system(handle);
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    pid_t pid = getpid();
    argc = 4;
    char *argv2[] = {"emq3", "cat", "emq3.c", "ls"};
    for (int i = 1; i < argc; i+=2) {
        fork();
        if (pid != getpid()) {
            child(i, argc, argv2);
        }
        else {
            //wait(NULL);
        }
    }
}
