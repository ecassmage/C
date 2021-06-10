#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 10 // I don't know how to assign Dynamic Memory so this is the best I got
#define COLUMN 10 // I don't know how to assign Dynamic Memory so this is the best I got
//Excessivesion is my name
void row_sums(int r, int c, int matrix[][COLUMN] , int additionArr[ROW]);
void buildMatrices(int Matrix[][COLUMN], int r, int c);
void circuitBoard();
void my_stuff();


int main() {
    srand(time(NULL));
    for (int _ = 0; _ < 100; _++){
        circuitBoard();
    }
    my_stuff();
    printf("Completion has been met");
    return 0;
}

void printArr(int array[], int size){
    for (int i = 0; i < size - 1; i++){
        printf("%d, ", array[i]);
    }
    printf("%d\n", array[size - 1]);
}

void row_sums(int r, int c, int matrix[][COLUMN] , int additionArr[ROW]){
    // ▲ Yes I know I changed stuff but this way looks better and is easier to work with
    // I also didn't really change stuff per say just renamed some stuff to better suit myself
    for (int i = 0; i < r; i++){
        int x = 0;
        for (int j = 0; j < c; j++){
            x += matrix[i][j];
        }

        additionArr[i] = x;
    }
}

void buildMatrices(int Matrix[][COLUMN], int r, int c){ // Builds matrices for me for more.
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            Matrix[i][j] = rand() % 100;
        }
    }
}

void circuitBoard(){ // Holds precious mechanics for cleanliness
    int row = rand() % 10;
    int column = rand() % 10;
    int Matrix[ROW][COLUMN] = {0};
    buildMatrices(Matrix, row, column);
    int mathArr[ROW] = {0};
    row_sums(row, column, Matrix, mathArr);
    printf("Random Matrix: ");
    printArr(mathArr, row);
}

void my_stuff(){
    int arr1[10][10] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    int mathArr[ROW] = {0};
    row_sums(3, 3, arr1, mathArr);
    printf("Actual Made Matrix: ");
    printArr(mathArr, 3);
}

/*
 * This is meant to to math to get answers. I don't Know how I am supposed to explain anything in depth here
 * First I build matrix then I add the rows nums then I print Repeat.
 */