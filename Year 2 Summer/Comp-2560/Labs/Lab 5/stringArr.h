//
// Created by evanm on 2021-06-14.
//

#ifndef LAB_5_STRINGARR_H
#define LAB_5_STRINGARR_H
#include "string.h"

typedef struct stringArray{
    str *strings;
    int len;
}strArray;

strArray *Array(char *string){
    strArray *temp = (strArray*) malloc(sizeof(strArray));
    temp -> strings = String(string);
    temp -> len = 1;
    if (string[0] == '\0'){
        temp -> len = 0;
    }
    return temp;
}

void append(strArray *arr, char *string){
    arr -> len++;
    arr -> strings = (str*) realloc(arr -> strings, (arr -> len) * sizeof(str));
    arr -> strings[arr -> len - 1] = *String(string);
}

str *pop(strArray *arr, int i){
    if (i < 0) i += (int) arr -> len;
    if (i >= arr -> len || i < 0) return NULL; // i < 0 catches anything that wrapped too far around.

    for (i+=1; i < arr -> len; i++)
        arr -> strings[i-1] = arr -> strings[i];
    arr -> strings = (str*) realloc(arr -> strings, arr -> len * sizeof(str));
}
#endif //LAB_5_STRINGARR_H
