//
// Created by evanm on 2021-07-26.
//

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <signal.h>
#include    <time.h>
#include    <sys/stat.h>
#include    <sys/types.h>

void child(int P[]){
    close(P[0]);
    write(P[1], "This is a Message\n", strlen("This is a Message\n"));
    exit(0);
}

void SIGPipe(){
    printf("We have failed to Read/Write To Pipe\n");
    exit(SIGPIPE);
}

int main(int argc, char *argv[]){
    int P[2];
    char buf[100];
    pipe(P);
    printf("Let Us Start\n");
    pid_t Child;
    signal(SIGPIPE, SIGPipe);
    switch (Child = fork()){
        case -1: exit(0);
        case 0: child(P);
        default: break;
    }
    close(P[0]);
    read(P[0], buf, strlen("This is a Message\n"));
}