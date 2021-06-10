/* ===========================================================================
COMP -1410 Lab 8
==============================================================================
Student name: Evan Morrison
Replace the error with a statement citing any sources of outside help:
None
=========================================================================== */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
// I put lines beside function definitions for easier traversal.
typedef struct node {
    int item;
    struct node *left;
    struct node *right;
} node;

// create_node(item , left , right) creates and returns a tree node containing
// given item and left/right pointers; caller must free allocated memory
// requires: left , right are NULL or point to tree nodes
// note: returns NULL if memory cannot be allocated

void error(node *node){
    if(node == NULL){
        printf("ERROR: Out of memory\n");
        exit(01134);
    }
}
/// Assertions are lines 57-149
node *createTree(int item);
node *create_node(int item, node *left, node *right);  /// lines 209-217 
bool sortNode(node *tree, node *Node, int num);
void attachNode(node *tree, int item, int num);
void sideThingThatIDid();
void printLevels(node *tree);
// free_tree(node) frees the memory associated with the given node and
// all of the node's children
// requires: root is the root of a tree allocated dynamically
void free_tree(node *root);  /// lines 242-251
// height(root) returns the height of the tree with given root
// requires: root is NULL or points to a tree node
int height(node *root);  /// lines 219-229
// num_leaves(root) returns the number of leaf nodes in the tree with
// given root
// requires: root is NULL or points to a tree node
int num_leaves(node *root);  /// lines 231-240

void assertNode(node *testNode, int num, node *left, node *right){
    assert(testNode -> item == num);
    assert(testNode -> left == left);
    assert(testNode -> right == right);
}

void asserting(){
    node *node20 = create_node(20, NULL, NULL);
    node *node12 = create_node(12, NULL, NULL);
    node *node14 = create_node(14, NULL, NULL);
    node *node13 = create_node(13, node12, node14);
    node *node16 = create_node(16, NULL, NULL);
    node *node17 = create_node(17, node16, NULL);
    node *node19 = create_node(19, NULL, node20);
    node *node18 = create_node(18, node17, node19);
    node *node15 = create_node(15, node13, node18);
    node *node5 = create_node(5, NULL, NULL);
    node *node8 = create_node(8, NULL, NULL);
    node *node7 = create_node(7, NULL, node8);
    node *node6 = create_node(6, node5, node7);
    node *node1 = create_node(1, NULL, NULL);
    node *node3 = create_node(3, NULL, NULL);
    node *node2 = create_node(2, node1, node3);
    node *node4 = create_node(4, node2, node6);
    node *node9 = create_node(9, node4, NULL);
    node *node11 = create_node(11, NULL, node15);
    node *root = create_node(10, node9, node11);

    assertNode(node20, 20, NULL, NULL);
    assertNode(node12, 12, NULL, NULL);
    assertNode(node14, 14, NULL, NULL);
    assertNode(node13, 13, node12, node14);
    assertNode(node16, 16, NULL, NULL);
    assertNode(node17, 17, node16, NULL);
    assertNode(node19, 19, NULL, node20);
    assertNode(node18, 18, node17, node19);
    assertNode(node15, 15, node13, node18);
    assertNode(node5, 5, NULL, NULL);
    assertNode(node8, 8, NULL, NULL);
    assertNode(node7, 7, NULL, node8);
    assertNode(node6, 6, node5, node7);
    assertNode(node1, 1, NULL, NULL);
    assertNode(node3, 3, NULL, NULL);
    assertNode(node2, 2, node1, node3);
    assertNode(node4, 4, node2, node6);
    assertNode(node9, 9, node4, NULL);
    assertNode(node11, 11, NULL, node15);
    assertNode(root, 10, node9, node11);

    // which could have been condensed to
    int arr[19] = {9, 11, 4, 15, 13, 18, 12, 14, 17, 19, 16, 20, 2, 1, 3, 6, 5, 7, 8};
    node *root2 = create_node(10, NULL, NULL);
    for (int i = 0; i < 19; i++){
        attachNode(root2, arr[i], 0);
    }
    // And while there are other things in the background written, this can handle any number of elements where as
    // the thing asked can only handle how ever many the human is willing to write before his hands fall off.
    // as you can probably tell I am annoyed by the limitations.
    assert(height(root) == 6);
    assert(num_leaves(root) == 8);
    assert(height(root2) == 6);
    assert(num_leaves(root2) == 8);

    printLevels(root);
    free_tree(root);
    free_tree(root2);
    root = create_node(10, NULL, NULL);

    assertNode(root, 10, NULL, NULL);

    assert(height(root) == 1);
    assert(num_leaves(root) == 1);
    free_tree(root);
    root = NULL;
    assert(root == NULL);
    assert(num_leaves(root) == 0);
    assert(num_leaves(root) == 0);
    free_tree(root);
    node *tree1 = create_node(1, NULL, NULL);
    node *tree3 = create_node(3, NULL, NULL);
    node *tree5 = create_node(5, NULL, NULL);
    node *tree7 = create_node(7, NULL, NULL);
    node *tree2 = create_node(2, tree1, tree3);
    node *tree6 = create_node(6, tree5, tree7);
    node *tree = create_node(4, tree2, tree6);

    assertNode(tree1, 1, NULL, NULL);
    assertNode(tree3, 3, NULL, NULL);
    assertNode(tree5, 5, NULL, NULL);
    assertNode(tree7, 7, NULL, NULL);
    assertNode(tree2, 2, tree1, tree3);
    assertNode(tree6, 6, tree5, tree7);
    assertNode(tree, 4, tree2, tree6);

    assert(height(tree) == 3);
    assert(num_leaves(tree) == 4);
    printLevels(tree);
    free_tree(tree);
}

