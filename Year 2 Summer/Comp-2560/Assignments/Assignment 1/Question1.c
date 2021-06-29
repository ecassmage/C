//
// Created by evanm on 2021-06-11.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int openFile(char file[], char openChar){
    int fd = open(file, openChar);
    return fd;
}

int main(int argc, char *argv[]){
    if (argc == 1) {
        printf("Did Not Receive File Name\n");
        exit(0);
    }
    int fd = openFile(argv[1], 'r');
    printf("The Size of the file Given is: %ld\n", lseek(fd, 0, SEEK_END));
    close(fd);
    return 0;
}