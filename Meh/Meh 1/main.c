//
// Created by evanm on 2021-08-18.
//
#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <signal.h>
#include    <time.h>
#include    <errno.h>

// Parent to child 1 == Signals
// Parent to Child 2 == Fifo / Pipe

int win = 0;

#define winningScore 10
#define numPlayers 2
#define Child1 34
#define GameOver 35
#define sleepTime 3
#define FIFOName "FIFO"

void playerSig();
void playerPipe(int p[], char *fifo);

void NotADummyFunc(int sig){
    if (sig == GameOver)    win = 1;
}

int main(int argc, char *argv[]){
    signal(Child1, NotADummyFunc);
    signal(GameOver, NotADummyFunc);
    unlink(FIFOName);

    int forkPid[numPlayers];
    int fd[2];
    int fdChild;
    char start = 'G';
    if (mkfifo(FIFOName, 0777) < 0 && errno != EEXIST) {
        printf("This is a Failed FIFO Error\n");
        exit(0);
    }
    if (pipe(fd) < 0) exit(0);


    for (int i = 0; i < numPlayers; i++) {
        switch (forkPid[i] = fork()) {
            case -1:
                exit(0);
            case 0:
                if (i == 0) playerSig();
                else playerPipe(fd, FIFOName);
                break;
            default:
                if (i > 0) {
                    fdChild = open(FIFOName, O_WRONLY);
                }
                break;
        }
    }

    char buf;
    while(1){
        printf("Referee: PlayerSig is Next\n");
        kill(forkPid[0], Child1);  // Tells Child 1 It is Okay To Run
        pause();  // Pauses for Parent to Say It is Okay
        if (win == 1) {
            printf("PlayerSig Won\n");
            break;
        }
        printf("Referee: PlayerPipe is Next\n");
        write(fdChild, &start, 1);
        read(fd[0], &buf, 1);
        if (buf == 'W') {
            printf("PlayerPipe Won\n");
            break;
        }
    }
    kill(0, SIGTERM);
    close(fd[0]);
    close(fd[1]);
    close(fdChild);
}

void playerSig(){
    int Points = 0;
    int Dice;
    long int ss = 0;
    char *name = "PlayerSig";
    while (1){
        pause();  // Pauses for Parent to Say It is Okay
        printf("%s: playing my dice\n", name);
        Dice = (int) time(&ss) % 10 + 1;
        printf("%s: got %d points\n", name, Dice);
        Points += Dice;
        printf("%s: Total so far %d\n\n", name, Points);
        if (Points >= winningScore) break;

        sleep(3);
        kill(getppid(), Child1);  // Tells parent to Proceed
    }
    kill(getppid(), GameOver);  // Tells parent That They Won. No Lying Here.
    exit(0);
}

void playerPipe(int p[], char *fifo){
    int Points = 0;
    int Dice;
    long int ss = 0;
    char *name = "PlayerPipe";
    int fd = open(fifo, O_RDONLY);
    close(p[0]);
    char buf;
    while (1){
        read(fd, &buf, 1);
        printf("%s: playing my dice\n", name);
        Dice = (int) time(&ss) % 10 + 1;
        printf("%s: got %d points\n", name, Dice);
        Points += Dice;
        printf("%s: Total so far %d\n\n", name, Points);
        if (Points >= winningScore)break;

        sleep(sleepTime); // Sleep Time
        write(p[1], "D", 1);
    }
    write(p[1], "W", 1);
    close(p[1]);
    close(fd);
    exit(0);
}
