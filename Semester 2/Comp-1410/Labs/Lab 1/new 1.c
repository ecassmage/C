#include <stdio.h>
void swap_nums(int *x, int *y){
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
void swap_pointers(int *x, int *y){
    printf("%p, %p\n", x, y);
    int *tmp;
    tmp = x;
    x = y;
    y = tmp;
    printf("%p, %p\n", x, y);
}
int main()
{
    int a,b;
    int *s1,*s2;
    a = 3; b=4;
    swap_nums(&a,&b);
    printf("a is %d\n", a);
    printf("b is %d\n", b);
    int *ptr1 = &a;
    int *ptr2 = &b;
    swap_pointers(ptr1, ptr2);
    printf("ptr1 is %p\n", ptr1);
    printf("ptr1 is %p\n", ptr2 - ptr1 + ptr2);
    printf("ptr2 is %p\n", ptr2);
    printf("ptr2 is %p\n", ((ptr1 - ptr2) + ptr2));
    return 0;
}