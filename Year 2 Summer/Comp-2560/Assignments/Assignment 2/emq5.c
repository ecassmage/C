//
// Created by evanm on 2021-06-26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h>

void childFunction(char *line){
    write(STDOUT_FILENO, "I am a child working for my parent for free: ", strlen("I am a child working for my parent for free: "));

    int num1, num2;
    char character;
    char buffer[100] = {'\0'};

    if (sscanf(line, "%d %c %d", &num1, &character, &num2) != 3) exit(50);

    switch (character){
        case '+':
            sprintf(buffer, "%d %c %d = %d\n", num1, character, num2, num1 + num2);
            break;

        case '-':
            sprintf(buffer, "%d %c %d = %d\n", num1, character, num2, num1 - num2);
            break;

        case '*':
            sprintf(buffer, "%d %c %d = %d\n", num1, character, num2, num1 * num2);
            break;

        case '/':
            if (num2 == 0) exit(100);
            sprintf(buffer, "%d %c %d = %d\n", num1, character, num2, num1 / num2);
            break;

        default:
            exit(200);
    }
    write(STDOUT_FILENO, buffer, strlen(buffer));
    exit(0);
}

int main(){
    pid_t Parent = getpid();
    pid_t waiting;
    char buffer[100] = {'\0'};
    while (1){ // Infinite Loop
        write(STDOUT_FILENO, "This program makes simple arithmetics: ", strlen("This program makes simple arithmetics: "));
        read(STDIN_FILENO, buffer, 100);
        if (fork() == -1) {
            write(STDOUT_FILENO, "Failed to Create a Child Process:(\n", strlen("Failed to Create a Child Process:(\n"));
            exit(0);
        }
        if (Parent != getpid())
            childFunction(buffer);
        else{
            wait(&waiting);
            switch (waiting >> 8){
                case 50:
                    write(STDOUT_FILENO, "Wrong Statement\n", strlen("Wrong Statement\n"));
                    break;
                case 100:
                    write(STDOUT_FILENO, "Division By Zero\n", strlen("Division By Zero\n"));
                    break;
                case 200:
                    write(STDOUT_FILENO, "Wrong Operator\n", strlen("Wrong Operator\n"));
                    break;
                default:
                    break;
            }
        }
    }
}