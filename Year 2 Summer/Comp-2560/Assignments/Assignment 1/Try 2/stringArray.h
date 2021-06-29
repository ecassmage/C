//
// Created by evanm on 2021-06-09.
//

/**
 * An Extension to "string.h" to allow for more interactions with string arrays.
 *
 * <p>
 *  Allows mainly for Appending, Popping and some other stuff array specific.
 *  Popping not implemented yet since I realized I actually needed to do my Assignment and haven't gotten around to it yet.
 * </p>
 *
 * @author Evan Morrison
 * @version 1.3.3
 * @since 1.2.0
 */

#ifndef MAIN_C_STRINGARRAY_H
#define MAIN_C_STRINGARRAY_H

#include "string.h"


str **strArr(char message[]){
    str **tempArr = (str**) malloc(sizeof(str*));
    tempArr[0] = String(message);
    return tempArr;
}

str *StringArray(str **array, char string[]){
    return StringArr(string, getArrInfo(array));
}

void appendStr(str ***array, str *string){
    str **temp = (str**) realloc(array, (lenArray(*array) + 1) * sizeof(str*));
    temp[lenArray(temp)] = string;
    setLenArr(temp, lenArray(temp)+1);
    *array = temp;
}

void append(str ***array, char *string){
    *array = (str**) realloc(*array, (lenArray(*array) + 1) * sizeof(str*));
    (*array)[lenArray(*array)] = StringArray(*array, string);
}

void appendMultiStr(str ***array, int num, ...){
    va_list list;
    va_start(list, num);
    for (int i = 0; i < num; i++){
        appendStr(array, va_arg(list, str*));
    }
}

void appendMulti(str ***array, int num, ...){
    va_list list;
    va_start(list, num);
    for (int i = 0; i < num; i++){
        append(array, va_arg(list, char*));
    }
}

void pop(str ***array, int i){
    if (i < 0) i += (int) lenArray(*array);
    if (i >= lenArray(*array) || i < 0) return; // i < 0 catches anything that wrapped too far around.

    for (i+=1; i < lenArray(*array); i++)
        (*array)[i-1] = (*array)[i];

    setLenArr(*array, lenArray(*array)-1);
    *array = (str**) realloc(*array, lenArray(*array) * sizeof(str*));
}
str *popStr(str ***array, int i){
    if (i < 0) i += (int) lenArray(*array);
    if (i >= lenArray(*array) || i < 0) return NULL; // i < 0 catches anything that wrapped too far around.
    str *temp = (*array)[i];

    for (i+=1; i < lenArray(*array); i++)
        (*array)[i-1] = (*array)[i];

    setLenArr(*array, lenArray(*array)-1);
    str **tempA = (str**) realloc(*array, lenArray(*array) * sizeof(str*));
    *array = tempA;
    return temp;
}

void popItem(str ***array, str *string){
    for (int i = 0; i < lenArray(*array); i++) if (*array[i] == string) pop(array, i);
}
str *popItemStr(str ***array, str *string){
    for (int i = 0; i < lenArray(*array); i++) if (*array[i] == string) return popStr(array, i);
    return NULL;
}






#endif //MAIN_C_STRINGARRAY_H
