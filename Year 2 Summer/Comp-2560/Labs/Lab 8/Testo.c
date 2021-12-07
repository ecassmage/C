//
// Created by evanm on 2021-07-19.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void catchint(int signo) {
    printf("\n CATCHINT: signo=%d\n", signo);
    printf("CATCHINT: returning\n\n");
}


int main()
{
    static struct sigaction act;

    void catchint(int);

    act.sa_handler = catchint;

    sigfillset(&(act.sa_mask));

    sigaction(SIGINT, &act, NULL);

    printf("sleep call #1\n");
    sleep(1);
    printf("sleep call #2\n");
    sleep(1);
    printf("sleep call #3\n");
    sleep(1);
    printf("sleep call #4\n");
    sleep(1);
    printf("Exiting \n");
    exit(0);
}