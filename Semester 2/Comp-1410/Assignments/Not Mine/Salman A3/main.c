/* ===========================================================================
COMP-1410 Assignment 3
==============================================================================
Student name: Salman Chowdhury

Replace the error with statement citing any sources of outside help:
https://www.geeksforgeeks.org/use-fflushstdin-c/

=========================================================================== */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

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
struct slist * create_list();

// insert_student(id, name, lst1) attempts to add a student with given id and
//   name into the given list lst1; if a student with that id is already in the
//   list then return false, otherwise lst1 is modified and true is returned
bool insert_student(int id, char name[], struct slist * lst1);

// remove_student(id, lst1) attempts to remove a student with given id from the
//   given list and free the memory allocated to that student; true is returned
//   if successful and false otherwise
bool remove_student(int id, struct slist * lst1);

// find_student(id, lst1) returns the name of the student with given id in the
//   given list lst1 in a dynamically-allocated string (that the caller must
//   free) or NULL if no student has that id
char * find_student(int id, struct slist * lst1);

// free_list (lst1) deallocates all memory associated with the given list lst1
//   including the memory used by the student records in the list
void free_list(struct slist * lst1);

// merge_lists(out, lst1, lst2) merges the student records from lst1 and lst2
//   into the list out with the students in sorted order;
//   lst1 and lst2 are then freed
// requires: out starts as an empty list
void merge_lists(struct slist * out, struct slist * lst1, struct slist * lst2);


//testing_merged_list(lst1) returns true if the list is sorted and false if not
bool testing_merged_list(struct slist *lst);


//--------------------------------------------------------------------------------------------------------------//

struct slist * create_list(){
    struct slist *lst1 = malloc(sizeof(struct slist));
    if(lst1==NULL){
        printf("**ERROR**: Memory could not cannot be allocated\n");
        exit(0);
    }

    lst1->front = NULL;

    return lst1;
}

bool insert_student(int id, char name[], struct slist * lst1){
    //Check if the given id is already in the list
    struct snode *check_node = lst1->front;
    while(check_node != NULL){
        if(check_node->id == id){
            return 0;
        }
        check_node = check_node->next;
    }

    int len = strlen(name);
    struct snode *new_node = malloc(sizeof(struct snode));
    if(new_node==NULL){
        printf("**ERROR**: Memory could not cannot be allocated\n");
        exit(0);
    }

    new_node->name = malloc(len+1*sizeof(char));

    //If the given list is empty OR the given ID is smaller than the first ID in the current list
    if((lst1->front == NULL ) || (id < lst1->front->id)){
        new_node->id = id;

        strncpy(new_node->name, name,len);
        new_node->name[len] = '\0';

        new_node->next = lst1->front;
        lst1->front = new_node;

        return 1;
    }

        //If there is 1 or more nodes in the given list
    else{
        struct snode *previous = lst1->front;
        while( (previous->next != NULL ) && (id > previous->next->id) ){
            previous = previous->next;
        }

        new_node->id = id;

        strncpy(new_node->name, name, len);
        new_node->name[len] = '\0';

        new_node->next = previous->next;
        previous->next = new_node;

        return 1;
    }
}

bool remove_student(int id, struct slist * lst1){
    //If list is empty
    if(lst1->front == NULL){
        printf("**ERROR**: List is empty\n");
        return 0;
    }

    //If first node's ID is the same as the given ID
    if(lst1->front->id == id){
        struct snode *old_front_node = lst1->front;
        lst1->front = lst1->front->next;

        free(old_front_node->name);
        free(old_front_node);
        return 1;
    }

    //The node preceding the actual node to remove
    struct snode *previous = lst1->front;
    while( (previous->next != NULL) && (id != previous->next->id) ){
        previous = previous->next;
    }

    //If the node after the previous node is NULL, return false
    if(previous->next == NULL){
        return 0;
    }

    //Removing given node
    struct snode *node_to_be_removed = previous->next;
    previous->next = previous->next->next;

    free(node_to_be_removed->name);
    free(node_to_be_removed);

    return 1;


}

char * find_student(int id, struct slist * lst1){
    if(lst1->front == NULL){
        printf("**ERROR**: List is empty\n");
        return NULL;
    }

    struct snode *traverse = lst1->front;
    while(traverse != NULL){
        if(traverse->id == id){
            return traverse->name;
        }

        traverse = traverse->next;
    }

    return NULL;

}

void free_list(struct slist * lst){
    struct snode *cur_node = lst->front;
    struct snode *next_node = NULL;

    while(cur_node != NULL){
        next_node = cur_node->next;

        free(cur_node->name);
        free(cur_node);

        cur_node = next_node;
    }

    free(lst);
}

