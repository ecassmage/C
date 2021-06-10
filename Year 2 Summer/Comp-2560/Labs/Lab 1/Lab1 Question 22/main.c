#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void){
    printf("Hello, my PID is %d\n", getpid());  //Needs <unistd.h>
    printf("Hello, my PPID is %d\n", getppid());  //Needs <unistd.h>
    exit(0);  // <stdlib.h> for same reason as Question 20
}
