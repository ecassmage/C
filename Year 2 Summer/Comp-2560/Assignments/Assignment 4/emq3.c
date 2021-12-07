//
// Created by evanm on 2021-07-21.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>

void theAllNewAllInOneHandler(int aNumberThatIsNormal){
    printf("This is an Important Number So Be Careful: %d\n", aNumberThatIsNormal);
    switch (aNumberThatIsNormal){
        case 3:
            printf("I guess SIGQUIT\n");
            break;
        case 2:
            printf("I guess SIGINT\n");
            break;
        default:
            printf("I give Up\n");
            break;
    }
}

int main(int argc, char *argv[]) {
    signal(SIGINT, theAllNewAllInOneHandler);
    signal(SIGQUIT, theAllNewAllInOneHandler);
    while(1){sleep(1); }  // sleepy sleepy
}