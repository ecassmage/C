
#ifndef PRACTICE_SOCKETS_H
#define PRACTICE_SOCKETS_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "../../../Year 2 Summer/Comp-2560/Final/Practice/ClientServerHeader.h"


typedef struct{
    int socketFD;
    struct sockaddr_in addr;
}skt;

skt *Socket(int domain, int type, int protocol, const char *IPAddress, int port, int serverClient);
skt *SocketS(int domain, int type, int protocol, const char *IPAddress, int port);
skt *SocketC(int domain, int type, int protocol, const char *IPAddress, int port);

void connectSocket(skt *addr);
int acceptSocket(skt *addr);

void error(int num, const char *message){
    if (num < 0){
        perror(message);
        exit(1);
    }
}


/**
 * This Will Create a socket. If the socket will be used by the client then it will also connect to the server through here as well
 * @param domain
 * @param type
 * @param protocol
 * @param IPAddress
 * @param port
 * @param serverClient
 * @return
 */
skt *Socket(int domain, int type, int protocol, const char *IPAddress, int port, int serverClient){
    skt *address = (skt*) malloc(sizeof(skt));

    (*address).socketFD = socket(domain, type, protocol);

    (*address).addr.sin_family = domain;
    (*address).addr.sin_addr.s_addr = ( IPAddress == NULL ? INADDR_ANY : inet_addr(IPAddress) );
    (*address).addr.sin_port = htons(port);

    switch(serverClient) {
        case 1:
            error(bind((*address).socketFD, (struct sockaddr *) &((*address).addr), sizeof((*address).addr)), "Bind Error");  // The Error is just for checking if this failed to achieve a result, not an actual error unless bind fails.
            error(listen((*address).socketFD, 5), "Listen Failed");
            break;
        case 0:
            connectSocket(address);
            break;
        case 2:
            break;
        default:
            printf("Bad serverClient Value Given Only (0, 1, 2) accepted, {Given: %d}", serverClient);
            perror("");
            exit(1);
    }

    return address;
}

skt *SocketS(int domain, int type, int protocol, const char *IPAddress, int port){
    return Socket(domain, type, protocol, IPAddress, port, 1);
}

skt *SocketC(int domain, int type, int protocol, const char *IPAddress, int port){
    return Socket(domain, type, protocol, IPAddress, port, 0);
}

int acceptSocket(skt *addr){
    int newSocket;
    error((newSocket = accept((*addr).socketFD, (struct sockaddr*) &((*addr).addr), (socklen_t*) &((*addr).addr))), "Accept Failed");
    return newSocket;
}

void connectSocket(skt *addr){
    error(connect((*addr).socketFD, (struct sockaddr*) &((*addr).addr), sizeof((*addr).addr)), "Connect Failed");
}

#endif