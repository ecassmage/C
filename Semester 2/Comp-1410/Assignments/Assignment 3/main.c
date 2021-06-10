/* ===========================================================================
COMP-1410 Assignment 3
==============================================================================
Student name: Evan Morrison

Replace the error with statement citing any sources of outside help:
None

=========================================================================== */
/// Asserts: From Lines 107 - 178
/// main: from Lines 180 - 202
/// Part 1: From Lines 204 - 317
/// Part 2: From Lines 319 - 349
/// My Stuff is mostly after Part 2, Though some stuff is above the asserts.
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Linked list node that holds a student record
typedef struct node{
  int id;
  char *name;
  struct node *next;
} node;

// Student list structure
typedef struct sList {
    node *front;
} list;

// create_list() returns an empty newly-created list of students
// note: caller must free using free_list
list *create_list();

// insert_student(id, name, lst) attempts to add a student with given id and
//   name into the given list lst; if a student with that id is already in the
//   list then return false, otherwise lst is modified and true is returned
bool insert_student(int id, char name[], list *lis);

// remove_student(id, lst) attempts to remove a student with given id from the
//   given list and free the memory allocated to that student; true is returned
//   if successful and false otherwise
bool remove_student(int id, list *lis);

// find_student(id, lst) returns the name of the student with given id in the
//   given list lst in a dynamically-allocated string (that the caller must
//   free) or NULL if no student has that id
char *find_student(int id, list *lis);

// free_list (lst) deallocates all memory associated with the given list lst
//   including the memory used by the student records in the list
void free_list(list *lis);

// merge_lists(out, lst1, lst2) merges the student records from lst1 and lst2
//   into the list out with the students in sorted order;
//   lst1 and lst2 are then freed
// requires: out starts as an empty list
void merge_lists(list * out, list *lis1, list *lis2);

// Tree node holding the numeric value that a word compresses to
typedef struct treeNode {
  char word[10];
  int value;
  /// Yes I know the names don't make sense I misread the assignment and made a doubly linked list. Now I am too far
  /// along to change the names, it functions properly I assume. Who knows maybe I misread the assignment again.
  struct treeNode *prev;  // prev is left.
  struct treeNode *next;  // next is right.
} treeNode;

void errorNode(node *newNode){
    if (newNode == NULL) exit(1100);
}
void errorChar(const char *newChar){
    if (newChar == NULL) exit(1100);
}
void printTree(treeNode *node);
signed int stringCmp(const char *char1, const char *char2);

// insert_node(word, value, tree) inserts a new node containing the given word
//   and value into the tree with given root (or NULL denoting an empty tree)
//   returns the root node of the tree following the insert
// requires: word is not already in the given tree
//           tree satisfies the ordering property
treeNode *insert_node(char word[], int value, treeNode *tree);

// lookup_word(word, tree) returns the numeric value associated with the given
//   word in the given tree (or 0 if the word does not appear in the tree);
//   tree points to the root node or is NULL (denoting an empty tree)
// requires: tree satisfies the ordering property
int lookup_word(char word[], treeNode *tree);

// free_tree(tree) frees all memory associated in the tree with given root node
void free_tree(treeNode *tree);
void printList(list *lis);
void makeSentence();

