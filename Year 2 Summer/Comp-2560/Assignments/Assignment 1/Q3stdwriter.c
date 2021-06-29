//
// Created by evanm on 2021-06-11.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    char lines[] = {"101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005\n"};

    FILE *fd;
    if (argc == 1) {
        printf("Failure to acquire a file name!!! So we are using a pre-defined name list2.txt\n");
        fd = fopen("list2.txt", "w");
    }
    else{
        fd = fopen(argv[1], "w");
    }
    if (fd == NULL) {
        printf("Ya Couldn't find your File, Sorry!!! :> \n");
        exit(0);
    }
    fwrite(&lines, 1, strlen(lines), fd);
    fclose(fd);
    return 0;
}