int main(void){
    // Implement your test code here
    // This randomized tree making thingy is unstable don't make the nested for loops generate too large of trees.
    // can crash easily if too big. as the recursion to build the tree and levels is very memory intensive. 500 seems
    // to be the limit of this variable before issues begin to occur frequently.
    srand(time(NULL));
    for (int j = 0; j < 1; j++) {
        node *tree = createTree(5000);
        for (int i = 0; i < 100; i++) {
            attachNode(tree, rand() % 10000, 0);
        }
        //printf("height: %d, leaves: %d\n", height(tree), num_leaves(tree));
        printLevels(tree);
        free_tree(tree);
    }// Obviously this can't be asserted since it is impossible to predict as I do not know when you will run this
    // and there fore can't write assertions for this.
    asserting(); /// Deals with asserting.
    printf("All tests passed successfully.\n");
    printf("Now for other stuff that has nothing to do with this assignment:\n");
    sideThingThatIDid();
}

node *createTree(int item){
    /// Creates the root Node
    node *nodeTree = (node*) calloc(1, sizeof(node));
    error(nodeTree);
    nodeTree -> item = item;
    return nodeTree;
}

bool sortNode(node *tree, node *Node, int num){
    if (Node -> item < tree -> item){
        if (tree -> left == NULL) {
            tree -> left = Node;
            return true;
        }
        return sortNode(tree -> left, Node, num);
    }
    else if (tree -> item < Node -> item){
        if (tree -> right == NULL) {
            tree -> right = Node;
            return true;
        }
        return sortNode(tree -> right, Node, num);
    }
    else{
        if (num == 1) printf("The number entered is a duplicate, please enter a different number.\n");
        return false;
    }
}

void attachNode(node *tree, int item, int num){
    node *nodeOfLife = create_node(item, NULL, NULL);
    if (sortNode(tree, nodeOfLife, num) == 0){
        free(nodeOfLife);
    }
}

node *create_node(int item, node *left, node *right){
    /// This is confusing me, why do we need to do this, it seems dumb.
    node *nodeTree = (node*) calloc(1, sizeof(node));
    error(nodeTree);
    nodeTree -> item = item;
    nodeTree -> left = left;
    nodeTree -> right = right;
    return nodeTree;
}

