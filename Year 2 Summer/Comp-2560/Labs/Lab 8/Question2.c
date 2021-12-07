//
// Created by evanm on 2021-07-19.
//

/*
 *  Name: Evan Morrison
 *  ID: 110043572
 *  Section: 51
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

#define AUTOMORE 1  // 1 for yes: do more automatically, 0 for no: do not do more automatically.  Basically Print to Terminal More
pid_t parent;  // Holds the Universal Original Parent pid_t. because I didn't want to have to pass it at some point.
char *buf[3] = {
        "EXAM! EXAM! EXAM!\n",
        "HELP! HELP! HELP!\n",
        "STUDY! STUDY! STUDY!\n"
};  // This holds the three lines separately

void writeStuff(int fd, const char *line){
    write(fd, line, strlen(line));  // Writes to file
    close(fd);  // Closes file.
    if (getpid() != parent) {  // Makes sure to not get parent confused with child.
        printf("%d has written to file: %s\n", getpid(), line);  // When this prints it will have two \n since there is 1 in the buf already. Didn't want to rely on the one given since not all inputs might have it and then it would just be printed on 1 line
        kill(parent, 34);  // Kills the parent to go ahead with next child
    }
    else printf("Parent has written to file: %s\nParent Closed the File\n", line);  // Prints a message for the parent
}
void dummyFunction(){printf("Hello\n");}  // Dummy function not useful what so ever

void allTasks(int fd, const char *line, const pid_t processes[]){
    if (parent == getpid()){ // These are the parent tasks
        for(int i = 0; i < 2; i++){
            char fake;
            kill(processes[i], 34);  // sends a signal to each child saying it is their turn to write pretty much. it actually just stops the pause function they are currently paused at.
            pause();
            //read(STDOUT_FILENO, &fake, 1);
        }
        writeStuff(fd, line); // Writes to some stuff to a file
    }
    else {// These are the child tasks

        //read(STDOUT_FILENO, &fake, 1);  // Pauses waiting for go ahead from parent
        pause();
        writeStuff(fd, line);// Writes to some stuff to a file
    }
}



int main(int argc, char *argv[]){
    if (argc == 1) {
        printf("Exited early due to no file\n");
        exit(0); // Exit early if no file was given
    }
    parent = getpid();
    pid_t processes[2];
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0700);
    printf("parent opened file: %s\n", argv[1]);
    signal(34, dummyFunction);  // I dunno really what I am doing but this should possibly break the pause without actually doing anything.
    for (int i = 0; i < 2; i++){
        if(parent == getpid()){
            switch(processes[i] = fork()){
                case -1:
                    perror("Failure");  // gives error message or something
                    exit(1);
                case 0:
                    allTasks(fd, buf[i], processes);  // Sends child to allTasks
                    break;
                default:
                    printf("Parent Created Child Process: %d\n", processes[i]);
                    break;
            }
        }
    }
    allTasks(fd, buf[2], processes);    // Sends Parent to allTasks  not necessary but I wasn't thinking when I was doing this. I could have kept them separate

    if (AUTOMORE){ // This automatically does the more stuff Don't know why I did this but I did.
        char *moreLine = (char*) calloc(6 + strlen(argv[1]), sizeof(char));
        if (moreLine == NULL) exit(0);// This is to catch if this quick form fails.
        printf(">>>>> more %s\n", argv[1]); // This is auto more.
        strcat(moreLine, "more ");
        strcat(moreLine, argv[1]);
        system(moreLine);
        printf("All Done\n>>>>>\n");

    }

}

