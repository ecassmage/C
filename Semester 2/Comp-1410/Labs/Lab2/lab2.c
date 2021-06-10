/* ===========================================================================
COMP-1410 Lab 2
==============================================================================
Student name: Evan Morrison

Cite any other sources of outside help
(e.g., websites, other students):
 Looked up on stackoverflow how to print a bool variable as true or false
 didn't want to print out 1 or 0

=========================================================================== */
                                                                            /*
 * Tested with repl.it, onlinegdb and cygwin terminal with - C version - C99
*/



#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// order(a, b) orders the values pointed to by a and b so that *a <= *b;
//   returns true if the values were switched and false otherwise
// requires: a and b point to memory that can be modified
bool order(int * a, int * b);

// swap_pointers(a, b) [ does something with a and b ]
// requires: [ requirements on a and b ]
void swap_pointers(int **a, int **b);


void check_asserts_order(int a, int b, bool x){
    assert(order(&a, &b) == x);
}

void check_asserts_swap(int *a, int *b){
    int *x = a, *y = b;
    printf("Before: %p points to: %d, %p points to: %d\n", a, *a, b, *b);
    swap_pointers(&a, &b);
    printf("After: %p points to: %d, %p points to: %d\n", a, *a, b, *b);
    assert(a == y && b == x);
}

void holding_the_asserts(){
    int a = 10, b = 7;
    bool c = true;
    printf("currently asserting a = %d, b = %d with a bool of ", a, b);
    printf("%s\n", c ? "true" : "false"); // Looked up how to do this
    check_asserts_order(a, b, c); // 10 > 7 so flipped and therefore true
    a = 7, b = 11;
    c = false;
    printf("currently asserting a = %d, b = %d with a bool of ", a, b);
    printf("%s\n", c ? "true" : "false"); // Looked up how to do this
    check_asserts_order(a, b, c); // 7 > 11 so no flipped and therefore false
    printf("All order asserts are completed\n\n\n");
    int x = 7, y = 10; // first the values are given then are given pointers
    int *ptr1 = &x, *ptr2 = &y; // not quite that pointy
    check_asserts_swap(ptr1, ptr2);
    x = 11, y = 7;
    ptr1 = &x, ptr2 = &y; // least pointy of them all
    check_asserts_swap(ptr1, ptr2);
    printf("All swap asserts are completed\n\n\n");
}

int main(void) {
    // Perform your tests here
    holding_the_asserts();
    printf("\n\nAll the Asserts have succeeded\n\n");
    printf("This is some other stuff that I did\n");
    int a = 23, b = 10;
    printf("For a = %d and b = %d: ", a, b);
    if (order(&a, &b) == 1)
        printf("We received a true\n");
    else
        printf("We received a false\n");
    printf("New order we get a = %d, b = %d\n", a, b);
    a = 7, b = 10;
    printf("For a = %d and b = %d: ", a, b);
    if (order(&a, &b) == 1)
        printf("We received a true\n");
    else
        printf("We received a false\n");
    printf("New order we get a = %d, b = %d\n", a, b);
    int *pointerPower_1 = &a, *pointerPower_2 = &b; // Very pointy
    printf("\nBefore the Swap: \nThis is 'a' memory: %p, This is 'b' memory: %p\n", pointerPower_1, pointerPower_2);
    swap_pointers(&pointerPower_1, &pointerPower_2); // Very pointy as well
    printf("After the Swap: \nThis is 'a' memory: %p, This is 'b' memory: %p\n", pointerPower_1, pointerPower_2);
    printf("This is a: %d, This is b: %d\n", a, b);
    printf("All tests passed successfully.\n");
}

bool order(int *a, int *b){
    if (*a <= *b){
        return false;
    }
    else{
        int temp = *a;
        *a = *b;
        *b = temp;
        return true;
    }
}

void swap_pointers(int **a, int **b){
    int *temp = *a;
    *a = *b;
    *b = temp;
}
