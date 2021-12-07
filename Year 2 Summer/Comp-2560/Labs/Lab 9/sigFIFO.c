//
// Created by evanm on 2021-07-26.
//

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <signal.h>
#include    <time.h>
#include    <sys/stat.h>
#include    <errno.h>
#include    <sys/types.h>


#define fifoFile "FIFOFILE"

void child(){
    sleep(2);
    int fd = open (fifoFile, O_RDONLY);
    // Darn this was annoying, fifo has too many safeguards to break it easily. had to quickly open it then close it before anything could be written to it.
    close(fd);
    exit(0);
}

void SIGFifo(){
    printf("We have failed to Read/Write To Pipe\n");
    exit(0);
}

void fifo(){
    if (mkfifo(fifoFile, 0777) < 0 && errno != EEXIST){
        exit(0);
    }
}

int main(int argc, char *argv[]){
    char buf[100];
    fifo();
    printf("Let Us Start\n");
    signal(SIGPIPE, SIGFifo);
    switch (fork()){
        case -1: exit(0);
        case 0: child();
        default: break;
    }
    int fd = open(fifoFile, O_WRONLY);
    sleep(2);
    write(fd, "This is a Message\n", strlen("This is a Message\n"));
}