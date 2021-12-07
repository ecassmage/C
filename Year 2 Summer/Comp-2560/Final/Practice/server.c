#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include "Sockets.h"
#include "error.h"
#include "str.h"
#include "queue.h"

int socketID = 0;
pid_t socketPid = 0;
str *NameOfClient;
int MasterPipe[2];
int CopyOfChildPipe[2];
queue *masterQueue;
char *getMessage(int PipeRead);

void receivedMessage(){
    char buf;
    str *string = String();

    printf("PID %d is Reading\n", getpid());

    while (read(CopyOfChildPipe[0], &buf, 1) > 0){
        concatSC(string, buf);
        if (buf == '\n')  break;
    }

    printf("PID %d is Sending\n", getpid());

    send(socketID, toCharArray(string), len(string), 0);
    freeString(string);
    kill(socketPid, SentMsgFromServer);

    printf("PID %d has Sent\n", getpid());
}

void sendMessage(str *message, int pipeMaster[2], int pipeFD[2], int signal){
    printf("Received and Sending Message\n");
    write(pipeFD[1], toCharArray(message), len(message));
    write(pipeMaster[1], &(pipeFD[0]), sizeof(pipeFD[0]));
    kill(getppid(), signal);
}

void printChars(str *fuckYou){
    for (int i = 0; i < len(fuckYou); i++){
        printf("<%c>", fuckYou -> string[i]);
    }
    printf("\n");
}

void childFork(int socketFD, int pipeMaster[2], int pipeFD[2]){
    CopyOfChildPipe[0] = pipeFD[0];
    CopyOfChildPipe[1] = pipeFD[1];
    socketID = socketFD;
    NameOfClient = String();
    char buf = '\0';


    write(socketFD, "Please Enter Your Name Here: ", strlen("Please Enter Your Name Here: ") + 1);

    for(; buf != '\n'; read(socketFD, &buf, 1)){// Runs a Chance of Failing Probably and not being detected as a failed read.
        if (buf == '\0') continue;
        concatSC(NameOfClient, buf);
    }
    concatSC(NameOfClient, '\n');
    sendMessage(NameOfClient, pipeMaster, pipeFD, ReadName);
    str *string = String();  // Will Hold the Messages being sent.
    while(read(socketFD, &buf, 1) > 0)  {
        if (buf == '\0') continue;
        concatSC(string, buf);
        if (buf == '\n'){
            if (strcmp(toCharArray(string), "%%//-quit\n") == 0) break;  // Breaks upon user wanting to quit
            sendMessage(string, pipeMaster, pipeFD, SentMsgFromClient);
            freeString(string);
            string = String();
        }
    }
    freeString(string);
    string = String();
    sendMessage(string, pipeMaster, pipeFD, LeftGroup);
    freeString(string);
    printf("PID %d is Exiting Process\n", getpid());
    sleep(2);
    close(pipeFD[1]);
    close(pipeFD[0]);
    close(pipeMaster[1]);
    close(pipeMaster[0]);
    exit(0);
}

void forkInstructions(int socketFD, int pipeMaster[2], int standardPipe[2]){
    pid_t child;
    pid_t clientPid;
    read(socketFD, &clientPid, sizeof(clientPid));
    switch(child = fork()){
        case -1:
            perror("Failed to Fork");
            exit(1);
        case 0:
            //Child
            socketPid = clientPid;
            childFork(socketFD, pipeMaster, standardPipe);
            break;
        default:{
            //Parent
            queueMember *temp = newQueueMember(standardPipe, NULL, child);
            addToQueue(masterQueue, temp);
            break;
        }
    }
}

char *getMessage(int PipeRead){
    printf("Received Message\n");
    char buf = '\0';
    str *tempStringContainer = String();
    for(; buf != '\n'; read(PipeRead, &buf, 1)){
        // Runs a Chance of Failing Probably and not being detected as a failed read.
        if (buf == '\0') continue;
        concatSC(tempStringContainer, buf);
    }
    char *temp = toCharArray(tempStringContainer);
    freeStringOnly(tempStringContainer);  // To Clean the Heap
    return temp;
}

