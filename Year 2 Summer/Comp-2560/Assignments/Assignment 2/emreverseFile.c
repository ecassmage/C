//
// Created by evanm on 2021-06-26.
//
//#include "stringio.h"
//#include "stringArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Sorry For all the Unnecessary Stuff.

typedef struct overheadString{
    unsigned int lenArr;
} overheadString;

typedef struct str{
    char *stringContainer;
    unsigned int len;
    overheadString *lenFo;
} str;

void ERROR(char errorMessage[]){
    printf("ERROR: %s\n", errorMessage);
    exit(0);
}

str *StringArr(char newStr[], overheadString *lengthSizes);
str **strArr(char message[]);
str *StringArray(str **array, char string[]);
void appendStr(str ***array, str *string);
void append(str ***array, char *string);
unsigned lenArray(str **string);
str *readToStrStd(FILE *fd);
int writeStrStd(FILE *fdStand, str *string);
int strWrite(str *container, int positionStart, const char word[]);
str* String(char newStr[]);
unsigned len(str *string);
void concatSingle(str *string, char arr[]);
void concatSingleChar(str *string, char chr);
void concatStr(str *string, str *stringConcat);
char *getStr(str *string);
void downLenArr(str **arr);
char charAt(str *string, unsigned int index);
unsigned strLen(const char *string);
void deleteStr(str *string);
void printStr(const char message[], ...);
str *readLine(FILE *fd, int *EOL);


int main(int argc, char *argv[]){
    if (argc < 3) return 0;
    FILE *read = fopen(argv[1], "r");
    FILE *write = fopen(argv[2], "w");
    str **arr = strArr("");
    //for (int E = 1; E; appendStr(&arr, readLine(read, &E))); // Dunno What I have done By I Like It. I Really Like this. Looks kind of like for EOL in open("emreverseFiletext.txt", "r").readline(): arr.append(EOL) I know nothing alike but it sort of has that structure to it.
    for (int E = 1; E; ){
        str *string = readLine(read, &E);
        appendStr(&arr,string);
        deleteStr(string);  // Sadly I need to deallocate this useless sections :(
    }
    for (int i = (int) lenArray(arr)-1; i >= 0; i--){
        if (i != 0) concatSingleChar(arr[i], '\n');
        writeStrStd(write, arr[i]);
    }
    fclose(read);
    fclose(write);
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

str **strArr(char message[]){
    str **tempArr = (str**) malloc(sizeof(str*));
    tempArr[0] = String(message);
    return tempArr;
}
str *StringArray(str **array, char string[]){
    return StringArr(string, array[0] -> lenFo);
}
void appendStr(str ***array, str *string){
    append(array, getStr(string));
}
void append(str ***array, char *string) {
    if (lenArray(*array) == 1 && ((*array)[lenArray(*array) - 1] == NULL || charAt((*array)[lenArray(*array) - 1], 0) == '\0')) {
        (*array)[lenArray(*array) - 1] = StringArray(*array, string);
        downLenArr(*array);
    }

    else{
        *array = (str**) realloc(*array, (lenArray(*array) + 1) * sizeof(str*));
        (*array)[lenArray(*array)] = StringArray(*array, string);
    }
}

unsigned lenArray(str **string){
    return string[0] -> lenFo -> lenArr;
}

str *readToStrStd(FILE *fd){
    fseek(fd, 0, SEEK_SET);
    char buffer[1];
    str *temp = String("");
    while (fread(buffer, 1, 1, fd) > 0){
        if (buffer[0] == EOF) break;
        concatSingleChar(temp, buffer[0]);
    }
    return temp;
}

int writeStrStd(FILE *fdStand, str *string){
    fseek(fdStand, 0, SEEK_END);
    fwrite(getStr(string), 1, len(string), fdStand);
    return fseek(fdStand, 0, SEEK_END);
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

void downLenArr(str **arr) {
    arr[0] -> lenFo -> lenArr--;
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
    printf("%s", getStr(tempMessage));
    va_end(strList);
}

void deleteStr(str *string){
    free(string -> stringContainer);
    free(string -> lenFo);
    free(string);
}

str *readLine(FILE *fd, int *EOL){
    char buffer[1];
    str *temp = String("");
    if (*EOL == 2) {
        *EOL = 0;
        return temp;
    }
    *EOL = 1;
    int num = 0;
    while (fread(buffer, 1, 1, fd) > 0){
        if (buffer[0] == EOF){
            break;
        }
        else if (buffer[0] == '\n' || buffer[0] == '\r') {  // My Computer started writing carriage returns for some reason. So I added \r. Computers are evil sometimes, But That just got to be the way sometimes.
            char tempChars[3] = {'\0', buffer[0], '\0'};

            if (fread(&tempChars[2], 1, 1, fd) == 0 && num == 0) {
                fseek(fd, -2, SEEK_CUR);
                fread(&tempChars[0], 1, 1, fd);
                if (tempChars[0] == '\n'){
                    *EOL = 2;
                }
                else{
                    *EOL = 0;
                }
                return temp;
            }

            if (tempChars[2] == '\n' || tempChars[2] == '\r'){
                if (tempChars[1] == tempChars[2]){
                    fseek(fd, -1, SEEK_CUR);  // Catches a \n or \r followed by the same character
                }
                //else concatSingleChar(temp, '\n');
            }
            else fseek(fd, -1, SEEK_CUR);  // Catches a \n or \r followed by irrelevant character
            // I need to check both these positions in case one doesn't appear. Since I was getting both to appear I needed to jump ahead or a new line would be added when I didn't need it.
            // This allowed for me to avoid both possible positions of only 1 appearing or both appearing. It also catches the same from appearing ie \n\n which would mean an empty line underneath.

            return temp; // My Computer started writing carriage returns for some reason. So I added \r
        }
        concatSingleChar(temp, buffer[0]);
        num++;
    }
    *EOL = 0;
    return temp;
}