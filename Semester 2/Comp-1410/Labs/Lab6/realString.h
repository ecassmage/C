//
// Created by evanm on 2021-03-10.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/*
 * This will create much bigger char arrays in which to make words. This will use up more memory, but in my opinion
 * the wasted memory is more then made up by an easier use of strings.
 */


typedef struct str{
    char *string;
    unsigned int len;
} str;

typedef struct strList{
    str *string;
    unsigned int len;
} strList;

void printS(str *string);
str *string();
str *stringWrite(char arr[]);
unsigned int stringLen(str *string);
unsigned int SLen(str *string);
unsigned int combinedSize(str *string, char arr[]);
void concatCalc(str *string, char arr[]);
void replace(str *string, char replace[], char replaceWith[]);
char chr(str *string, int number);
void newString(str *string, char replace[]);
void printString(str *string);
void concat(str *string, int num, ...);
char *string(str *String);

void printS(str *string){
    printf("%s\n", string -> string);
}

str *string(){
    str *temp = (str*) calloc(1, sizeof(str));
    temp -> string = (char*) calloc(10, sizeof(char));
    temp -> len = 0;
    return temp;
}

str *stringWrite(char arr[]){
    str *temp = (str*) calloc(1, sizeof(str));
    if (strlen(arr) == 0) {
        temp -> string = (char*) calloc(1, sizeof(char));
        return temp;
    }
    temp -> string = (char*) calloc(strlen(arr) + 1, sizeof(char));
    int i = 0;
    for (; arr[i] != '\0'; i++){
        temp -> string[i] = arr[i];
    }
    temp -> string[i] = '\0';
    temp -> len = strlen(arr);

    return temp;
}

unsigned int stringLen(str *string){
    unsigned int c = 0;
    while (string -> string[c] != '\0') c++;
    return c;
}

unsigned int SLen(str *string){
    return string -> len;
}

unsigned int combinedSize(str *string, char arr[]){
    return stringLen(string) + strlen(arr);
}

void concatCalc(str *string, char arr[]){
    string -> string = (char*) realloc(string -> string, (combinedSize(string, arr)+1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        string -> string[SLen(string)+i] = arr[i];
    }
    string -> string[SLen(string)+i] = '\0';
    string -> len += strlen(arr);
}

/// replaces a string of characters with another string. Will replace all occurrences.
void replace(str *string, char replace[], char replaceWith[]){
    for(int i = 0; string -> string[i] != '\0'; i++){
        if (string -> string[i] == replace[0]){
            if (strncmp(string -> string + i, replace, strlen(replace)) == 0){
                if (strlen(replaceWith) > strlen(replace)){
                    string -> string = (char*) realloc(string -> string, (stringLen(string) + strlen(replaceWith) - strlen(replace)) * sizeof(char));
                    for (unsigned int j = (stringLen(string) + strlen(replaceWith) - strlen(replace)); i + strlen(replace) < j; j--){
                        string -> string[j] = string -> string[j - strlen(replaceWith) + strlen(replace)];
                    }
                    for(int j = 0; replaceWith[j] != '\0'; j++){
                        string -> string[i + j] = replaceWith[j];
                    }
                    string -> string[stringLen(string)] = '\0';
                }
                else {
                    int j = 0;
                    for(; replaceWith[j] != '\0'; j++){
                        string -> string[i + j] = replaceWith[j];
                    }
                    for (j = i + j; string -> string[j + (strlen(replace) - strlen(replaceWith))] != '\0'; j++){
                        string -> string[j] = string -> string[j + (strlen(replace) - strlen(replaceWith))];
                    }
                    string -> string = (char*) realloc(string -> string, (stringLen(string) + strlen(replaceWith) - strlen(replace) ) * sizeof(char));
                    string -> string[j] = '\0';
                }
                i += (int) strlen(replaceWith) - 1;
            }
        }
    }
    string -> len = stringLen(string);
}

char chr(str *string, int number){
    return string -> string[number];
}
char *string(str *String){
    return String -> string;
}

void newString(str *string, char replace[]){
    string -> string = (char*) realloc(string -> string, (1 + strlen(replace)) * sizeof(char));
    int i = 0;
    for (; replace[i] != '\0'; i++){
        string -> string[i] = replace[i];
    }
    string -> string[i] = '\0';
    string -> len = stringLen(string);
}

void printString(str *string){
    printf("String -> [");
    for (int i = 0; string -> string[i] != '\0'; i++){
        if (string -> string[i+1] == '\0') printf("\"%c\"] Characters -> %d\n", string -> string[i], string -> len);
        else printf("\"%c\", ", string -> string[i]);
    }
}

void concat(str *string, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatCalc(string, va_arg(varList, char*));
    }
}
