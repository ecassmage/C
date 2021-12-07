//
// Created by evanm on 2021-08-18.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

skt *clientSocket(){
    skt *Skt = (skt*) malloc(sizeof(skt));
    Skt -> fd = socket(AF_INET, SOCK_STREAM, 0);

    Skt -> addr.sin_family = AF_INET;
    Skt -> addr.sin_addr.s_addr = inet_addr(serverIP);
    Skt -> addr.sin_port = PORT;

    error(connect(Skt -> fd, (struct sockaddr*) &(Skt -> addr), sizeof(Skt -> addr)), "Connection Error");

    return Skt;
}

int main(){
    int nums[2] = {10, 25};
    skt *serverSkt = clientSocket();
    printf("These are my 2 Numbers: {%d, %d}\n", nums[0], nums[1]);
    for (int i = 0; i < 2; i++){
        write(serverSkt -> fd, &nums[i], sizeof(nums[i]));
    }
    int numLargest = 0;
    read(serverSkt -> fd, &numLargest, sizeof(numLargest));
    printf("This is the Smaller Number To The Server: %d\n", numLargest);
    printf("Thank You. Client Terminated\n");
    exit(0);
}