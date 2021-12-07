#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void ChildrenCorner(){
    int i = 1;
    while (i == 1){
        sleep(5);
        printf("This is a Printedf\n");
    }
}

#define longLooooooop 1
int main() {
    pid_t parent = getpid();
    pid_t children[longLooooooop];
    for (int i = 0; i < longLooooooop; i++){
        children[i] = fork();
        if (getpid() != parent) break;
        else printf("PID for Child %d: %d\n", i, children[i]);
    }
    if (getpid() == parent) {for (int i = 0; i < longLooooooop; i++) if (waitpid(children[i], NULL, WNOHANG) == 0) waitpid(children[i], NULL, 0);}
    else ChildrenCorner();



    return 0;
}
