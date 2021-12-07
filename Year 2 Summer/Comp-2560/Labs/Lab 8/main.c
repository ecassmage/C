#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void ChildFunction(){
    printf("Hello World, I am Child Number: %d\n", getpid());
}
void ParentFunction(){
    printf("Hello This is Parent Speaking World: %d\n", getpid());
}
void parent_task(pid_t *child){
    kill(child[0], 64);
    kill(child[1], 64);
    sleep(5);
}
void child_task(){
    printf("The Child is Working Here\n");
    kill(getppid(), 63);
    sleep(1);
    exit(0);
}


int main() {
    char *buf[3];
    pid_t parent = getpid();
    pid_t child[2];
    buf[0] = "EXAM! EXAM! EXAM!\n";
    buf[1] = "HELP! HELP! HELP!\n";
    buf[2] = "STUDY! STUDY! STUDY!\n";
    printf("%s%s%s", buf[0], buf[1], buf[2]);
    signal(64, ChildFunction);
    signal(63, ParentFunction);

    //alarm(3);
    child[0] = fork();
    if (parent != getpid()) child_task();
    child[1] = fork();
    if (parent != getpid()) child_task();
    printf("I am Parent: %d and these are my Children: <%d, %d>\n", parent, child[0], child[1]);
    parent_task(child);
    sleep(10);
}