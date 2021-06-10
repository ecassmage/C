#include <stdio.h>
#include "str.h"


void makeCopy(FILE *fd, FILE *fd2){
    str *newString = String("");
    while (1){
        char c = (char) getc(fd);
        if (c == EOF) break;
        concatSingleChar(newString, c);
    }
    printf("%s\n", string(newString));
    for (int i = len(newString)-1; 0 <= i; i--){
        if (charAt(newString, i) == EOF) break; // Just for Precautions
        fputc((int) charAt(newString, i), fd2);
    }
}

int main(int argc, char *argv[]) {
//    char temp[] = {"main.c"};
//    char temp2[] = {"mainCopy.txt"};
//    char temp3[] = {"mainCopy2.txt"};
    FILE *fd = fopen(argv[1], "r");
    FILE *fd2 = fopen(argv[2], "w");
    //FILE *fd = fopen(temp, "r");
    //FILE *fd2 = fopen(temp2, "w");
    makeCopy(fd, fd2);
    fclose(fd);
    fclose(fd2);
    fd = fopen(argv[2], "r");
    fd2 = fopen(argv[3], "w");
    makeCopy(fd, fd2);
    fclose(fd);
    fclose(fd2);
}
