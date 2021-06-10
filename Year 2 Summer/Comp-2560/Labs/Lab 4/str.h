//
// Created by evanm on 2021-06-07.
// This is all my Own Work. Any Copying of this will be met with copyright infringement or something like that.
//

#ifndef LAB_4_STR_H
#define LAB_4_STR_H

#endif //LAB_4_STR_H
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>




typedef struct string{
    char *stringContainer;
    unsigned int len;
} str;

unsigned len(str *string);

void ERROR(char errorMessage[]){
    printf("ERROR: %s\n", errorMessage);
    exit(0);
}

int strWrite(str *container, int positionStart, const char word[]){
    int c = 0;
    while (word[c] != '\0') {
        container -> stringContainer[positionStart + c] = word[c];
        c++;
    }
    return c++;
}

str* String(char newStr[]){
    str *string = (str*) malloc((strlen(newStr) + 1) * sizeof(str));
    string -> stringContainer = (char*) malloc((strlen(newStr) + 1) * sizeof(char));
    if (string == NULL) ERROR("Unable to allocate Memory");
    //string -> stringContainer[(strlen(newStr))] = '\0';
    string -> len = strWrite(string, 0, newStr);
    string -> stringContainer[len(string)] = '\0';
    return string;
}

char charAt(str *string, unsigned int index){
    if (index >= string -> len) ERROR("IndexOutOfRange");
    return string -> stringContainer[index];
}

unsigned int combinedSize(str *string, char arr[]){
    return strlen(string -> stringContainer) + strlen(arr);
}


unsigned len(str *string){
    return string -> len;
}
unsigned length(char *string){
    return strlen(string);
}

unsigned int measureLength(str *string){
    unsigned int c = 0;
    while (string -> stringContainer[c] != '\0') c++;
    return c;
}

void concatSingle(str *string, char arr[]){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + length(arr) + 1) * sizeof(char));
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

char *string(str *string){
    return string -> stringContainer;
}