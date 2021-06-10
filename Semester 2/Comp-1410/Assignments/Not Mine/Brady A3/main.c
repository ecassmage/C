/* ===========================================================================
COMP-1410 Assignment 3
==============================================================================
Student name: Brady Dedecker

Replace the error with statement citing any sources of outside help:
ERROR_NO_INTEGRITY_STATEMENT

=========================================================================== */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Linked list node that holds a student record
struct snode {
    int id;
    char * name;
    struct snode * next;
};

// Student list structure
struct slist {
    struct snode * front;
};

// create_list() returns an empty newly-created list of students
// note: caller must free using free_list
struct slist * create_list(){
    struct slist *ptr = NULL;
    ptr = (struct slist*)malloc(sizeof(struct slist));
    ptr->front = NULL;
    return ptr;
}

// insert_student(id, name, lst) attempts to add a student with given id and
//   name into the given list lst; if a student with that id is already in the
//   list then return false, otherwise lst is modified and true is returned
bool insert_student(int id, char name[], struct slist * lst){
    struct snode * student = (struct snode *) malloc(sizeof(struct snode));
    student->name = (char*)malloc(sizeof(strlen(name)+1));
    struct snode * search = lst->front;
    if(student->name==NULL){
        return false;
    }
    student->id = id;
    strcpy(student->name, name);
    student->next = NULL;

    if(lst->front == NULL){
        lst->front = student;
        return true;
    }
    if (student == NULL){
        return 0;
    }
    else{
        while(search->next != NULL){
            if(search->id == id){
                return false;
            }

            else if(search->next->id > id){
                student->next = search ->next;
                search->next = student;
                return true;
            }
            search = search->next;
        }
        search->next = student;
    }
    return true;
}


// remove_student(id, lst) attempts to remove a student with given id from the
//   given list and free the memory allocated to that student; true is returned
//   if successful and false otherwise
bool remove_student(int id, struct slist * lst){
    if (id == lst->front->id){
        struct snode *remove = lst->front;
        lst->front = lst->front->next;
        free(remove);
        return true;
    }
    if(id == lst ->front->next->id){
        struct snode *remove = lst->front->next;
        lst->front->next = lst->front->next->next;
        free(remove);
        return true;
    }
    struct snode * temp = lst -> front -> next;
    while(temp -> next != NULL){
        if(temp -> next -> id == id){
            struct snode *removeNode = temp -> next;
            temp -> next = temp -> next -> next;
            free(removeNode);
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

// find_student(id, lst) returns the name of the student with given id in the
//   given list lst in a dynamically-allocated string (that the caller must
//   free) or NULL if no student has that id
char * find_student(int id, struct slist * lst){
    struct snode * search = lst->front;
    if(lst == NULL){
        return NULL;
    }
    while(search != NULL){
        if(search->id==id){
            return search->name;
        }
        search = search->next;
    }
    return NULL;
}


// free_list (lst) deallocates all memory associated with the given list lst
//   including the memory used by the student records in the list
void free_list(struct slist * lst){
    struct snode *ptr = lst ->front;
    while(ptr!= NULL){
        struct snode *freed = ptr;
        ptr = ptr -> next;
        free(freed->name);
        free(freed);
    }
    free(lst);
}
// merge_lists(out, lst1, lst2) merges the student records from lst1 and lst2
//   into the list out with the students in sorted order;
//   lst1 and lst2 are then freed
//assumed the lists were already ordered least to greatest sperately before merging
// requires: out starts as an empty list
void merge_lists(struct slist * out, struct slist * lst1, struct slist * lst2){
    struct snode *list1 = lst1->front;
    struct snode *list2 = lst2->front;
    struct snode *append;
    struct snode *temp = NULL;
    if(list1->id > list2->id){
        append = list2;
        list2 = list2->next;
        //append = append->next;
    }
    else{
        append = list1;
        list1 = list1->next;
        //append = append->next;
    }
    out -> front = append;
    temp = append;
    //temp = temp -> next;
    while(list1 != NULL || list2 != NULL){
        if(list1 == NULL && list2 != NULL){
            append = list2;
            list2= list2->next;
        }
        else if(list1 != NULL && list2 ==NULL){
            append = list1;
            list1 = list1->next;
        }
        else if(list1->id >= list2->id){
            append = list2;
            list2 =list2->next;
        }
        else{
            append = list1;
            list1= list1->next;
        }
        if(temp == NULL){
            out->front = append;
            temp = append;
        }
        else{
            temp->next = append;
        }
        temp = temp->next;
    }
    free(list1);
    free(list2);
}

// Tree node holding the numeric value that a word compresses to
struct treenode {
    char word[10];
    int value;
    struct treenode * left;
    struct treenode * right;
};

// insert_node(word, value, tree) inserts a new node containing the given word
//   and value into the tree with given root (or NULL denoting an empty tree)
//   returns the root node of the tree following the insert
// requires: word is not already in the given tree
//           tree satisfies the ordering property
struct treenode * insert_node(char word[], int value, struct treenode * tree);

// lookup_word(word, tree) returns the numeric value associated with the given
//   word in the given tree (or 0 if the word does not appear in the tree);
//   tree points to the root node or is NULL (denoting an empty tree)
// requires: tree satisfies the ordering property
int lookup_word(char word[], struct treenode * tree);

// free_tree(tree) frees all memory associated in the tree with given root node
void free_tree(struct treenode * tree);

int main(void) {
    struct slist * list1;
    struct slist * list2;
    struct slist *out;
    list1 = create_list();
    list2 = create_list();
    out = create_list();

    insert_student(100000001, "Carroll", list1);
    insert_student(110036028, "Brady", list1);
    insert_student(123456789, "Jimmy", list1);

    assert(strcmp(find_student(110036028, list1), "Brady")==0);
    assert(strcmp(find_student(100000001, list1), "Carroll")==0);
    assert(strcmp(find_student(123456789, list1), "Jimmy")==0);

    insert_student(238965427, "Leon", list2);
    insert_student(876543829, "Dr.Saad", list2);
    insert_student(987654321, "Ozzy", list2);
    assert(strcmp(find_student(876543829, list2), "Dr.Saad")==0);
    assert(strcmp(find_student(876543829, list2), "Ozzy")!=0);
    assert(strcmp(find_student(987654321, list2), "Ozzy")==0);
    printf("All tests passed successfully");

    merge_lists(out, list1, list2);
    int arr[6] = {100000001,110036028, 123456789, 238965427, 876543829, 987654321};
    struct snode * temp = out->front;
    for(int i = 0; i < 6; i++){
        assert(temp->id == arr[i]);
        temp = temp->next;
    }
}