list *copyList(list *copyList){
    list *newList = create_list();
    insert_student(copyList -> front -> id, copyList -> front -> name, newList);
    return newList;
}
node *createStudent(int id, char name[]);
void TreePosition(treeNode *compareTreeNode, treeNode *newNode);
bool assertingAsserts(){
    list *list1 = create_list();
    assert(insert_student(12345678, "Evan", list1) == 1);
    assert(insert_student(12345679, "Connor", list1) == 1);
    assert(insert_student(12345679, "Connor", list1) == 0);
    assert(insert_student(12345680, "Bob", list1) == 1);
    assert(insert_student(12345682, "John", list1) == 1);
    //list *pointingToList1 = copyList(list1);

    list *list2 = create_list();
    assert(insert_student(64564, "Far", list2) == 1);
    assert(insert_student(465456, "Jeep", list2) == 1);
    assert(insert_student(5345354, "Harry", list2) == 1);
    assert(insert_student(12345681, "Grinning", list2) == 1);
    assert(insert_student(11223344, "GrinningEvan", list2) == 1);
    assert(insert_student(34534532, "Ron", list2) == 1);
    assert(insert_student(45644564, "Jim", list2) == 1);
    assert(insert_student(456456456, "MeepDaBoy", list2) == 1);
    //list *pointingToList2 = copyList(list2);

    list *output1 = create_list();
    merge_lists(output1, list1, list2);
    // Apparently attempting to prove freedom is difficult and can lead to crashing.
    //assert(list1 -> front -> id != pointingToList1 -> front -> id); // proof that it freed
    //assert(list2 -> front -> id != pointingToList2 -> front -> id); // proof that it free
    // can't assert chars after freed since memory is impossible to rate accurately.
    int arrayOfTheRealNumbers[] = {64564, 465456, 5345354, 11223344, 12345678, 12345679, 12345680, 12345681, 12345682, 34534532, 45644564, 456456456, 0};
    char arrayOfTheRealWords[][13] = {"Far", "Jeep", "Harry", "GrinningEvan", "Evan", "Connor", "Bob", "Grinning", "John", "Ron", "Jim", "MeepDaBoy"};
    node *weGotThePointerQuestionMark = output1 -> front;
    printf("First Section Done.\n");

    for (int i = 0; arrayOfTheRealNumbers[i] != 0; i++){
        assert(arrayOfTheRealNumbers[i] == weGotThePointerQuestionMark -> id);
        assert(strcmp(arrayOfTheRealWords[i], weGotThePointerQuestionMark -> name) == 0);
        weGotThePointerQuestionMark = weGotThePointerQuestionMark -> next;
    }
    printf("Second Section Done.\n");

    assert(strcmp(find_student(11223344, output1), "GrinningEvan") == 0);
    assert(strcmp(find_student(12345680, output1), "Bob") == 0);
    assert(strcmp(find_student(456456456, output1), "MeepDaBoy") == 0);
    assert(strcmp(find_student(45644564, output1), "Jim") == 0);
    assert(strcmp(find_student(64564, output1), "Far") == 0);
    assert(find_student(2112, output1) == NULL);
    printf("Third Section Done.\n");

    assert(strcmp(find_student(12345680, output1), "Bob") == 0);
    remove_student(12345680, output1);
    assert(find_student(12345680, output1) == NULL);
    printf("Fourth Section Done.\n");
    free_list(output1); // debugged it and saw gibberish so it probably works.
    treeNode  *treeOfLife = (treeNode*) calloc(1, sizeof(treeNode));
    insert_node("mango", 1, treeOfLife);
    insert_node("word", 2, treeOfLife);
    insert_node("words", 3, treeOfLife);
    insert_node("apple", 4, treeOfLife);
    insert_node("flip", 5, treeOfLife);
    insert_node("house", 6, treeOfLife);
    insert_node("last", 7, treeOfLife);
    insert_node("thing", 8, treeOfLife);
    assert(lookup_word("apple", treeOfLife) == 4);
    assert(lookup_word("word", treeOfLife) == 2);
    assert(lookup_word("last", treeOfLife) == 7);
    assert(lookup_word("words", treeOfLife) == 3);
    assert(lookup_word("thing", treeOfLife) == 8);
    assert(lookup_word("house", treeOfLife) == 6);
    assert(lookup_word("flip", treeOfLife) == 5);
    assert(lookup_word("flippy", treeOfLife) == 0);
    printf("Fifth Section Done.\n");
    free_tree(treeOfLife);  // debugged it and saw gibberish so it probably works.
    return true;
}

