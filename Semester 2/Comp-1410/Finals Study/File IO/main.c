#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct node{
    int value;
    struct node *next;
};

bool is_palindrome(char str[], int n){
    int start = 0;
    int end = n - 1;
    while (start < end){
        if (str[start] != str[end]) return false;
        else start++, end--;
    }
    return true;
}

void remove_from_list(struct node *lst1, struct node *lst2){
    struct node *cur_node1 = lst1;
    struct node *temp;
    while (cur_node1 != NULL){
        struct node *cur_node2 = lst2;
        while (cur_node2 -> next != NULL){
            if (cur_node2 -> next -> value == cur_node1->value){
                temp = cur_node2 -> next;
                cur_node2 -> next = cur_node2 -> next -> next;
                free(temp);
            }
            else{
                cur_node2 = cur_node2 -> next;
            }

        }
        cur_node1 = cur_node1 -> next;
    }
}

struct node *create_node(struct node *np, int value){
    struct node *head = np;
    while (np != NULL && np -> next != NULL){
        np = np -> next;
    }
    struct node *newNodes = (struct node*) calloc(1, sizeof(struct node));
    newNodes -> value = value;
    if (np == NULL){
        return newNodes;
    }
    np -> next = newNodes;
    return head;
}


int foo(int x){
    int y = x - 1;
    return y;
}

int bar(int x){
    int y = x - 2;
    return y;
}


int main() {
    int x = 5;
    int y = foo(x - 1);
    int z = bar(x - 2);
    printf("%d\n", is_palindrome("abba", 4));
    printf("%d\n", is_palindrome("abcba", 5));
    printf("%d\n", is_palindrome("abbc", 4));
    printf("%d\n", is_palindrome("abcdcba", 7));
    printf("%d\n", is_palindrome("abccba", 6));
    printf("%d\n", is_palindrome("a", 1));
    printf("%d\n", is_palindrome("", 0));
    struct node *newNode = NULL;
    newNode = create_node(newNode, 5);
    newNode = create_node(newNode, 4);
    newNode = create_node(newNode, 8);
    newNode = create_node(newNode, 9);
    newNode = create_node(newNode, 4);
    newNode = create_node(newNode, 3);
    newNode = create_node(newNode, 3);
    newNode = create_node(newNode, 8);
    newNode = create_node(newNode, 7);
    newNode = create_node(newNode, 1);
    newNode = create_node(newNode, 9);
    newNode = create_node(newNode, 3);
    struct node *newNode2 = NULL;
    newNode2 = create_node(newNode2, 1);
    newNode2 = create_node(newNode2, 3);
    remove_from_list(newNode2, newNode);
}
