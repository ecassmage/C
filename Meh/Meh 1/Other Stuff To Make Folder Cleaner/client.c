//
// Created by evanm on 2021-08-17.
//

#include "socket.h"

int main(){
    skt *Skt = IP4ssSocket_c("192.168.0.101", 777);
    printf("Hello World From Client\n");
    write(getSocket(Skt), "Hello: From The Client\n", strlen("Hello: From The Client\n"));
    free(Skt);
    exit(0);
}