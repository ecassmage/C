#include <stdio.h>
#include "socket.h"




int main() {
    skt *Skt = IP4ssSocket_s(NULL, 777, 5);
    printf("Going into StandBy Mode\n");
    int socket = newAccept(Skt);
    printf("Hello World\n");
    char buf;
    while (read(socket, &buf, 1) > 0){
        write(STDOUT_FILENO, &buf, 1);
        if (buf == '\n') break;
    }
    return 0;
}
