//
// Created by Evan Morrison on 2021-03-08.
//
#include <stdlib.h>


typedef struct linkedInfo linkedInformation;
struct linkedInfo {
    int length; /// Current length of array.
    int sizeTotal;  /// Current Length allocated to the array.
};

typedef struct linkedList linkedList;
struct linkedList {
    int value;  /// Value held by the array
    linkedInformation *info;  /// Information pertaining to the array
    linkedList *next;  /// Next element in the array
    linkedList *prev;  /// previous element in the array.
};


void printLinkedList(struct linkedList array[]);


void changeLen(struct linkedInfo *informationBlock, int num){
    (*informationBlock).length = num;
    if (num > (*informationBlock).sizeTotal){
        (*informationBlock).sizeTotal = num;
    }
}

static struct linkedList *makeLinkedList(int number){
    //struct linkedList linkedListArray[number] = {0, 0};
    struct linkedList *dynamicLink;
    struct linkedInfo info = {0};
    dynamicLink = (struct linkedList*) malloc(number);
    dynamicLink[0].value = 0;
    dynamicLink[0].next = &dynamicLink[1];
    dynamicLink[0].prev = &dynamicLink[number-1];
    dynamicLink[0].info = &info;
    for (int i = 1; i < number-1; i++){
        dynamicLink[i].value = i;
        dynamicLink[i].next = &dynamicLink[i+1];
        dynamicLink[i].prev = &dynamicLink[i-1];
        dynamicLink[i].info = &info;
    }
    dynamicLink[number-1].value = number-1;
    dynamicLink[number-1].next = &dynamicLink[0];
    dynamicLink[number-1].prev = &dynamicLink[number-2];
    dynamicLink[number-1].info = &info;
    changeLen(&info, number);
    return dynamicLink;
}

int *lenLL(struct linkedList array[]){
    return &(*array[0].info).length;
}

void printLinkedList(struct linkedList array[]){
    for (int i = 0; i < 100; i++){
        printf("%p has value: %d, next is: %p, prev is: %p\n", &array[i], array[i].value, array[i].next, array[i].prev);
    }
}

void appendLL(struct linkedList array[], struct linkedList pointer, int value){
    if (array[0].info -> length == array[0].info -> sizeTotal){
        array = realloc(array, array[0].info -> sizeTotal+1);
    }
    array[0].info -> length++;
    array[array[0].info -> length].value = value;
    array[array[0].info -> length].prev = &pointer;
    array[array[0].info -> length].next = pointer.next;
    array[array[0].info -> length].info = array[0].info;
    (*pointer.next).prev = &array[array[0].info -> length];
    pointer.next = &array[array[0].info -> length];
}


