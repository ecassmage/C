//
// Created by evanm on 2021-06-11.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    if (argc == 1) {
        printf("was not given file\n");
        return 0;
    }
    int fd = open(argv[1], 'r');
    if (fd == -1){
        printf("Failure to acquire a file name!!!\n");
        return 0;
    }
    char buffer;
    long ch;
    int foundLines = 0;
    while ((ch = read(fd, &buffer, 1)) > 0) if (buffer == '\n') foundLines++;
    printf("The Total Line Count for %s is: %d\n", argv[1], foundLines);
    return foundLines+1;
}
//wc -l is an inaccurate by 1 for some reason, it is giving an answer of 25 when this counted up is 26. I had to modify my program which is why the printf and the return don't match up.