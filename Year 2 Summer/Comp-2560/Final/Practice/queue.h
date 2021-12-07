//
// Created by evanm on 2021-08-11.
//

#ifndef PRACTICE_QUEUE_H
#define PRACTICE_QUEUE_H

#ifndef _STRING_H_
#include <string.h>
#endif
#ifndef _STDLIB_H_
#include <stdlib.h>
#endif
#ifndef _SYS_TYPES_H
#include <types.h>
#endif



typedef struct queueMember{
    struct queueMember *next;
    struct queueMember *prev;
    int *pipeValues;
    char *name;
    pid_t Pid;
} queueMember;

typedef struct{
    queueMember *first;
    queueMember *last;
} queue;

void setPipe(queueMember *QM, const int pipeValues[2]);
void setName(queueMember *QM, const char *name);
void setPid(queueMember *QM, pid_t pid);

queue *Queue(){
    queue *temp = (queue*) malloc(sizeof(queue));
    temp -> first = NULL;
    temp -> last = NULL;
    return temp;
}

queueMember *newQueueMember(const int pipeValues[2], const char *name, pid_t pid){
    queueMember *temp = (queueMember*) malloc(sizeof(queueMember));

    temp -> next = NULL;

    temp -> prev = NULL;

    if (pipeValues != NULL)  setPipe(temp, pipeValues);
    else  temp -> pipeValues = NULL;

    if (name != NULL)  setName(temp, name);
    else  temp -> name = NULL;

    if (pid != -1)  setPid(temp, pid);
    else temp -> Pid = -1;

    return temp;
}

void setPipe(queueMember *QM, const int pipeValues[2]){
    QM -> pipeValues = (int*) malloc(sizeof(int) * 2);
    QM -> pipeValues[0] = pipeValues[0];
    QM -> pipeValues[1] = pipeValues[1];
}

void setName(queueMember *QM, const char *name){
    QM -> name = (char*) malloc(strlen(name) + 1);
    for (int i = 0; i < strlen(name); i++)  QM -> name[i] = name[i];
    QM -> name[strlen(name)] = '\0';
}

void setPid(queueMember *QM, pid_t pid){
    QM -> Pid = pid;
}

void addToQueue(queue *Q, queueMember *newAddition){
    if (Q -> first == NULL) Q -> first = newAddition;
    if (Q -> last != NULL) {
        Q -> last -> prev = newAddition;
        newAddition -> next = Q -> last;
    }
    Q -> last = newAddition;
}

void printQueue(queue *Q){
    queueMember *ptr = Q -> first;

    while (ptr != NULL){
        printf("%s\n", ptr -> name);
        ptr = ptr -> prev;
    }
}

#endif //PRACTICE_QUEUE_H
