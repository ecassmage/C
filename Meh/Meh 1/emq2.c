//
// Created by evanm on 2021-08-18.
//
/// Server
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#define serverIP "192.168.0.101"
#define PORT 7777 //49152
#define BackLog 5


void error(int num, char *message){
    if (num < 0){
        perror(message);
        exit(0);
    }
}

typedef struct{
    int fd;
    struct sockaddr_in addr;
} skt;

skt *serverSocket(){
    skt *Skt = (skt*) malloc(sizeof(skt));
    Skt -> fd = socket(AF_INET, SOCK_STREAM, 0);

    Skt -> addr.sin_family = AF_INET;
    Skt -> addr.sin_addr.s_addr = INADDR_ANY;
    Skt -> addr.sin_port = PORT;

    error(bind(Skt -> fd, (struct sockaddr*) &(Skt -> addr), sizeof(Skt -> addr)), "Bind Error");
    error(listen(Skt -> fd, BackLog), "Bind Error");

    return Skt;
}

int acceptSocket(skt *Skt){
    int clientFD = accept(Skt -> fd, (struct sockaddr *) &(Skt -> addr), (socklen_t*) &(Skt -> addr));
    error(clientFD, "Accepting Error");
    return clientFD;
}

int main(){
    skt *serverSkt = serverSocket();
    printf("Server In Standby Mode\n");  // So I know it has been built correctly
    int Client = acceptSocket(serverSkt);
    printf("Client Connected successfully\n");
    int nums[2];
    for (int i = 0; i < 2; i++){
        read(Client, &nums[i], sizeof(nums[i]));
    }
    printf("The Two integers received are: {%d, %d}\n", nums[0], nums[1]);
    printf("I will find the bigger one and let the client know.\n");
    nums[0] < nums[1] ? write(Client, &nums[0], sizeof(nums[0])) : write(Client, &nums[1], sizeof(nums[1]));
    printf("Server Terminated\n");
    exit(9);
}