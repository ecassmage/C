//
// Created by evanm on 2021-06-10.
//

#include <stdio.h>
#include "stringio.h"
#include <fcntl.h>


int Q8(void){
    char buf1[] = "abcdefghij";
    char buf2[] = "ABCDEFGHIJ";
    FILE *fd = fopen("file.hole", "w");
    fwrite(buf1, 10, 1, fd);
    fseek(fd, 16384, SEEK_SET);
    fwrite(buf2, 10, 1, fd);
    fclose(fd);
    return 0;
}


int main(int argc, char *argv[]){
/*
    if (argc == 1) printf("No File Names Given\n");

    // Question 6
    int fdSys = open(argv[1], O_RDWR);
    str *string = readToStrSys(fdSys);
    printStr("This is String: %s\n", string);
    printf("What Information do you want to append?: ");
    str *appendStr = String("");
    scanStr("%s", appendStr);
    writeStrSys(fdSys, appendStr);
    deleteStr(string);
    string = readToStrSys(fdSys);
    printStr("This is The New String: %s\n", string);
    close(fdSys);
    // Question 6

    deleteStr(string);
    deleteStr(appendStr);

    //Question 7
    FILE *fdStd = fopen(argv[1], "r+");
    string = readToStrStd(fdStd);
    printStr("\n\nThis is String: %s\n", string);
    printf("What Information do you want to append?: ");
    appendStr = String("");
    scanStr("%s", appendStr);
    writeStrStd(fdStd, appendStr);
    deleteStr(string);
    string = readToStrStd(fdStd);
    printStr("This is The New String: %s\n", string);
    fclose(fdStd);
    // Question 7
*/
    Q8();
}