int height(node *root){
    if (root == NULL){
        return 0;
    }
    if (root -> left == NULL && root -> right == NULL) return 1;
    int left = 0, right = 0;
    if (root -> left != NULL)  left = 1 + height(root -> left);
    if (root -> right != NULL) right = 1 + height(root -> right);
    if (left < right) return right;
    return left;
}

int num_leaves(node *root){
    if (root == NULL){
        return 0;
    }
    if (root -> left == NULL && root -> right == NULL) return 1;
    int left = 0, right = 0;
    if (root -> left != NULL)  left = num_leaves(root -> left);
    if (root -> right != NULL) right = num_leaves(root -> right);
    return left + right;
}

void free_tree(node *root){
    if (root == NULL) return;
    if (root -> left == NULL && root -> right == NULL) {
        free(root);
        return;
    }
    if (root -> left != NULL)  free_tree(root -> left);
    if (root -> right != NULL) free_tree(root -> right);
    free(root);
}

void sideThingThatIDid(){
    // No reason why just felt like making this.
    char x[3] = {'\0'};
    int num = 0;
    node *tree = (node*) calloc(1, sizeof(node));
    error(tree);
    printf("Just skip this if you want completely irrelevant, just press x\n");
    while (strcmp(x, "x") != 0) {
        memset(x, 0, 3);
        printf("Please enter a number greater then 0, or enter x to finish the tree: ");
        if (scanf("%d", &num)){
            if (tree -> item == 0){
                tree -> item = num;
            }
            else {
                attachNode(tree, num, 1);
            }
        }
        else {
            scanf("%3[^\n]s", x);
            if ((strcmp(x, "x") != 0)){
                printf("Sorry what ever you printed is not accepted.\n");
                fflush(stdin);
            }
            else if (tree -> item == 0){
                tree = NULL;
            }
        }
    }
    printf("The height of this tree is: %d,\nThe number of leaves on this tree is: %d\n", height(tree), num_leaves(tree));
    if (height(tree) > 0) printLevels(tree);
    else printf("Leaves: [len: 0] -> []\n");
}

typedef struct intSpecial{
    // Was made for something else, which was scrapped. Not changing since its a side project of mine and not
    // lab.
    int num;
} intSpecial;

typedef struct level{
    intSpecial *num;
    int lenC; // 0
    int lenT; // 10
} level;
typedef struct specialIntArr{
    level *num;
    int len; // 1
} specialIntArr;

void newLevel(specialIntArr *arr){
    arr -> num = (level*) realloc(arr -> num, ((arr -> len) + 1) * sizeof(level));
    if (arr -> num == NULL){
        printf("ERROR: Out of memory\n");
        exit(123456789);
    }
    arr -> num[arr -> len].num = (intSpecial*) calloc(10, sizeof(intSpecial));
    if (arr -> num[arr -> len].num == NULL){
        printf("ERROR: Out of memory\n");
        exit(123456788);
    }
    arr -> num[arr -> len].lenT = 10;
    arr -> num[arr -> len].lenC = 0;
    (arr -> len)++;
    //return arr -> num;
}

void printArr(specialIntArr *arr){
    for (int i = 1; i < arr -> len; i++){
        printf("Level %d: [len: %d] -> [", i, arr -> num[i].lenC);
        //printf("%d\n", arr -> num[i].lenC);
        for (int j = 0; j < arr -> num[i].lenC - 1; j++){
            printf("%d, ", arr -> num[i].num[j].num);
        }
        printf("%d]\n", arr -> num[i].num[arr -> num[i].lenC - 1].num);
    }
    printf("Leaves: [len: %d] -> [", arr -> num[0].lenC);
    for (int j = 0; j < arr -> num[0].lenC - 1; j++){
        printf("%d, ", arr -> num[0].num[j].num);
    }
    printf("%d]\n", arr -> num[0].num[arr -> num[0].lenC - 1].num);
}

void addTab(int level, const bool *arr){
    for (int i = 1; i <= level; i++){
        if (arr[i] == true) printf("║   ");
        else printf("    ");
    }
}

