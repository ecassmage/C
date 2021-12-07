//
// Created by evanm on 2021-07-07.
//

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void child(int i, int argc, char *argv[]){
    printf("I am child: %d and I will be executing the %s command\n", getpid(), argv[i]);
    if (i + 1 >= argc) system(argv[i]);
    else {
        char *handle = (char*) calloc(((strlen(argv[i]) + strlen(argv[i+1])) + 2), sizeof(char));  // Creates a char array long enough to hold entire command line.
        strcat(handle, argv[i]);  // I gave up copy pasting my str.h header file and just use this annoying thing.
        strcat(handle, " "); // This concatenates a space onto the end of the command line.
        strcat(handle, argv[i+1]); // This concatenates the input onto the end of the command line.
        system(handle);  // This calls the Command Line.
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    pid_t pid = getpid();
    pid_t *pids = (pid_t*) calloc((argc / 2) + 1, sizeof(pid_t));
    int index = 0;
    for (int i = 1; i < argc; i+=2) {  // This Should loop expecting a command and an input
        pids[index++] = fork();
        if (pid != getpid()) child(i, argc, argv);
    }
    /// If this works how I hope it is, it should make sure that every child process has terminated before the parent terminates.
    for (int i = 0; i < index; i++) {
        if (pids[i] == 0) continue;
        if (waitpid(pids[i], NULL, WNOHANG) == 0) waitpid(pids[i], NULL, 0);
        else continue;
    }
}
