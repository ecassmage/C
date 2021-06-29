//
// Created by evanm on 2021-06-14.
//

#include <stdio.h>
#include <unistd.h>

int main(){  int i;
    printf("before fork, my pid is %d\n" , getpid());
    for (i=0; i<4; i++){
        if ( fork() == 0 )
            printf("Hi, I am child. My pid is %d\n", getpid());
    }
}