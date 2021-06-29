//
// Created by evanm on 2021-06-09.
//


/**
 * An Extension to "string.h" to allow for more interactions related io
 * <p>
 *  Deals with Input Output Interactions with strings like file I/O, or even just Console I/O
 * </p>
 *
 * @author Evan Morrison
 * @version 1.3.3
 * @since 1.1.0
 */

#ifndef MAIN_C_STRINGIO_H
#define MAIN_C_STRINGIO_H

#include "string.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

int writeStrSys(int fd, str *string);
int writeStrStd(FILE *fd, str *string);
int writeStrAtSys(int fd, int index, str *string);
int writeStrAtStd(FILE *fd, int index, str *string);

/**
 * Writes a str structures data to file based on location given. Uses System I/O
 * <p>
 *      Writes string at the end of File.
 * </p>
 * @param fd takes an integer for location of file
 * @param string Takes str struct with information of what is wanted to be added.
 * @return returns integer for index program finished off at
 */

int writeStrSys(int fdSys, str *string){
    lseek(fdSys, 0, SEEK_END);
    write(fdSys, getStr(string), len(string) - 1);
    return lseek(fdSys, 0, SEEK_END);
}

int writeStrStd(FILE *fdStand, str *string){
    fseek(fdStand, 0, SEEK_END);
    fwrite(getStr(string), 1, len(string), fdStand);
    return fseek(fdStand, 0, SEEK_END);
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

int writeStrAtSys(int fd, int index, str *string){
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

int writeStrAtStd(FILE *fdStand2, int index, str *string){
    fseek(fdStand2, index, SEEK_SET);
    fwrite(getStr(string), 1, len(string), fdStand2);
    int store = fseek(fdStand2, 0, SEEK_CUR);
    int val = fseek(fdStand2, 0, SEEK_END);
    fseek(fdStand2, store, SEEK_SET);
    return val;
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
/*
str *scanStr(char message[]){
    printf("%s", message);
    fflush(stdout);
    fflush(stdin);
    char buffer[1];
    str *tempStr = String("");
    while (read(STDIN_FILENO, buffer, 1) > 0) if (buffer[0] != '\n') concatSingleChar(tempStr, buffer[0]); else break;
    return tempStr;
}
*/
str *strArrToStr(str **array){
    str *tempString = String("[");
    for (int i = 0; i < lenArray(array); i++) {
        if (i > 0) concatSingle(tempString, ", ");
        concat(tempString, 3, "\"", getStr(array[i]), "\"");
    }
    concatSingle(tempString, "]");
    return tempString;
}

void printStr(const char message[], ...){
    str *tempMessage = String("");
    va_list strList;
    va_start(strList, message);
    for (int i = 0; message[i] != '\0'; i++){
        if (message[i] == '%'){
            switch (message[i+1]){
                case 's':
                    concatSingle(tempMessage, getStr(va_arg(strList, str*)));
                    i++;
                    break;
                case 'a':
                    concatSingle(tempMessage, getStr(strArrToStr(va_arg(strList, str**))));
                    i++;
            }

        }
        else concatSingleChar(tempMessage, message[i]);
    }
    printf("%s", getStr(tempMessage));
    va_end(strList);
}

int charToInt(char chr){
    if(48 <= chr && chr <= 57) return chr - 48;
    return -1;
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

#endif //STRINGIO_H