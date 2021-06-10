#include<stdio.h>


int main(){
    int rows = 0, columns = 1;
    while (rows < 2 || rows > 10){
        printf("Enter number of rows wanted: ");
        scanf("%d", &rows);
        if (rows < 2 or rows > 10)
            printf("%d is out of bounds (bounds are 2-10)\n", rows);
    }
    for (int i = 1; i <= rows; i++){
        printf("* ");
        if (i == columns && i != rows){
            i = 0;
            columns += 1;
            printf("\n");
            continue;
        }
    }
}
