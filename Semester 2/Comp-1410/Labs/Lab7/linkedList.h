//
// Created by evanm on 2021-03-17.
//

typedef struct sll{
    int val;
    struct sll *next;
} sll;

typedef struct dll{
    int val;
    struct dll *next;
    struct dll *prev;
} dll;


sll *newSinglyNode(int val, sll *nextNode){
    sll *temp = (sll*) calloc(1, sizeof(sll));
    temp -> val = val;
    temp -> next = nextNode;
    return temp;
}

dll *newDoublyNode(int val, dll *nextNode, dll *prevNode){
    dll *temp = (dll*) calloc(1, sizeof(dll));
    temp -> val = val;
    temp -> next = nextNode;
    temp -> prev = prevNode;
    return temp;
}

sll *SCLL(int arr[], int n){
    sll *tempList = (sll*) malloc(sizeof(sll));
    tempList = newSinglyNode(arr[n-1], NULL);
    //sll *tempList = newSinglyNode(arr[n-1], NULL);
    sll *first = tempList;
    for (int i = n-2; 0 <= i; i--){
        tempList = newSinglyNode(arr[i], tempList);
    }
    first -> next = tempList;
    return tempList;
}

dll *DCLL(int arr[], int n){
    dll *tempList = (dll*) malloc(sizeof(dll));
    tempList = newDoublyNode(arr[n-1], NULL, NULL);
    //sll *tempList = newSinglyNode(arr[n-1], NULL);
    dll *first = tempList;
    for (int i = n-2; 0 <= i; i--){
        tempList = newDoublyNode(arr[i], tempList, NULL);
        tempList -> next -> prev = tempList;
    }
    first -> next = tempList;
    tempList -> prev = first;
    return tempList;
}