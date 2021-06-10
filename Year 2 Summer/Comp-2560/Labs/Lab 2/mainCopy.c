#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    char buffer[100];
    long int n1 = 0;
    int fd1, fd2;

    char chr[100] = {"Hello.txt"};
    char chr2[100] = {"output.txt"};
    if(((fd1 = open(chr, O_RDONLY)) == -1) ||  ((fd2 = open(chr2, O_CREAT|O_WRONLY|O_TRUNC,0700)) == -1)){
        perror("file problem ");
        exit(1);
    }
    int i = 0;
    while((n1=read(fd1, buffer, 1) > 0)) {
        if (write(fd2, buffer, n1) != n1) {
            perror("writing problem ");
            exit(3);
        }
    }

// in Case of an error exit from the loop
    if(n1 == -1){
        perror("Reading problem ");
        exit(2);
    }
    close(fd1);
    close(fd2);
    printf("HELLO WORLD:\t%s", buffer);
    exit(0);
}