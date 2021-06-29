//
// Created by evanm on 2021-06-11.
//

#include <stdio.h>

int main(int argc, char *argv[]){
    if (argc == 1) {
        printf("was not given file\n");
        return 0;
    }
    FILE *fd = fopen(argv[1], "r");
    if (fd == NULL){
        printf("Failure to acquire a file name!!!\n");
        return 0;
    }
    long ch = 0;
    int foundLines = 0;
    while ((ch = getc(fd)) > 0) if (ch == '\n') foundLines++;
    printf("The Total Line Count for %s is: %d\n", argv[1], foundLines+1);
    return foundLines+1;
}