int main(void) {
    // Perform your testing here
    assert(assertingAsserts());
    printf("All Asserts have finished, This includes all asserts for both Part 1 and Part 2 which have finished, now onto other stuff\n");
    list *Hello = create_list();
    printf("%d\n", insert_student(12345678, "Evan", Hello));
    printf("%d\n", insert_student(12345679, "Connor", Hello));
    printf("%d\n", insert_student(12345679, "Connor", Hello));
    printf("%d\n", insert_student(12345680, "Bob", Hello));
    printf("%d\n", insert_student(12345681, "John", Hello));
    list *Hello2 = create_list();
    printf("%d\n", insert_student(64564, "Far", Hello2));
    printf("%d\n", insert_student(465456, "Jeep", Hello2));
    printf("%d\n", insert_student(5345354, "Harry", Hello2));
    printf("%d\n", insert_student(12345681, "Grinning", Hello2));
    printf("%d\n", insert_student(34534532, "Ron", Hello2));
    printf("%d\n", insert_student(45644564, "Jim", Hello2));
    printf("%d\n", insert_student(456456456, "Meep", Hello2));
    list *Hello3 = create_list();
    merge_lists(Hello3, Hello, Hello2);
    printList(Hello3);
    makeSentence();
}

list *create_list(){
    list *temp = (list*) calloc(1, sizeof(list));;
    if (temp == NULL)
        exit(0);
    return temp;
}

bool insert_student(int id, char name[], list *lis){
    if (lis -> front == NULL){
        lis -> front = createStudent(id, name);
    }
    else{
        node *ptr = lis -> front;
        while (ptr -> next != NULL){
            if (ptr -> id == id) return false;
            else if (id < ptr -> next -> id){
                node *newStudent = createStudent(id, name);
                newStudent -> next = ptr -> next;
                ptr -> next = newStudent;
                return true;
            }
            ptr = ptr -> next;
        }
        if (ptr -> id != id) ptr -> next = createStudent(id, name);
        else return false;
    }
    return true;
}

bool remove_student(int id, list *lis){
    if (lis -> front == NULL){
        return false;
    }
    else{
        node *ptr = lis -> front;
        while (ptr -> next != NULL){
            if (ptr -> next -> id == id){
                node *clean = ptr -> next;
                ptr -> next = ptr -> next -> next;
                free(clean -> name);
                free(clean);
                return true;
            }
            ptr = ptr -> next;
        }
        if (ptr -> next -> id == id){
            node *clean = ptr -> next;
            ptr -> next = ptr -> next -> next;
            free(clean -> name);
            free(clean);
            return true;
        }
    }
    return false;
}

char *find_student(int id, list *lis){
    if (lis -> front != NULL){
        node *ptr = lis -> front;
        while (ptr -> next != NULL){
            if (ptr -> id == id){
                return ptr -> name;
            }
            ptr = ptr -> next;
        }
        if (ptr -> id == id){
            return ptr -> name;
        }
    }
    return NULL;
}

void free_list(list *lis){
    node *ptr = lis -> front;

    while (ptr != NULL) {
        node *clean = ptr;
        ptr = ptr -> next;
        free(clean -> name);
        free(clean);
    }
    free(lis);
}

void merge_lists(list *out, list *lis1, list *lis2){
    // Luckily I wrote a python merge sort a couple weeks ago so I just copied that.
    node *listPtr1 = lis1 -> front;
    node *listPtr2 = lis2 -> front;

    if (listPtr1 -> id < listPtr2 -> id){
        out -> front = listPtr1;
        listPtr1 = listPtr1 -> next;
    }
    else {
        out -> front = listPtr2;
        listPtr2 = listPtr2 -> next;
    }
    node *outPtr = out -> front;
    while (listPtr1 != NULL || listPtr2 != NULL){
        if (listPtr1 == NULL || (listPtr2 != NULL && (listPtr2 -> id < listPtr1 -> id))){
            outPtr -> next = listPtr2;
            outPtr = outPtr -> next;
            listPtr2 = listPtr2 -> next;
        }
        else{
            outPtr -> next = listPtr1;
            outPtr = outPtr -> next;
            listPtr1 = listPtr1 -> next;
        }
    }
    free(lis1); // need to use free since using free_list will also wipe out and because of overlap will crash free_list(lis2);.
    printf("Hello\n");
    free(lis2); // need to use free since using free_list will also wipe out.
}

