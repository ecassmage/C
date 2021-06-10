//
// Created by evanm on 2021-03-10.
//
#include "realString.h"

//typedef struct str{
//    char *string;
//    unsigned int len;
//} str;

typedef struct listLength{
    int lenC;
    int lenT;
} listLength;

typedef struct list{
    int type;
    int number;
    str *string;
    listLength *len;
} list;

int CLen(list *arr) {return (arr -> len -> lenC);}
int TLen(list *arr) {return (arr -> len -> lenT);}
int sizeDif(list *arr) {return (arr -> len -> lenT) - (arr -> len -> lenC);}


void checkSize(list *arr){
    if (sizeDif(arr) <= 0) {
        listLength *FuckYou = (listLength*) realloc(arr[0].len, (arr[0].len -> lenT) * sizeof(listLength));
        arr = (list*) realloc(arr, ((arr[0].len -> lenT) * 10) * sizeof(list));
        (FuckYou -> lenT) *= 10;
        for (int i = 0; i < FuckYou -> lenT; i++){
            arr[i].len = FuckYou;
        }
    }
    else if (CLen(arr) >= 1 && TLen(arr) / CLen(arr) >= 15){
        arr = (list*) realloc(arr, ((arr[0].len -> lenT) / 10) * sizeof(list));
        arr[0].len = (listLength*) realloc(arr[0].len, (arr[0].len -> lenT) * sizeof(listLength));
        (arr[0].len -> lenT) /= 10;
    }
}

#define FuckYou 10
list *List(){
    list *temp = (list*) calloc(FuckYou, sizeof(list));
    listLength *tempLength = (listLength*) calloc(1, sizeof(listLength));
    tempLength -> lenT = FuckYou;
    for (int i = 0; i < FuckYou; i++){
        temp[i].len = tempLength;
    }
    return temp;
}

void appendI(list *list, int val){
    checkSize(list);
    list[list -> len -> lenC].number = val;
    list[list -> len -> lenC].type = 1;
    list -> len -> lenC++;
}

void appendC(list *list, char arr[]){
    checkSize(list);
    list[list -> len -> lenC].string = (str*) realloc(list[list -> len -> lenC].string, sizeof(str));
    list[list -> len -> lenC].string = stringWrite(arr);
    printf("%s\n", list[list -> len -> lenC].string -> string);
    list[list -> len -> lenC].type = 2;
    list -> len -> lenC++;
}

void appendS(list *list, str *string){
    checkSize(list);
    //printf("%s\n", string -> string);
    list[list -> len -> lenC].string = (str*) realloc(list[list -> len -> lenC].string, sizeof(str));
    list[list -> len -> lenC].string = string;
    list[list -> len -> lenC].type = 2;
    list -> len -> lenC++;
}

void print(list *list){
    printf("[");
    for (int i = 0; i < list[0].len -> lenC; i++){
        if (list[i].type == 1){
            printf("%d", list[i].number);
        }
        else if (list[i].type == 2){
            printf("%s", list[i].string -> string);
        }
        if ((i+1 < list[0].len -> lenC))
            printf(", ");
    }
    printf("]\n");
}
