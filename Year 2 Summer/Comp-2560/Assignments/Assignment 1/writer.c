//
// Created by evanm on 2021-06-11.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Wish I was sure if I could use my "string.h" headers. This assignment would be so much easier and cleaner.

int main(int argc, char *argv[]) {
    char lines[] = {"101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005\n"};
    int fd;
    if (argc == 1) {
        printf("Failure to acquire a file name!!! So we are using a pre-defined name list1.txt\n");
        fd = open("list1.txt", O_CREAT|O_WRONLY|O_TRUNC, 0700);
    }
    else{
        fd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, 0700);
    }
    if (fd == -1){
        printf("Ya Couldn't seem to either find the file or make the file either, Sorry!!! :> \n");
        exit(0);
    }
    write(fd, &lines, strlen(lines));
    close(fd);

    return 0;
}