treeNode *insert_node(char word[], int value, treeNode *tree){
    treeNode *tempTree = (treeNode*) calloc(1, sizeof(treeNode));
    strcpy(tempTree -> word, word);
    tempTree -> value = value;
    TreePosition(tree, tempTree);
    return tempTree;
}

int lookup_word(char word[], treeNode *tree) {
    if (tree == NULL) {
        return 0;
    }
    signed int num = stringCmp(word, tree->word);
    switch (num) {
        case (-1):
            return lookup_word(word, tree->prev);
        case (0):
            return tree->value;
        case (1):
            return lookup_word(word, tree->next);
    }
    return 0;
}

void free_tree(treeNode *tree){
    if (tree != NULL){
        free_tree(tree -> prev);
        free_tree(tree -> next);
        free(tree);
    }
}

node *createStudent(int id, char name[]){
    node *newNode = (node*) calloc(1, sizeof(node));
    errorNode(newNode);
    newNode -> name = (char*) calloc(strlen(name) + 1, sizeof(char));
    errorChar(newNode -> name);
    strcpy(newNode -> name, name);
    newNode -> id = id;
    return newNode;
}

void printLine(node *ptr, int c){
    printf("Student ");
    printf("<%d>:\n\tStudent id: ", c);
    printf("%d\n\tStudent name: ", ptr -> id);
    if (ptr -> next == NULL) printf("%s\n\tNext Student Memory Address: NULL\n\n", ptr -> name);
    else                     printf("%s\n\tNext Student Memory Address: %p\n\n", ptr -> name, ptr -> next);
}
void printTab(int number){
    for (int i = 0; i <= number; i++){
        printf("\t");
    }
}

void printTabbing(node *ptr, int c){
    /// Nice and pretty printing in debugger form. Basically just prints it out, tabbing every new student.
    /// Don't actually know what this style of viewing the information is actually called, ... maybe menu format? so
    /// I am going to call it debugger format since it is how the debugger tends to showcase the information.
    if (ptr == NULL){
        printf(" Last Student\n}\n");
        return;
    }
    else if (c != 1){
        printf(" Next Student\n\n");
    }
    else{
        printf("{\n");
    }
    printTab(c-1);
    printf("Student ");
    printf("<%d>:{\n", c);
    printTab(c);
    printf("Student id: ");
    printf("%d\n", ptr -> id);
    printTab(c);
    printf("Student name: ");
    printf("%s\n", ptr -> name);
    printTab(c);
    printf("}");
    printTabbing(ptr -> next, c+1);
}

void printList(list *lis){
    if (lis -> front == NULL){
        printf("The list is empty.\n");
        return;
    }
    else {
        printf("debugger format or standard (type anything other then debugger for standard, NO capitals): ");
        char array[10];
        scanf("%9s", array);
        while (getchar() != '\n');
        printf("\n");
        if (strcmp(array, "debugger") == 0){
            printTabbing(lis -> front, 1);
        }
        else{
            node *ptr = lis->front;
            int c = 1;
            while (ptr != NULL) {
                printLine(ptr, c);
                ptr = ptr -> next;
                c++;
            }
        }
    }
}

void Try(const char *line){
    if (line == NULL) assert(1==0);
}

bool findWord(const char *input, int *n, char *output){
    int c = 0;
    memset(output, 0, 10);
    while (input[*n] != '\0' && input[*n] != ' ' && input[*n] != '\n'){
        if (c >= 10) {
            printf("Word is too long");
            exit(0);
        }
        output[c++] = input[(*n)++];

    }
    if (input[*n] == '\0') return true;
    (*n)++;
    return false;
}

