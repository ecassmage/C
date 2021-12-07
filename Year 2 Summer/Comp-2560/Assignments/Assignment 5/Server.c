//
// Created by evanm on 2021-07-27.
//
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

// This is the server
int main(int argc, char *argv[]){
    int fd;
    int fdWrite;
    char ch;
    char *confrmMsg = "I received your message\n";

    unlink("../myserver"); // delete it if it exists
    unlink("../myclient"); // delete it if it exists

    if(mkfifo("../myserver", 0777)!=0)
        exit(1);
    if(mkfifo("../myclient", 0777)!=0)
        exit(1);
    while(1){
        fprintf(stderr, "Waiting for a client\n");

        fd = open("../myserver", O_RDONLY);
        sleep(1);
        fdWrite = open("../myclient", O_WRONLY);
        fprintf(stderr, "Got a client: ");

        while(read(fd, &ch, 1) == 1){
            fprintf(stderr, "%c", ch);
            if (ch == '\n'){
                sleep(1); //for suspense
                write(fdWrite, confrmMsg, strlen(confrmMsg));
            }
        }

    }
}