void merge_lists(struct slist * out, struct slist * lst1, struct slist * lst2){
    struct snode *list1 = lst1->front;
    struct snode *list2 = lst2->front;
    struct snode *merged_list = out->front;

    //For the front node of list "out"
    if( list1->id > list2->id ){
        out->front = list2;
        merged_list = list2;
        list2 = list2->next;
    }

    else if( list1->id < list2->id ){
        out->front = list1;
        merged_list = list1;
        list1 = list1->next;
    }

    //For the rest of the list
    while(1){

        if( (list1 == NULL) && (list2 != NULL) ){
            while(list2 != NULL){
                merged_list->next = list2;
                merged_list = list2;
                list2 = list2->next;
            }
            merged_list->next = NULL;
            break;
        }

        else if( (list1 != NULL) && (list2 == NULL)  ){
            while(list1 != NULL){
                merged_list->next = list1;
                merged_list = list1;
                list1 = list1->next;
            }
            merged_list->next = NULL;
            break;
        }


        if( list1->id > list2->id ){
            merged_list->next = list2;
            merged_list = list2;
            list2 = list2->next;
        }

        else if( list1->id < list2->id ){
            merged_list->next = list1;
            merged_list = list1;
            list1 = list1->next;
        }
    }

    free(lst1);
    free(lst2);
}