void printingLevels(node *tree, specialIntArr *arr, int level, bool *x, int yes){
    if (level < 0 || level > 100 || yes > 1){
        // Umm Idk what is the problem with this but level and yes keep exceeding their limits in this function
        // but having this little check fixes it for some reason. The only thing I can think of is that it is
        // slowing down here and realizing that hey level can't get be -214282342 now can it considering it could only
        // go up to maybe 2000000 at most which so unless passing too many values, this should be fine.
        printf("%d", level);
    }
    if (tree == NULL) return;
    if (arr -> len <= level){
        //arr = (specialIntArr*) realloc(arr);
        // arr -> num = newLevel(arr); // makes a new level
        newLevel(arr);
    }
    addTab(level-2, x);
    if (level != 1) {
        if (x[level-1] == true){
            printf("╠══ ");
        }
        else{
            printf("╚══ ");
        }
    }
    printf("%d\n", tree -> item);

    if (tree->left != NULL){
        if (tree->right != NULL){
            x[level] = true;
        }
        printingLevels(tree->left, arr, level + 1, x, 1);
        x[level] = false;
    }
    if (tree->right != NULL){
        printingLevels(tree->right, arr, level + 1, x, 0);
    }
    if (yes == 1 && tree -> left != NULL && tree -> right != NULL){
        addTab(level - 1, x);
        printf("\n");
    }
    if (tree -> left == NULL && tree -> right == NULL){
        if (arr -> num[0].lenC == arr -> num[0].lenT){
            arr -> num[0].num = (intSpecial*) realloc(arr -> num[0].num, ((arr -> len) * 10) * sizeof(intSpecial));
            if (arr -> num[0].num == NULL){
                printf("ERROR: Out of memory\n");
                exit(123456788);
            }
            arr -> num[0].lenT *= 10;
        }
        arr -> num[0].num[arr -> num[0].lenC].num = tree -> item;
        (arr -> num[0].lenC)++;
    }
    if (arr -> num[level].lenC == arr -> num[level].lenT){
        arr -> num[level].num = (intSpecial*) realloc(arr -> num[level].num, ((arr -> len) * 10) * sizeof(intSpecial));
        if (arr -> num[level].num == NULL){
            printf("ERROR: Out of memory\n");
            exit(1);
        }
        arr -> num[level].lenT *= 10;
    }
    arr -> num[level].num[arr -> num[level].lenC].num = tree -> item;
    (arr -> num[level].lenC)++;
    //printArr(arr);
}

void printLevels(node *tree){
    specialIntArr *arr = (specialIntArr*) calloc(1, sizeof(specialIntArr));
    if (arr == NULL){
        printf("ERROR: Out of memory\n");
        exit(123456799);
    }
    arr -> num = (level*) calloc(1, sizeof(level));
    if (arr -> num == NULL){
        printf("ERROR: Out of memory\n");
        exit(123456789);
    }
    arr -> num[0].num = (intSpecial*) calloc(10, sizeof(intSpecial));
    if (arr -> num[0].num == NULL){
        printf("ERROR: Out of memory\n");
        exit(123456788);
    }
    arr -> num -> lenT = 10;
    arr -> len = 1;
    bool *mallocTemp = (bool*) calloc(height(tree)+1, sizeof(bool));
    if (mallocTemp == NULL){
        printf("ERROR: Out of memory\n");
        exit(12345655);
    }
    printingLevels(tree, arr, 1, mallocTemp, 1);
    printArr(arr);
    printf("\nThe height of this tree is: %d,\nThe number of leaves on this tree is: %d\n\n", height(tree), num_leaves(tree));
    free(mallocTemp);
    for (int i = 0; i < arr -> len; i++){
        free(arr -> num[i].num);
    }
    free(arr -> num);
    free(arr);
}


/*

         6
        / \
       4   N
     /   \
    3     5
   / \   / \
  2   N N   N
 / \
1   N

     1
   /   \
  1     1
 / \   / \
1  10 1   1
*/
