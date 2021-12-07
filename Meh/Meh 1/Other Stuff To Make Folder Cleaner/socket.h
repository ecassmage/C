//
// Created by evanm on 2021-08-17.
//

#ifndef C_SOCKET_H
#define C_SOCKET_H


#ifndef _UNISTD_H_
    #include <unistd.h>
#endif

#ifndef _STDIO_H_
    #include <stdio.h>
#endif

#ifndef _SYS_SOCKET_H
    #include <sys/socket.h>
#endif

#ifndef _STDLIB_H_
    #include <stdlib.h>
#endif

#ifndef _NETINET_IN_H
    #include <netinet/in.h>
#endif

#ifndef _ARPA_INET_H
    #include <arpa/inet.h>
#endif

#ifndef _STRING_H_
    #include <string.h>
#endif


typedef struct{
    int socketFD;
    struct sockaddr_in addr;
}skt;

void error(int num, const char *message){
    if (num < 0){
        perror(message);
        exit(1);
    }
}


int getSocket(skt*);
struct sockaddr_in getSktStruct(skt*);
int len(skt*);

skt *setSocket();
skt *sSocket();

skt *IP4ssSocket_s(const char*, int, int);
skt *sIP4ssSocket_s(skt*, const char*, int, int);
skt *IP4ssSocket_c(const char*, int);
skt *sIP4ssSocket_c(skt*, const char*, int);


int getSocket(skt *Skt){return Skt -> socketFD;}
struct sockaddr_in getSktStruct(skt *Skt){return Skt -> addr;}
int len(skt *Skt){return (int) sizeof(getSktStruct(Skt));}


struct sockaddr *toSockAddr(skt *Skt){
    return (struct sockaddr*) &(Skt -> addr);
}

skt *setSocket(){
    skt *Skt = (skt*) malloc(sizeof(skt));
    return Skt;
}

/**
 * Naming Convention for IP4ssSocket
 * IP4: IPv4 type
 * ss: SOCK_STREAM
 * Socket: socket(); + some other initializations.
 *
 * @param Skt Takes the skt structure found in this header.
 * @param ipAddress Takes an IP Address
 * @param port takes the port number
 * @return returns the skt past to this function. Doesn't need to be recovered if you already are pointing to it.
 */
static skt *IP4ssSocket(skt *Skt, const char *ipAddress, int port){
    Skt -> socketFD = socket(AF_INET, SOCK_STREAM, 0);

    Skt -> addr.sin_family = AF_INET;
    Skt -> addr.sin_addr.s_addr = ipAddress == NULL ? INADDR_ANY : inet_addr(ipAddress);
    Skt -> addr.sin_port = htons(port);

    return Skt;
}

/**
 * Naming Convention for IP4ssSocket
 * IP4: IPv4 type
 * ss: SOCK_STREAM
 * Socket: socket(); + some other initializations.
 * _s: server
 *
 * @param Skt Takes the skt structure found in this header.
 * @param ipAddress Takes an IP Address
 * @param port takes the port number
 * @return returns the skt past to this function. Doesn't need to be recovered if you already are pointing to it.
 */
skt *IP4ssSocket_s(const char *ipAddress, int port, int backlog){ return sIP4ssSocket_s(setSocket(), ipAddress, port, backlog); }
skt *sIP4ssSocket_s(skt *Skt, const char *ipAddress, int port, int backlog){
    IP4ssSocket(Skt, ipAddress, port);
    error(bind(getSocket(Skt), toSockAddr(Skt), sizeof(getSktStruct(Skt))), "Binding Error");
    error(listen(getSocket(Skt), backlog), "Listening Error");

    return Skt;
}

/**
 * Naming Convention for IP4ssSocket
 * s: skt structure is a parameter.
 * IP4: IPv4 type
 * ss: SOCK_STREAM
 * Socket: socket(); + some other initializations.
 * _c: client
 *
 * @param Skt Takes the skt structure found in this header.
 * @param ipAddress Takes an IP Address
 * @param port takes the port number
 * @return returns the skt past to this function. Doesn't need to be recovered if you already are pointing to it. Returns NULL if failed.
 */
skt *IP4ssSocket_c(const char *ipAddress, int port){
    skt *temp = setSocket();
    if (sIP4ssSocket_c(temp, ipAddress, port) == NULL) {
        free(temp);
        return NULL;
    }
    return temp;
}
skt *sIP4ssSocket_c(skt *Skt, const char *ipAddress, int port){
    IP4ssSocket(Skt, ipAddress, port);
    if (connect(getSocket(Skt), toSockAddr(Skt), len(Skt)) < 0) return NULL;

    return Skt;
}


int newAccept(skt *Skt){
    int newSocket;
    error((newSocket = accept(getSocket(Skt), toSockAddr(Skt), (socklen_t*) &(Skt -> addr))), "Accept Failed");
    return newSocket;
}

#endif //C_SOCKET_H
