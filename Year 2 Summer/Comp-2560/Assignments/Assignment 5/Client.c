//
// Created by evanm on 2021-07-27.
//

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    int fd;
    int fdRead;
    char ch;
    char msg[25];

    while((fd=open("../myserver", O_WRONLY))==-1){
        fprintf(stderr, "trying to connect\n");
        sleep(1);
    }
    while((fdRead = open("../myclient", O_RDONLY)) == -1) {
        fprintf(stderr, "trying to connect\n");
        sleep(1);
    }
    printf("Connected: type in data to be sent\n");



    while((ch=getchar()) != -1){ // -1 is CTRL-D
        write(fd, &ch, 1);
        if (ch == '\n'){
            while (read(fdRead, &ch, 1) == 1){
                fprintf(stderr, "%c", ch);
                if (ch == '\n') break;
            }
        }
    }
    close(fd);
}
