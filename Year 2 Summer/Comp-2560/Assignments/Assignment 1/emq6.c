//
// Created by evanm on 2021-06-11.
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct overheadString{
    unsigned int lenArr;
} overheadString;


/**
 * Structure for str holds information like the char array and length of string. as well as some array information.
 */
typedef struct str{
    char *stringContainer;
    unsigned int len;
    overheadString *lenFo;
} str;

void ERROR(char errorMessage[]){
    printf("ERROR: %s\n", errorMessage);
    exit(0);
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
char *getStr(str *string){return string -> stringContainer;}
str *StringArr(char newStr[], overheadString *lengthSizes){
    str *string = (str*) malloc(sizeof(str));
    string -> stringContainer = (char*) malloc((strlen(newStr) + 1) * sizeof(char));
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

void concatSingle(str *string, char arr[]){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + strlen(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        string -> stringContainer[len(string)+i] = arr[i];
    }
    string -> stringContainer[len(string)+i] = '\0';
    string -> len += strlen(arr);
}

str* String(char newStr[]){
    overheadString *temp = (overheadString*) malloc(sizeof(overheadString));
    temp -> lenArr = 0;
    return StringArr(newStr, temp);
}

str *readToStrSys(int fd){
    lseek(fd, 0, SEEK_SET);
    char buffer[1];
    long ch;
    str *temp = String("");
    while ((ch = read(fd, buffer, 1)) > 0){
        if (ch == 0) break; // Useless probably because of while loop but meh
        concatSingleChar(temp, buffer[0]);
    }
    return temp;
}
int charToInt(char chr){
    if(48 <= chr && chr <= 57) return chr - 48;
    return -1;
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
    printf("%s", getStr(tempMessage));
    va_end(strList);
}

void replaceStr(str *string, char newString[]){
    free(string -> stringContainer);
    string -> stringContainer = (char*) malloc((strlen(newString) + 1) * sizeof(char));
    for (int i = 0; newString[i] != '\0'; i++){
        string -> stringContainer[i] = newString[i];
    }
    string -> stringContainer[strlen(newString)] = '\0';
    string -> len = strlen(newString) + 1;
}

char *pickupChars(int num){
    char buffer[1];
    int newIndex = 0;
    str *tempStr = String("");
    if (num == 0){
        while (read(STDIN_FILENO, buffer, 1) > 0){
            if (buffer[0] == '\n') break;
            concatSingleChar(tempStr, buffer[0]);
        }
    }
    else{
        while (read(STDIN_FILENO, buffer, 1) > 0 && newIndex < num){
            if (buffer[0] == '\n') break;
            concatSingleChar(tempStr, buffer[0]);
            newIndex++;
        }
    }
    return getStr(tempStr);
}

void scanStr(char message[], ...){
    fflush(stdout);
    va_list strList;
    va_start(strList, message);
//    read(STDIN_FILENO, NULL, 0);
    for (int i = 0; message[i] != '\0'; i++){
        if (message[i] == '%' && message[i-1] != '\\'){
            int num = 0, j = i+1;
            for (; charToInt(message[j]) != -1; j++) num = (num * 10) + charToInt(message[j]);
            if (message[j] == 's'){
                replaceStr(va_arg(strList, str*), pickupChars(num));
            }
        }
    }
    va_end(strList);
}

void deleteStr(str *string){
    free(string -> stringContainer);
    free(string -> lenFo);
    free(string);
}

int writeStrSys(int fdSys, str *string){
    lseek(fdSys, 0, SEEK_END);
    write(fdSys, getStr(string), len(string) - 1);
    return lseek(fdSys, 0, SEEK_END);
}

int main(int argc, char *argv[]) {

    if (argc == 1) printf("No File Names Given\n");

    // Question 6
    int fdSys = open(argv[1], O_RDWR, 0700);
    if (fdSys == -1) {
        printf("Failure to locate file.");
        return 0;
    };
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
}