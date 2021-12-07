#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


void weDidIt(){
    write(STDOUT_FILENO, "I have taken your CTRL-C Hostage, HAHAHA!!!\n", strlen("I have taken your CTRL-C Hostage, HAHAHA!!!\n"));
}


int main(int argc, char *argv[]) {
    /// Remember Evan, SIGSTP doesn't seem to exist on my pc. Test this in NoMachine At some point.
    signal(SIGINT, weDidIt);  // Since the signals can change based on os/terminal I am just gonna use the Short Name.
    signal(SIGSTOP, weDidIt);  // Since the signals can change based on os/terminal I am just gonna use the Short Name.
    pid_t child = fork();
    if (child == 0){
        switch(argc){
            case 1:     execl("donothing.exe", "donothing", NULL);  break;
            case 2:     execl(argv[1], "donothing", NULL);          break;
            default:    execvp(argv[1], &argv[2]);              break;
        }
    }
    else{
        while(1){sleep(1);}
    }
    return 0;
}

/*
 * Based on observations, it seems while
 */
