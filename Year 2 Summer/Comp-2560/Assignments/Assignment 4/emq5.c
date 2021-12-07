//
// Created by evanm on 2021-07-22.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>

pid_t parent;
pid_t child;
#define SIGCONTINUE 34
#define pathFile "result.txt"

void childTasks(int pipe[], const char *command){
    FILE *fd = popen(command, "r");
    if (fd == NULL) exit(1);
    char buf;
    while ((buf = fgetc(fd)) != EOF){
        write(pipe[1], &buf, 1);
    }
    write(pipe[1], "\0", 1);
    pclose(fd);
    kill(parent, SIGCONTINUE);
    exit(0);
}

void dummyFunc(){}

int main(int argc, char *argv[]) {
    if (argc == 1)  exit(0);
    signal(SIGCONTINUE, dummyFunc);

    int num = 0;
    int Pipes[2];
    parent = getpid();

    if (pipe(Pipes) < 0) exit('p'/*hehehe*/);  // arg this gave me so much trouble for the simple fact I forgot to set up the pipe.
    if ((child = fork()) < 0) exit('f'/*hehehe*/);

    if (child == 0) {
        childTasks(Pipes, argv[1]);
    }
    else{
        pause();
        FILE *fd = fopen(pathFile, "w");
        char buf[] = "\0\0";

        while (read(Pipes[0], buf, 1) > 0) {
            if (buf[0] == '\0') break;
            fwrite(buf, 1, 1, fd);
            num++;
        }
        fclose(fd);
    }
    printf("The result of %s is written into %s with a total of %d bytes\n", argv[1], pathFile, num);
    close(Pipes[1]);
    close(Pipes[0]);
    exit(0);
}