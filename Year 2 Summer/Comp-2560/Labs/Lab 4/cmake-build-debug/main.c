#include <stdio.h>
#include "str.h"


void smartMe(str *string, char newChar){
    concatSingleChar(string, newChar);
}

int main(int argc, char *argv[]) {
    str *newString = String("");
    char temp[] = {"main.c"};
    //FILE *fd = fopen(argv[1], "r");
    FILE *fd = fopen(temp, "r");
    FILE *fd2 = fopen(argv[2], "w");
    while (1){
        char c = (char) getc(fd);
        smartMe(newString, c);
        if (c == EOF) break;
    }
    fclose(fd);
    fclose(fd2);
    printf("Totally Overkill: %s\n", string(newString));
}



