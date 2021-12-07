//
// Created by evanm on 2021-07-26.
//

#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <signal.h>
#include    <time.h>
#include    <sys/stat.h>
#include    <sys/types.h>
#include    <errno.h>

int fifoOpen[2];

void player(char *s, int FD[]);

int main(int argc, char *argv[]){
    if (mkfifo("FIFO", 0777) < 0 && errno != EEXIST){  // Errno should only be checked if mkfifo returns a bad creation.
        printf("Not Made File\n");
        exit(0);
    }
    else{
        printf("Success\n");
    }
    fifoOpen[1] = open("FIFO", O_WRONLY);   // Does this work, Dunno.
    printf("Opening\n");
    fifoOpen[0] = open("FIFO", O_RDONLY);   // Does this work, Dunno.
    printf("Opened\n");
    close(fifoOpen[1]);
    close(fifoOpen[0]);
    printf("Done\n");
    return 0;
}


void player(char *Player, int FD[]) {
    int Points = 0;
    int dice;
    long ss = 0;

}