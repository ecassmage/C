//
// Created by evanm on 2021-07-21.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>

void writeS(int fd, ...){
    ///  I heard somewhere it isn't a good idea to use printf with forks since something asynchronous stuff. so I am using something recommended which is write();
    va_list list;
    va_start(list, fd);
    for (char *chr = va_arg(list, char*); chr != NULL; write(fd, chr, strlen(chr)), chr = va_arg(list, char*));
    va_end(list);
}

int stringToIntConversion(const char *str){
    int num = 0;
    for (int i = 0; str[i] != '\0'; num = (num * 10) + ((int) str[i] - 48), i++);
    return num;
}
void alarmChildOverride(){
    kill(getppid(), SIGALRM);
}
void alarmParentOverride(){
    writeS(STDOUT_FILENO, "Ding\n", NULL);
}

void continueFunc(){}



int main(int argc, char *argv[]) {
    char *chr = "5";
    int num;
    if (argc == 1) {
        num = stringToIntConversion(chr);
        argv[1] = chr;  // just for testing
    }
    else if (argc == 2){
        num = stringToIntConversion(argv[1]);
    }
    pid_t child;
    signal(SIGCONT, continueFunc);
    switch(child = fork()){
        case -1:
            exit(0);
        case 0:
            signal(SIGALRM, alarmChildOverride);
            pause();
            alarm(num);
            writeS(STDOUT_FILENO, "<", argv[1], " second pause>\n", NULL);
            break;
        default:
            signal(SIGALRM, alarmParentOverride);
            writeS(STDOUT_FILENO, "Alarm application running\n", "Waiting for alarm to go off\n", NULL);
            kill(child, SIGCONT);
            break;
    }
    pause(); // Prevents any process from exiting naturally
    if (child == 0) {
        //writeS(STDOUT_FILENO, "Child has Completed and will now exit\n", NULL);   //This can be run to prove that the Child is exiting
    }
    else{
        //writeS(STDOUT_FILENO, "Parent has Completed and will now exit\n", NULL);  //This can be run to prove that the Parent is exiting
        printf("Done!\n");
    }

}