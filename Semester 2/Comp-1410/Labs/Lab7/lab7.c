/* ===========================================================================
COMP -1410 Lab 7
==============================================================================
Student name: Evan Morrison
Replace the error with a statement citing any sources of outside help:
None
=========================================================================== */
/// Forgot a section of free_node asserting and forgot to change the stuff above here.
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
// Linked list node storing a string of at most 4 characters
typedef struct strNode {
    char str[5]; // I assume I am not supposed to change this from size 5.
    struct strNode *next;
}strNode;
// create_node(str, next) creates a strnode containing the string str
// and given next pointer; caller must free allocated memory using free_node
// requires: str has length at most 4
// next is NULL or points to a strnode
// note: returns NULL if memory cannot be allocated
strNode * create_node(char str[], strNode * next);
// free_node(node) frees the memory associated with the given node; returns a
// pointer to the next node in the list previously headed by the given node
// requires: node is a valid strnode allocated dynamically
strNode * free_node(strNode * node);
// concat_nodes(head , str) modifies str to be a string representation of the
// contents of the list with given head
// requires: str points to enough memory to store the output string
// head is NULL or points to a strnode
void concat_nodes(strNode * head , char * str);
unsigned int sizeOf(strNode * head);

/// Asserts directly below
void createNodeAsserts(){
    strNode *temp = create_node("Z", NULL);
    assert(temp -> next == NULL);
    assert(strcmp(temp -> str, "Z") == 0);
    strNode *tempZ = temp;

    temp = create_node("Y", temp);
    assert(temp -> next -> next == NULL);
    assert(temp -> next == tempZ);
    assert(strcmp(temp -> next -> str, "Z") == 0);
    assert(strcmp(temp -> str, "Y") == 0);
    strNode *tempY = temp;

    temp = create_node("L", temp);
    assert(temp -> next -> next -> next == NULL);
    assert(temp -> next -> next == tempZ);
    assert(temp -> next == tempY);
    assert(strcmp(temp -> next -> next -> str, "Z") == 0);
    assert(strcmp(temp -> next -> str, "Y") == 0);
    assert(strcmp(temp -> str, "L") == 0);
    strNode *tempL = temp;

    temp = create_node("A", temp);
    assert(temp -> next -> next -> next -> next == NULL);
    assert(temp -> next -> next -> next == tempZ);
    assert(temp -> next -> next == tempY);
    assert(temp -> next == tempL);
    assert(strcmp(temp -> next -> next -> next -> str, "Z") == 0);
    assert(strcmp(temp -> next -> next -> str, "Y") == 0);
    assert(strcmp(temp -> next -> str, "L") == 0);
    assert(strcmp(temp -> str, "A") == 0);
}

strNode *free_nodesAsserts(strNode *head, char *newWord){
    char *tempWord = (char*) calloc(strlen(head -> str), sizeof(char));
    strNode *tempNode = head -> next;
    strcpy(tempWord, head -> str);
    assert(strcmp(head -> str, tempWord) == 0);
    head = free_node(head);
    assert(tempNode == head);
    assert(strcmp(head -> str, newWord) == 0);
    assert(strcmp(head -> str, tempWord) != 0);
    // This won't assert properly if duplicate words are being used just comment assert(strcmp(head -> str, tempWord) != 0); to fix it.
    return head;
}