bool testing_merged_list(struct slist *lst){
    struct snode *traverse = lst->front;

    while(traverse != NULL){
        if( (traverse->next != NULL) && (traverse->id > traverse->next->id) ){
            return 0;
        }

        traverse = traverse->next;
    }

    return 1;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

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

void printTree(struct treenode *node){
    if (node != NULL){
        printf("Node %d: value: %d, word: %s\n", node -> value, node -> value, node -> word);
        printTree(node -> left);
        printTree(node -> right);
    }
}
//--------------------------------------------------------------------------------------------------//

struct treenode * insert_node(char word[], int value, struct treenode * tree){
    struct treenode *node = malloc(sizeof(struct treenode));
    if(node==NULL){
        printf("**ERROR**: Memory could not cannot be allocated\n");
        exit(0);
    }

    if(tree==NULL){
        strcpy(node->word , word);
        node->value = value;
        node->right = NULL;
        node->left = NULL;

        return node;
    }

    struct treenode *cur_node = tree;
    printf("%s, %d\n", word, value);
    while(1){
        //Go left
        if( ( strcmp(word , cur_node->word) < 1 ) && (cur_node->left != NULL) ){
            if (strcmp(word, "panama") == 0){
                printf("Hello 1\n");
            }
            cur_node = cur_node->left;
            if (strcmp(word, "panama") == 0){
                printf("Hello 1\n");
            }
            continue;
        }

            //Go right
        else if( ( strcmp(word , cur_node->word) > 1 ) && (cur_node->right != NULL) ){
            if (strcmp(word, "panama") == 0){
                printf("Hello 2\n");
            }
            cur_node = cur_node->right;
            if (strcmp(word, "panama") == 0){
                printf("Hello 2\n");
            }
            continue;
        }

        if( ( strcmp(word , cur_node->word) < 1 ) && (cur_node->left == NULL) ){
            if (strcmp(word, "panama") == 0){
                printf("Hello 3\n");
            }
            strcpy(node->word , word);
            node->value = value;
            node->right = NULL;
            node->left = NULL;

            cur_node->left = node;
            if (strcmp(word, "panama") == 0){
                printf("Hello 3\n");
            }
            return node;
        }

        else if( ( strcmp(word , cur_node->word) > 1 ) && (cur_node->right == NULL) ){
            if (strcmp(word, "panama") == 0){
                printf("Hello 4\n");
            }
            strcpy(node->word , word);
            node->value = value;
            node->right = NULL;
            node->left = NULL;

            cur_node->right = node;
            if (strcmp(word, "panama") == 0){
                printf("Hello 4\n");
            }
            return node;
        }

    }

}


int lookup_word(char word[], struct treenode * tree){
    printf("%s\n", word);
    if (strcmp(word, "backwards") == 0){
        printf("We got them boies\n");
    }
    if(tree==NULL){
        return 0;
    }

    struct treenode *cur_node = tree;

    if( strcmp(word, cur_node->word)==0 ){
        return cur_node->value;
    }

    while(1){
        //If next node is NULL
        printf("Word: %s, %d\n", word, strcmp(word , cur_node->word));
        if( strcmp(word , cur_node->word) < 1 && cur_node->left==NULL){
            printf("Hello");
            return 0;
        }

        else if( strcmp(word , cur_node->word) > 1 && cur_node->right==NULL){
            printf("Hello");
            return 0;
        }

        //Going to next node
        if( strcmp(word , cur_node->word) < 1){
            cur_node = cur_node->left;

        }

        else if( strcmp(word , cur_node->word) > 1){
            cur_node = cur_node->right;
        }

        //Checking if they're words are equal
        if( strcmp(word, cur_node->word)==0 ){
            return cur_node->value;
        }
    }

}


void free_tree(struct treenode * tree){
    if(tree==NULL){
        return;
    }

    free_tree(tree->left);
    free_tree(tree->right);

    free(tree);
}





int main(void) {
    //QUESTION #1

    //List #1
    struct slist *lst1 = create_list();
    insert_student(122245222, "Bob", lst1);
    insert_student(123456789, "Amy", lst1);
    insert_student(987654321, "Carlton", lst1);

    //List #2
    struct slist *lst2 = create_list();
    insert_student(110038846, "Salman", lst2);
    insert_student(911212321, "Catherine", lst2);
    insert_student(891735275, "Victor", lst2);
    insert_student(435162322, "Ariel", lst2);
    insert_student(111111453, "Some_random_really_long_name_that_is_randomly_really_long", lst2);
    insert_student(551826456, "Markeseum", lst2);

    //List "out"
    struct slist *out = create_list();

    merge_lists(out, lst1, lst2);
    assert(testing_merged_list(out)==1);



    //List #3
    struct slist *lst3 = create_list();
    insert_student(562938574, "Yo_boi_Marcus", lst3);
    insert_student(213141516, "Yo_boi_Jameelaji", lst3);

    //List #4
    struct slist *lst4 = create_list();
    insert_student(942635443, "Jeremy", lst4);
    insert_student(888888888, "I am Eight", lst4);

    //List #5
    struct slist *lst5 = create_list();
    insert_student(153424564, "Hello World", lst5);
    insert_student(657246561, "Ali_Baba", lst5);
    insert_student(567856245, "Hi", lst5);
    insert_student(456583325, "I_am_the_best_in_the_world", lst5);
    insert_student(457680982, "There's no one like me", lst5);


    //Removing students from list
    assert(remove_student(562938574,lst3)==1);
    assert(remove_student(101010101,lst3)==0); //Doesn't exist in the list
    assert(remove_student(942635443,lst4)==1);
    assert(remove_student(567856245,lst5)==1);

    //Testing my find_student function
    char *name1 = find_student(213141516, lst3);
    assert(strcmp(name1,"Yo_boi_Jameelaji")==0);

    char *name2 = find_student(888888888, lst4);
    assert(strcmp(name2,"I am Eight")==0);

    char *name3 = find_student(1010190122, lst4); //Doesn't exist in the list
    assert(name3==NULL);

    char *name4 = find_student(456583325, lst5);
    assert(strcmp(name4,"I_am_the_best_in_the_world")==0);

    char *name5 = find_student(457680982, lst5);
    assert(strcmp(name5,"There's no one like me")==0);

    //Freeing the lists
    free_list(out);
    free_list(lst3);
    free_list(lst4);
    free_list(lst5);


    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

    //QUESTION #2

    //WORKS ONLY FOR SMALL SENTENCES IDK WHY
    char root_word[10];
    char new_word[10];
    int count = 1;
    int lookup;

    printf("Enter a sentence with spaces and to terminate, input a period: ");
    scanf("%s",root_word); //My first word
    printf(" %s ",root_word);
    struct treenode *root = insert_node(root_word, count, NULL);
    ++count;

    while(1){
        printf("hello\n");
        scanf("%s",new_word);
        printf("Hello\n");
        if( strcmp(new_word,".") == 0 ){
            printf("Hello End\n");
            printf(" . \n\n");
            break;
        }
        printf("Search\n");
        lookup = lookup_word(new_word, root);
        printf("Search222\n");
        if(lookup==0){
            printf(" %s ",new_word);
            insert_node(new_word, count, root);
            printf("We be Cool\n");
            count++;
            printf("We be Cool\n");
        }

        else{
            printf("Words be cool\n");
            printf(" %d ",lookup);
            printf("Words be cool2\n");
        }

        fflush(stdin);
    }
    printTree(root);
    //TESTING lookup_word FUNCTION

    //TEST #1
    struct treenode *root1 = insert_node("the", 1, NULL);
    struct treenode *a = insert_node("boss", 2, root1);
    struct treenode *b = insert_node("of", 3, root1);

    assert(lookup_word("boss",root1)==2);
    free_tree(root1);

    //TEST #2
    struct treenode *root2 = insert_node("a", 1, NULL);
    struct treenode *c = insert_node("monster", 2, root2);
    struct treenode *d = insert_node("and", 3, root2);
    struct treenode *e = insert_node("something", 4, root2);
    struct treenode *f = insert_node("else", 5, root2);

    assert(lookup_word("else",root2)==5);
    free_tree(root2);

    //TEST #3
    struct treenode *root3 = insert_node("wow", 1, NULL);
    struct treenode *g = insert_node("that", 2, root3);
    struct treenode *h = insert_node("is", 3, root3);
    struct treenode *i = insert_node("really", 4, root3);
    struct treenode *j = insert_node("cool", 5, root3);
    struct treenode *k = insert_node("bro", 6, root3);

    assert(lookup_word("invalid",root3)==0);
    free_tree(root3);

    //TEST #4
    struct treenode *root4 = NULL;
    assert(lookup_word("hi",root4)==0);
    free_tree(root4);


    printf("Success!\n");

    return 0;
}