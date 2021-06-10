//
// Created by evanm on 2021-06-09.
//

#ifndef DFSDJFSHFDKJSHJFJKSHFJSD_FUCKCKCKCKC_H
#define DFSDJFSHFDKJSHJFJKSHFJSD_FUCKCKCKCKC_H

#endif //DFSDJFSHFDKJSHJFJKSHFJSD_FUCKCKCKCKC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct str{
    char *stringContainer;
    unsigned int len;
} str;

void ERROR(char errorMessage[]){
    printf("ERROR: %s\n", errorMessage);
    exit(0);
}


int strWrite(str *container, int positionStart, const char word[]);
str* String(char newStr[]);
char charAt(str *string, unsigned int index);
void replaceChar(str *string, unsigned int index, char chr);
unsigned len(str *string);
unsigned charLength(char *string);
unsigned int measureLength(str *string);
str *copyStr(str *string);
str **split(str *stringToSplit, char characterToSplitAt);
void concatSingle(str *string, char arr[]);
void concatSingleChar(str *string, char chr);
void concat(str *string, int num, ...);
int findInstance(str *string, char instance);
void replace(str *string, char replace[], char replaceWith[]);
int writestr(int fd, str *string);
int writeStr(FILE *fd, str *string);
int writestrat(int fd, int index, str *string);
int writeStrAt(FILE *fd, int index, str *string);
char *getStr(str *string);
void clearStr(str *string);
void deleteStr(str *string);


int strWrite(str *container, int positionStart, const char word[]){
    int c = 0;
    while (word[c] != '\0') {
        container -> stringContainer[positionStart + c] = word[c];
        c++;
    }
    return c++;
}

str* String(char newStr[]){
    str *string = (str*) malloc(sizeof(str));
    string -> stringContainer = (char*) malloc((strlen(newStr) + 1) * sizeof(char));
    if (string == NULL) ERROR("Unable to allocate Memory");
    //string -> stringContainer[(strlen(newStr))] = '\0';
    string -> len = strWrite(string, 0, newStr);
    string -> stringContainer[len(string)] = '\0';
    return string;
}

char charAt(str *string, unsigned int index){
    if (index > string -> len) ERROR("IndexOutOfRange");
    return string -> stringContainer[index];
}

void replaceChar(str *string, unsigned int index, char chr){
    string -> stringContainer[index] = chr;
}

unsigned len(str *string){
    return string -> len;
}
unsigned charLength(char *string){
    return strlen(string);
}

unsigned int measureLength(str *string){
    unsigned int c = 0;
    while (string -> stringContainer[c] != '\0') c++;
    return c;
}

str *copyStr(str *string){
    str *newString = (str*) malloc(sizeof(str));
    newString -> stringContainer = (char*) malloc((len(string) + 1) * sizeof(char));
    for (int i = 0; charAt(string, i) != '\0'; i++){
        replaceChar(newString, i, charAt(string, i));
    }
    return newString;
}

str **split(str *stringToSplit, char characterToSplitAt){
    str **stringArr = (str**) malloc(findInstance(stringToSplit, characterToSplitAt) * sizeof(str*));
    str *strTemp = (str*) malloc(sizeof(char));
    strTemp = String("");
    int strFoundToSplit = 0;
    for (int i = 0; charAt(stringToSplit, i) != '\0'; i++){
        if (charAt(stringToSplit, i) != characterToSplitAt){
            concatSingleChar(strTemp, charAt(stringToSplit, i));
        }
        else{
            stringArr[strFoundToSplit] = copyStr(strTemp);
            clearStr(strTemp);
            strTemp = String("");
            strFoundToSplit++;
        }
    }
    deleteStr(strTemp);
}

void concatSingle(str *string, char arr[]){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + charLength(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        string -> stringContainer[len(string)+i] = arr[i];
    }
    string -> stringContainer[len(string)+i] = '\0';
    string -> len += strlen(arr);
}

void concatSingleChar(str *string, char chr){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + 2) * sizeof(char));
    string -> stringContainer[len(string)] = chr;
    string -> stringContainer[len(string)+1] = '\0';
    string -> len ++;
}

void concat(str *string, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatSingle(string, va_arg(varList, char*));
    }
}

int findInstance(str *string, char instance){
    int countNumber = 0;
    for (int i = 0; charAt(string, i) != '\0'; i++){
        if (charAt(string, i) == instance) countNumber++;
    }
    return countNumber;
}