void LeftGroupFunction(){
    int StandardReceived;
    read(MasterPipe[0], &StandardReceived, sizeof(StandardReceived));
    queueMember *ptr = masterQueue -> first;
    while (ptr -> pipeValues[0] != StandardReceived)    ptr = ptr -> prev;
    queueMember *ptr2 = ptr;
    ptr = masterQueue -> first;
    while(ptr != NULL && ptr2 != NULL){
        if (ptr != ptr2){
            str *stringTemp = String();
            concat(stringTemp, 2, ptr2 -> name, " Has Left The Group\n");
            write(ptr -> pipeValues[1], toCharArray(stringTemp), len(stringTemp)+1);
            kill(ptr -> Pid, SentMsgFromServer);
        }
        ptr = ptr -> prev;
    }
}

void ManagementForkWork(){
    queueMember *ptr = masterQueue -> first;
    int StandardPipe;
    read(MasterPipe[0], &StandardPipe, sizeof(StandardPipe));
    char *msg = getMessage(StandardPipe);
    char *name;
    while (ptr != NULL){
        if (ptr -> pipeValues[0] == StandardPipe)   name = ptr -> name;
        ptr = ptr -> prev;
    }
    ptr = masterQueue -> first;
    while (ptr != NULL){
        if (ptr -> pipeValues[0] != StandardPipe && ptr -> name != NULL){
            str *temp = mkString(name);
            concat(temp, 3, ": ", msg, "\n");
            write(ptr -> pipeValues[1], toCharArray(temp), len(temp)+1);
            kill(ptr -> Pid, SentMsgFromServer);
        }
        ptr = ptr -> prev;
    }
}
// <pipeWrite> <Name> <message>
// int pipeReturn = <pipeWrite>
// char *name = <Name>
// char *message = <message>
void ManagementFork(int sig){
    switch (fork()){
        case -1:
            perror("Failed to Fork");
            exit(1);
        case 0:
            if (sig == SentMsgFromClient)ManagementForkWork();
            else if (sig == LeftGroup) LeftGroupFunction();
            exit(0);
        default:
            break;
    }
}

void findForkedInformation(){
    int StandardReceived;
    read(MasterPipe[0], &StandardReceived, sizeof(StandardReceived));
    queueMember *ptr = masterQueue -> first;
    char *nim;
    while (ptr != NULL){
        if (ptr -> pipeValues[0] == StandardReceived){
            nim = getMessage(StandardReceived);
            setName(ptr, nim);
            printf("5 >> %s << 6\n", nim);
            break;
        } else  ptr = ptr -> prev;
    }
    queueMember *ptr2 = ptr;
    ptr = masterQueue -> first;
    while(ptr != NULL && ptr2 != NULL){
        if (ptr != ptr2 && ptr -> name != NULL){
            str *stringTemp = String();
            concat(stringTemp, 2, nim, " Has Entered The Chat\n");
            write(ptr -> pipeValues[1], toCharArray(stringTemp), len(stringTemp)+1);
            kill(ptr -> Pid, SentMsgFromServer);
        }
        ptr = ptr -> prev;
    }
}

void ManagerWork(){
    while (1){
        pause();
    }
}

void ServerWork(){
    skt *server = SocketS(AF_INET, SOCK_STREAM, 0, NULL, PORT);
    masterQueue = Queue();

    signal(ReadName, findForkedInformation);
    signal(SentMsgFromClient, ManagementFork); // Meant to Decrease Clients registered in Service
    signal(SentMsgFromServer, receivedMessage);
    signal(LeftGroup, ManagementFork);
    if (pipe(MasterPipe) < 0)    exit(2);

    printf("Completed Server Startup\n");
    while (1){
        int newSocket = acceptSocket(server);

        int P[2];  // Not sure if the pipe will break upon exiting the function from de-allocation so it will be created here.
        if (pipe(P) < 0)    exit(1);
        forkInstructions(newSocket, MasterPipe, P);
    }
}

int main() {
    ServerWork();
    return 0;
}
