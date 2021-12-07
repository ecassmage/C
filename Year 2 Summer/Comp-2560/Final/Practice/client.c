//
// Created by evanm on 2021-08-11.
//

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "Sockets.h"
#include "error.h"
#include "str.h"




char NameOfClient[maxNameSize] = {'\0'};  // Mostly Pointless and can be switched out for better system but don't feel like it.
str *buffer = NULL;  // Hopefully if all goes well, this will allow me to store stuff up while still being able to write to console from socket.
skt *addr;


void quit(){
    system("stty cooked");
    send((*addr).socketFD, "%%//-quit\n", strlen( "%%//-quit\n")+1, 0);
    freeString(buffer);
    free(addr);
    exit(0);
}


void backSpace(){
    write(STDOUT_FILENO, backspace, strlen(backspace));
    if (len(buffer) > 0) {
        write(STDOUT_FILENO, backspace, strlen(backspace));
        removeNCharacter(buffer, len(buffer) - 1);
    }
}

str *bufferReader(){
    freeString(buffer);
    buffer = String();
    char buf;

    while (1){
        system("stty raw");
        read(STDIN_FILENO, &buf, 1);

        switch(buf){
            case 127:
                backSpace();
                continue;
            case '\r':
                printf("\n");
                buf = '\n';
                break;
            case 3:
                backSpace();
                quit();
                break;
            case 28:
                backSpace();
                kill(getpid(), SIGQUIT);
                break;
            case '\0':
                continue;
            default:
                break;
        }
        system("stty cooked");
        concatSC(buffer, buf);
        if (buf == '\n') {
            //printf("\n");
            return buffer;
        }
    }
}

void receiveMsg(){
    system("stty cooked");
    char buf = '\0';
    for (int loop = 0; loop < 3; loop++){
        if (loop == 1)  for(int i = 0; i < len(buffer) + strlen(clientTag); i++)    write(STDOUT_FILENO, " ", 1);
        else            for(int i = 0; i < len(buffer) + strlen(clientTag); i++)    write(STDOUT_FILENO, "\b", 1);
    }

    str *sentOverMessage = String();
    for (; buf != '\n'; read((*addr).socketFD, &buf, 1)) concatSC(sentOverMessage, buf);
    concatSC(sentOverMessage, '\n');

    write(STDOUT_FILENO, toCharArray(sentOverMessage), len(sentOverMessage));
    write(STDOUT_FILENO, clientTag, strlen(clientTag));
    write(STDOUT_FILENO, toCharArray(buffer), len(buffer));
    system("stty raw");
}

void CollectAndSendStr(skt *address, int flags){
    str *msg = bufferReader();
    if (strcmp(toCharArray(msg), "-quit\n") == 0) quit();
    else    send((*address).socketFD, toCharArray(msg), len(msg), flags);
}

void mainClient(int argc, char *argv[]){
    if (argc == 2)addr = SocketC(AF_INET, SOCK_STREAM, 0, argv[1], PORT);
    else addr = SocketC(AF_INET, SOCK_STREAM, 0, ServerIP, PORT);
    signal(SentMsgFromServer, receiveMsg);

    int tempPid = getpid();
    send((*addr).socketFD, &tempPid, sizeof(tempPid), 0);

    char msg[30];
    read((*addr).socketFD, msg, 30);    // Asks For Name
    write(STDOUT_FILENO, msg, 30);      // Asks For Name
    CollectAndSendStr(addr, 0);

    while (1){
        write(STDOUT_FILENO, clientTag, strlen(clientTag));
        CollectAndSendStr(addr, 0);  // Collect and Send Stuff
    }
}

int main(int argc, char *argv[]){
    mainClient(argc, argv);
    return 0;
}