void concatNodesAsserts(){
    strNode *head = create_node("sea", NULL);
    head = create_node("bee", head);
    head = create_node("eh", head);
    char *meh = (char*) calloc(sizeOf(head), sizeof(char));
    concat_nodes(head, meh);
    assert(strcmp(meh, "eh bee sea") == 0);
    assert(strcmp(head -> str, "eh") == 0);
    head = free_nodesAsserts(head, "bee");
    head = free_nodesAsserts(head, "sea");
    head = free_node(head);
    assert(head == NULL);
    free(meh);

    head = create_node("?", NULL);
    head = create_node("goal", head);
    head = create_node("your", head);
    head = create_node("is", head);
    head = create_node("what", head);
    head = create_node("fly", head);
    head = create_node("to", head);
    head = create_node("were", head);
    head = create_node("you", head);
    head = create_node("If", head);
    meh = (char*) calloc(sizeOf(head), sizeof(char));
    concat_nodes(head, meh);
    assert(strcmp(meh, "If you were to fly what is your goal ?") == 0);
    assert(strcmp(head -> str, "If") == 0);
    head = free_nodesAsserts(head, "you");
    head = free_nodesAsserts(head, "were");
    head = free_nodesAsserts(head, "to");
    head = free_nodesAsserts(head, "fly");
    head = free_nodesAsserts(head, "what");
    head = free_nodesAsserts(head, "is");
    head = free_nodesAsserts(head, "your");
    head = free_nodesAsserts(head, "goal");
    head = free_nodesAsserts(head, "?");
    head = free_node(head);
    assert(head == NULL);
    free(meh);

    head = create_node("zero", NULL);
    head = create_node("Zero", head);
    head = create_node("one", head);
    head = create_node("One", head);
    meh = (char*) calloc(sizeOf(head), sizeof(char));
    concat_nodes(head, meh);
    assert(strcmp(meh, "One one Zero zero") == 0);
    assert(strcmp(head -> str, "One") == 0);
    assert(head != NULL);
    head = free_nodesAsserts(head, "one");
    assert(head != NULL);
    head = free_nodesAsserts(head, "Zero");
    assert(head != NULL);
    head = free_nodesAsserts(head, "zero");
    head = free_node(head);
    assert(head == NULL);
    free(meh);
}
/// Asserts directly above

int main(void){
    // Implement your test code here
    createNodeAsserts(); // This asserts create_node. located above
    concatNodesAsserts(); // This asserts concat_nodes and free nodes. located above
    strNode *head = create_node("Z", NULL);
    for (int i = 1; i < 26; i++){
        char ltr[] = {(char) (90 - i), '\0'};
        head = create_node(ltr, head); // Replacing the next linked struct with previous one.
    }
    char *meh = (char*) calloc(sizeOf(head), sizeof(char)); // This is for concat string.
    concat_nodes(head, meh);
    printf("%s\n", meh);
    assert(strcmp(meh, "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z") == 0);
    printf("%s.\nThe Period shows that I caught the ending and therefore no space is probably there.\n", meh);
    assert(strcmp(meh, "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z") == 0);
    assert(strcmp(head->str, "A") == 0);
    for (int i = 66; i <= 90; i++) {
        char ltr[] = {(char) (i), '\0'};
        head = free_node(head);
        assert(strcmp(head->str, ltr) == 0);
    }
    head = free_node(head);
    assert(head == NULL);
    printf("\nAll tests passed successfully.\n");
}

unsigned int sizeOf(strNode * head){
    unsigned int size = 0;
    strNode *temp = head;
    while (temp -> next != NULL){
        /// strlen(temp -> str) gets the size of what will be added, + 1 adds a space and \0 at the end.
        size += strlen(temp -> str) + 1;
        temp = temp -> next;
    }
    return size;
}

strNode *create_node(char str[], strNode *next){
    struct strNode *notInTheMood = (strNode*) calloc(1, sizeof(strNode));
    strcpy(notInTheMood -> str, str);
    notInTheMood -> next = next;
    return notInTheMood;
}

strNode *free_node(strNode *node){
    strNode *tempMood = node -> next;
    free(node);
    return tempMood;
}

void concat_nodes(strNode * head, char *str){
    /// I have no idea if this is right or not since I am not completely sure what I was supposed to do but this is
    /// what I got. First I am not sure if I was just allowed to write a char arr[27] in main or something so I added
    /// a calloc to before this function so as to get the correct size of the linked list. While this could technically
    /// increase the big-O notation I would argue that it doesn't as it is just gathering the size for the function
    /// and is still equal to O(n) so the algorithm should still only be increasing in complexity by n.
    strNode *temp = head;
    while (1){
        strcpy(str + strlen(str), temp -> str);
        strcpy(str + strlen(str), " ");
        temp = temp -> next;
        if (temp -> next == NULL){
            strcpy(str + strlen(str), temp -> str);
            strcpy(str + strlen(str), "\0");
            break;
        }
    }
}