void replace(str *string, char replace[], char replaceWith[]){
    for(int i = 0; string -> stringContainer[i] != '\0'; i++){
        if (string -> stringContainer[i] == replace[0]){
            if (strncmp(string -> stringContainer + i, replace, strlen(replace)) == 0){
                if (strlen(replaceWith) > strlen(replace)){
                    string -> stringContainer = (char*) realloc(string -> stringContainer, (measureLength(string) + strlen(replaceWith) - strlen(replace)) * sizeof(char));
                    for (unsigned int j = (measureLength(string) + strlen(replaceWith) - strlen(replace)); i + strlen(replace) < j; j--){
                        string -> stringContainer[j] = string -> stringContainer[j - strlen(replaceWith) + strlen(replace)];
                    }
                    for(int j = 0; replaceWith[j] != '\0'; j++){
                        string -> stringContainer[i + j] = replaceWith[j];
                    }
                    string -> stringContainer[measureLength(string)] = '\0';
                }
                else {
                    int j = 0;
                    for(; replaceWith[j] != '\0'; j++){
                        string -> stringContainer[i + j] = replaceWith[j];
                    }
                    for (j = i + j; string -> stringContainer[j + (strlen(replace) - strlen(replaceWith))] != '\0'; j++){
                        string -> stringContainer[j] = string -> stringContainer[j + (strlen(replace) - strlen(replaceWith))];
                    }
                    string -> stringContainer = (char*) realloc(string -> stringContainer, (measureLength(string) + strlen(replaceWith) - strlen(replace) ) * sizeof(char));
                    string -> stringContainer[j] = '\0';
                }
                i += (int) strlen(replaceWith) - 1;
            }
        }
    }
    string -> len = measureLength(string);
}
/**
 * Writes a str structures data to file based on location given. Uses System I/O
 * <p>
 *      Writes string at the end of File.
 * </p>
 * @param fd takes an integer for location of file
 * @param string Takes str struct with information of what is wanted to be added.
 * @return returns integer for index program finished off at
 */
int writestr(int fd, str *string){
    lseek(fd, 0, SEEK_END);
    write(fd, getStr(string), len(string));
    return lseek(fd, 0, SEEK_END);
}
int writeStr(FILE *fd, str *string){ //All upper case other then first word means standard i/o
    fseek(fd, 0, SEEK_END);
    fwrite(getStr(string), 1, len(string), fd);
    return fseek(fd, 0, SEEK_END); // I could probably just do SEEK_SET here but whats the fun of that
}

/**
 * Writes a str structures data to file based on location given. Uses System I/O
 * <p>
 *      If you want to write multiple strings after one another this will return the current end of where you wrote the program.
 *      If however you were overriding a section it will leave off where this function finished modifying so SEEK_END will probably be needed
 *      to find the end of the file.
 * </p>
 * @param fd takes an integer for location of file
 * @param index takes integer for where user wants to append to
 * @param string Takes str struct with information of what is wanted to be added.
 * @return returns integer for index program finished off at
 */
int writestrat(int fd, int index, str *string){  //All lower case means system i/o
    lseek(fd, index, SEEK_SET);
    write(fd, getStr(string), len(string));
    int store = lseek(fd, 0, SEEK_CUR);
    int val = lseek(fd, 0, SEEK_END);
    lseek(fd, store, SEEK_SET);
    return val;
}

/**
 * Writes a str structures data to file based on location given. Uses Standard I/O
 * <p>
 *      If you want to write multiple strings after one another this will return the current end of where you wrote the program.
 *      If however you were overriding a section it will leave off where this function finished modifying so SEEK_END will probably be needed
 *      to find the end of the file.
 * </p>
 * @param fd takes a FILE reference for location of file
 * @param index takes integer for where user wants to append to
 * @param string Takes str struct with information of what is wanted to be added.
 * @return returns integer for index program finished off at
 */
int writeStrAt(FILE *fd, int index, str *string){ //All upper case other then first word means standard i/o
    fseek(fd, index, SEEK_SET);
    fwrite(getStr(string), 1, len(string), fd);
    int store = fseek(fd, 0, SEEK_CUR);
    int val = fseek(fd, 0, SEEK_END);
    fseek(fd, store, SEEK_SET);
    return val;
}

char *getStr(str *string){
    return string -> stringContainer;
}

void clearStr(str *string){
    free(string -> stringContainer);
}

void deleteStr(str *string){
    clearStr(string);
    free(string);
}