//
// Created by evanm on 2021-06-26.
//
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

typedef struct overheadString{
    unsigned int lenArr;
} overheadString;

typedef struct str{
    char *stringContainer;
    unsigned int len;
    overheadString *lenFo;
} str;

void ERROR(char errorMessage[]){
    write(STDOUT_FILENO, "\033[0;31m", strlen("\033[0;31m"));  // NOTE: Won't work for everything but should if my experiences with java are correct will work on uWindsor servers. stupid other consoles which don't have colors set up on them or can't interpret ansi.
    write(STDOUT_FILENO, errorMessage, strlen(errorMessage));
    write(STDOUT_FILENO, "\033[0m", strlen("\033[0m"));  // Reverts Console back to Normal Colors.
    exit(0);
}
str *readToStrSys(int fd);
int writeStrSys(int fdSys, str *string);
int strWrite(str *container, int positionStart, const char word[]);
str* String(char newStr[]);
unsigned len(str *string);
void concatSingle(str *string, char arr[]);
void concatSingleChar(str *string, char chr);
void concatStr(str *string, str *stringConcat);
char *getStr(str *string);
char charAt(str *string, unsigned int index);
unsigned strLen(const char *string);
void deleteStr(str *string);
void printStr(const char message[], ...);

int main(int argc, char *argv[]){
    str *string = String("");
    int i = 1;
    for (; i < argc - 1; i++){
        int fd = open(argv[i], O_RDONLY);
        if (i > 1) concatSingleChar(string, '\n');
        str *stringConcat = readToStrSys(fd);
        concatStr(string, stringConcat);
        close(fd);
        deleteStr(stringConcat);
    }
    int fd = open(argv[i], O_CREAT|O_WRONLY|O_TRUNC, 0700);
    writeStrSys(fd, string);
    close(fd);
    printStr("%s\n", string);
}

int writeStrSys(int fdSys, str *string){
    lseek(fdSys, 0, SEEK_END);
    write(fdSys, getStr(string), len(string) - 1);
    return lseek(fdSys, 0, SEEK_END);
}

str *readToStrSys(int fd){
    lseek(fd, 0, SEEK_SET);
    char buffer[1];
    long ch;
    str *temp = String("");
    while ((ch = read(fd, buffer, 1)) > 0){
        if (ch == 0) break;
        concatSingleChar(temp, buffer[0]);
    }
    return temp;
}

unsigned len(str *string){return string -> len;}
int strWrite(str *container, int positionStart, const char word[]){
    int c = 0;
    while (word[c] != '\0') {
        container -> stringContainer[positionStart + c] = word[c];
        c++;
    }
    return c;
}
char charAt(str *string, unsigned int index){
    if (index > string -> len)
        ERROR("IndexOutOfRange");
    return string -> stringContainer[index];
}
char *getStr(str *string){return string -> stringContainer;}
unsigned strLen(const char *string){
    unsigned int i = 0;
    for (; string[i] != '\0'; i++);
    return i;
}
str *StringArr(char newStr[], overheadString *lengthSizes){
    str *string = (str*) malloc(sizeof(str));
    string -> stringContainer = (char*) malloc((strLen(newStr) + 1) * sizeof(char));
    string -> lenFo = lengthSizes;
    if (string == NULL) ERROR("Unable to allocate Memory");
    string -> len = strWrite(string, 0, newStr);
    string -> lenFo -> lenArr++;
    string -> stringContainer[len(string)] = '\0';
    return string;
}
void concatSingleChar(str *string, char chr){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + 2) * sizeof(char));
    string -> stringContainer[len(string)] = chr;
    string -> len++;
    string -> stringContainer[len(string)] = '\0';
}
void concatStr(str *string, str *stringConcat){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + len(stringConcat) + 1) * sizeof(char));
    unsigned i = 0;
    for (; charAt(stringConcat, i) != '\0'; i++){
        string -> stringContainer[len(string)+i] = charAt(stringConcat, i);
    }
    string -> stringContainer[len(string)+i] = '\0';
    string -> len += len(stringConcat);
}

void concatSingle(str *string, char arr[]){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + strLen(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        string -> stringContainer[len(string)+i] = arr[i];
    }
    string -> stringContainer[len(string)+i] = '\0';
    string -> len += strLen(arr);
}

str* String(char newStr[]){
    overheadString *temp = (overheadString*) malloc(sizeof(overheadString));
    temp -> lenArr = 0;
    return StringArr(newStr, temp);
}

void printStr(const char message[], ...){
    str *tempMessage = String("");
    va_list strList;
    va_start(strList, message);
    for (int i = 0; message[i] != '\0'; i++){
        if (message[i] == '%'){
            switch (message[i+1]){
                case 's': //I don't feel like limiting size at the moment, Might Later DUNNO.
                    concatSingle(tempMessage, getStr(va_arg(strList, str*)));
                    i++;
                    break;
//                case 'a': //I don't feel like limiting size at the moment, Might Later DUNNO.
//                    concatSingle(tempMessage, getStr(strArrToStr(va_arg(strList, str**))));
//                    i++; Takes more importing from header then worth it. Won't cause any issues though.
            }

        }
        else concatSingleChar(tempMessage, message[i]);
    }
    write(STDOUT_FILENO, getStr(tempMessage), len(tempMessage));
    va_end(strList);
}

void deleteStr(str *string){
    free(string -> stringContainer);
    free(string -> lenFo);
    free(string);
}
