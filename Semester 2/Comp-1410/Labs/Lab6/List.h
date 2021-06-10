//
// Created by evanm on 2021-03-10.
//
#include <stdlib.h>
#include <stdio.h>
//typedef struct list list;
//typedef struct length length;

typedef struct length {
    int lenC;
    int lenT;
} length;

typedef struct list{
    int value;
    length *len;
} listS;


typedef struct trueList{
    int *value;
    int lenC;
    int lenT;
} list;

int len(list *arr) {return (arr -> lenC);}
int TLen(list *arr) {return (arr -> lenT);}
int sizeDif(list *arr) {return (arr -> lenT) - (arr -> lenC);}


list *List(int num){
    list *returnList = (list*) malloc(sizeof(list));
    returnList -> value = (int*) calloc(num, sizeof(int));
    returnList -> lenC = 0;
    returnList -> lenT = num;
    return returnList;
}

void checkSize(list *arr){
    if (sizeDif(arr) == 0) {
        arr->value = (int*) realloc(arr->value, ((arr->lenT) * 10) * sizeof(int));
        arr->lenT *= 10;
    }
    else if (len(arr) >= 1 && TLen(arr) / len(arr) >= 15){
        arr->value = (int*) realloc(arr->value, ((arr->lenT) / 10) * sizeof(int));
        arr->lenT /= 10;
    }
}

void append(list *listArray, int num){
    checkSize(listArray);
    listArray -> value[len(listArray)] = num;
    listArray -> lenC++;
}

list *pop(list *listArray, int pos){
    for (int i = pos; i < len(listArray) - 1; i++){
        listArray -> value[i] = listArray -> value[i + 1];
    }
    listArray -> lenC--;
    checkSize(listArray);
    return listArray;
}

void print(list *arr){
    printf("[");
    for (int i = 0; i < (arr -> lenC) - 1; i++){
        printf("%d, ", arr -> value[i]);
    }
    printf("%d]\n", arr -> value[(arr -> lenC) - 1]);
}

void del(list *arr){
    free(arr);
}

int value(list *arr, int pos){
    return arr -> value[pos];
}

int listIndex(list *arr, int val){
    for (int i = 0; i < len(arr); i++){
        if (val == arr -> value[i]){
            if (arr -> value[i] == 25) printf("Yes\n");
            return i;
        }
    }
    printf("Key Error: %d is not an element of list\n", val);
    exit(0);
}

//trueList *makeTrueList(int num){
//    //trueList tempTrueList = {, num, num};
//    trueList *returnList = (trueList*) malloc(sizeof(trueList));
//    returnList -> value = (int*) calloc(num, sizeof(int));
//    returnList -> lenC = num;
//    returnList -> lenT = num;
//    return returnList;
//}