void makeSentence(){
    /// I hate C so Much.
    /// Since no O(n) limit was asked I can do whatever inefficient thing I want to make.
    int size = 10;
    int ptr = 0;
    char *sentence = (char *) calloc(10, sizeof(char));
    Try(sentence);
    printf("Insert Word or Something: ");
    // I don't know why I chose to do it this way but I did it this way. and now I can catch anything muwhhahahahah.
    fflush(stdin);
    scanf("%c", &sentence[ptr]);
    if (sentence[ptr] != '\n' && sentence[ptr] != '\0') ptr++; // \n was giving me issues never disappearing so this is my solution to that.
    bool space = false;
    do{
        scanf("%c", &sentence[ptr++]);
        if (sentence[ptr-1] == ' '){
            sentence[ptr-1] = '\0';
            space = true;
        }
        else if (space == true && sentence[ptr-1] != '.'){
            sentence[ptr-2] = ' ';
            space = false;
        }
        if (ptr == size && sentence[ptr-1] != '.'){
            sentence = (char *) realloc(sentence, (size * 10) * sizeof(char));
            size *= 10;
            Try(sentence);
        }

    } while (sentence[ptr-1] != '.');
    sentence[ptr-1] = '\0';
    treeNode *treeOfLife = (treeNode*) calloc(1, sizeof(treeNode));
    int c = 0, value = 1;
    char word[10] = {'\0'};
    findWord(sentence, &c, word);
    treeOfLife -> value = value++;
    strcpy(treeOfLife -> word, word);
    treeNode *treeOfLifeTemp = treeOfLife;

    if (c < strlen(sentence)) printf("%s ", word);
    else printf("%s\n", word);
    memset(word, 0, 10);

    while (findWord(sentence, &c, word) == 0){
        if (strcmp(word, " ") == 0) printf("Hello");
        else if (lookup_word(word, treeOfLife) == 0){
            treeOfLifeTemp = insert_node(word, value, treeOfLife);
            value++;
            printf("%s ", word);
        }
        else{
            printf("%d ", lookup_word(word, treeOfLife));
        }

        memset(word, 0, 10);
    }
    if (lookup_word(word, treeOfLife) == 0){
        treeOfLifeTemp = insert_node(word, value, treeOfLifeTemp);
        printf("%s\n", word);
    }
    else{
        printf("%d\n", lookup_word(word, treeOfLife));
    }
    printf("The sentence it should look like is\n"
           "a man 1 plan 1 canal panama backwards is 5 4 1 3 1 2 1\n");
    printTree(treeOfLife);
}

signed int stringCmp(const char *char1, const char *char2){
    int c = 0;
    while (char1[c] != '\0'){
        if (char1[c] < char2[c]){
            return -1;
        }
        else if (char2[c] < char1[c]){
            return 1;
        }
        c++;
    }
    if (strlen(char1) < strlen(char2)) return -1;
    else if (strlen(char2) < strlen(char1)) return 1;
    return 0;
}

void TreePosition(treeNode *compareTreeNode, treeNode *newNode){
    signed int num = stringCmp(newNode -> word, compareTreeNode -> word);
    switch (num){
        case (-1):
            if (compareTreeNode -> prev == NULL){
                compareTreeNode -> prev = newNode;
            }
            else
                TreePosition(compareTreeNode -> prev, newNode);
            break;
        case (0):
            printf("Not Possible\n");
            // While I am not using this as I do stuff elsewhere, I could just use this to catch matching words
            // returning and not allowing the new node to be added to the tree. alternatively if you dislike the fact
            // that a new tree node is made even if a word  matches, I can just switch this function to match just a
            // char word I send up and return a pointer to the position to  where the new node should go, then after
            // returning to the insert_node section, creating a new node if I didn't receive a NULL and then inserting.
            break;
        case (1):
            if (compareTreeNode -> next == NULL) {
                compareTreeNode -> next = newNode;
            }
            else
                TreePosition(compareTreeNode -> next, newNode);
            break;
    }
}

void printTree(treeNode *node){
    if (node != NULL){
        printf("Node %d: value: %d, word: %s\n", node -> value, node -> value, node -> word);
        printTree(node -> prev);
        printTree(node -> next);
    }
}