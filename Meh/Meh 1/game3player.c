//
// Created by evanm on 2021-07-26.
//

// I don't see the point of using pipes Here.

#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <signal.h>
#include    <time.h>

#define PlayerCount 3
#define CONT 34
pid_t Parent;
pid_t Children[PlayerCount];

void player(int num, int FD[]);
void signalContinue(int sig){}

int main(int argc, char *argv[]){
    int Pipe[2];  // Might need more pipes.
    if (pipe(Pipe) < 0) exit(0);
    signal(CONT, signalContinue);
    Parent = getpid();
    for (int i = 0; i < PlayerCount; i++){
        switch(Children[i] = fork()){
            case -1:    exit(0);
            case 0:     player(i+1, Pipe);   // child
            default:    break; // child
        }
    }
    sleep(1);
    while (1){
        for (int i = 0; i < PlayerCount; i++){
            printf("\nReferee: It is your move Player %d\n\n", i + 1);
            kill(Children[i], CONT);
            pause();
        }
    }
}

void player(int num, int FD[]){
    int Points = 0;
    int Dice;
    long int ss = 0;
//    long int ss = 0;  // I don't think necessary since NULL will just use real time.
    while (1){
        pause();
        printf("Player %d: playing my dice\n", num);
        Dice = (int) time(&ss) % 10 + 1;
        printf("Player %d: got %d points\n", num, Dice);
        Points += Dice;
        printf("Player %d: Total so far %d\n\n", num, Points);
        if(Points >= 50){
            printf("Player %d: game over I won\n", num);
            break;
        }
        else {
            sleep(3);
            kill(Parent, CONT);
        }
    }
    kill(0, SIGTERM);
}