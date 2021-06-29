//
// Created by evanm on 2021-06-14.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void printPC(pid_t TopParentID){
    printf("My Parents PID is: %d, My Own PID is: %d, My Top Level Parents PID is: %d\n", getppid(), getpid(), TopParentID);  // Print Stuffs
}

void InBetween(pid_t HeadParent){
    if (HeadParent != getpid()){  // Checks if this is Head Parent. This Prevents the Top Level Parent from ever printing itself.
        printPC(HeadParent);  // Prints the Line asked.
        exit(0);  // Exits so That Children Can't Reproduce.
    }
}

int main() {  // I Don't think I need the extra stuff here since nothing is being passed as extra arguments.
    pid_t HeadParent = getpid();  // Saves the Top Level Parent Process ID. Because of Stack Copying stuff.
    if (fork() == -1) exit(0);  // Catches Failures
    InBetween(HeadParent);  // Calls an Intermediary
    if (fork() == -1) exit(0);  // Catches Failures
    InBetween(HeadParent);  // Calls an Intermediary
    if (fork() == -1) exit(0);  // Catches Failures
    InBetween(HeadParent);  // Calls an Intermediary
    sleep(5);  // Lab recommended it so I did it. Also kind of gives my process a little breathing room or something, dunno.
}

// Write a C program such that the parent process generates exactly 4 child processes.
// Each child process prints its pid and its parent's pid.
// Please put in comments in your code so that markers could understand your idea.
// You could also put in sleep() function if necessary to make sure child process terminates before the parent process.