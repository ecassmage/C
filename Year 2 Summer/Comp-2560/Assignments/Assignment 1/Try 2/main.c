#include <stdio.h>
#include <unistd.h>
#include "read.h"
#include "stringio.h"
#include "stringArray.h"

void infoToAppend(char file[]){
    long check;
    int fd = open(file, O_CREAT|O_WRONLY|O_TRUNC, 0700);
    printf("What do You Want?: ");
    fflush(stdout);
    char buffer[1];
    while ((check = read(STDIN_FILENO, buffer, 1)) > 0){
        if (buffer[0] == '\n') break;
        if (write(fd, buffer, 1) != check){
            exit(0);
        }
    }
    close(fd);
}


void arrayTesting(){
    str **array = strArr("This is First Message");
    append(&array, "This is the Second Message");
    append(&array, "This is the Third Message");
    printStr("This is Single Str: %s\nThis is Array: %a\n", array[0], array);

    //printStr("%s\n", pop(array, -1));
    printStr("This is Array: %a\n", array);

    append(&array, "Hello World1");
    append(&array, "Hello World2");
    append(&array, "Hello World3");
    printStr("This is Array: %a\n", array);
    printStr("This was Removed: %s\n", pop(&array, 3));
    printStr("This is Array: %a\n", array);
    append(&array, "Hello World4");
    append(&array, "Hello World5");
    append(&array, "Hello World6");
    append(&array, "Hello World7");
    printStr("This is Array: %a\n", array);
    printStr("This was Removed: %s\n", pop(&array, 5));
    pop(&array, 5);
    printStr("This is Array: %a\n", array);
}


int main(int argc, char *argv[]) {

    int fd = open("Checkers.txt", O_CREAT|O_WRONLY|O_TRUNC, 0700);
    str *newString = String("This is a Message of problems with compilers, They suck.");
    writeStrSys(fd, newString);
    close(fd);
    str **strArray = split(newString, ' ');
    for (int i = 0; i < 10; i++){
        printf("%s\n", getStr(strArray[i]));
    }
    printf("Hello World\n");
    //infoToAppend("HelloWorld.txt");
    FR * file = FileRead("HelloWorld.txt");
    while (!atEndOfFile(file)){
        printf("%s\n", getStr(readLine(file)));
    }
    closeFR(file);
    //printf("%s\n", getStr(scanStr("Please Enter Something Here: ")));
    str *secondNewString = String("This is What We Are!!!");
    printStr("This is a Message where you want something Here: %s, So Ya Here and Here: %s, Ta Da, here you GO!!!\n", newString, secondNewString);
    str *string = String("");
    scanStr("%s", string);
    printStr("This is Output: %s\n", string);

    arrayTesting();
}
