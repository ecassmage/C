#include <stdio.h>
#include <stdbool.h>

void print(int array[], int length){
    for (int i = 0; i < length-1; i++){
        printf("%d, ", array[i]);
    }
    printf("%d\n", array[length-1]);
}

void Q3(){
    int A[20] = {4, 5, 14, 4, 6, 7, 8, 10, 9, 3, 6};
    int c = 0, k = 3;
    int longest = 0, longestI = 0;
    int i;
    for (i = 0; i < 20; i++){
        if (A[i] == 0){
            if (c > longest){
                longestI = i;
                longest = c;
            }
            c = 0;
        }
        if (A[i] % k == 0){
            c++;
        }
        else{
            if (c > longest){
                longestI = i;
                longest = c;
            }
            c = 0;
        }
    }
    if (c > longest){
                longestI = i;
                longest = c;
            }
    printf("The Answer to Q3 is: (");
    for (i = longestI - longest; i < longestI - 1; i++){
        printf("%d, ", A[i]);
    }
    printf("%d)", A[longestI - 1]);
    printf("\n\n\n");
}


bool inArray(int searchTerm, const int array[], int size){
    for (int a = 0; a < size; a++){
        if (array[a] == searchTerm){
            return true;
        }
    }
    return false;
}

int indexArray(int searchTerm, const int array[], int size){
    for (int a = 0; a < size; a++){
        if (array[a] == searchTerm){
            return a;
        }
    }
    printf("Index not Found for: %d\n", searchTerm);
    return -1;
}

void makeArray(int arr[], int x, int y){
    int next = (x % 10);
    x -= next;
    x /= 10;
    arr[y] = next;
    if (x >= 10)
        makeArray(arr, x, y + 1);
    else{
        arr[y + 1] = x;
    }
}

int digitSum(const int x[], int y){
    int z = 0;
    for (int i = 0; i < y; i++){
        z += x[i];
    }
    if (z >= 10){
        int arr[20] = {0};
        makeArray(arr, z, 0);
        return digitSum(arr, 20);
    }
    //printf("\n%d\n\n", z);
    return z;
}

void Q2(int array[][3], int row, int col){
    int unique[20][2] = {0, 0}, notUnique[20] = {0};
    int c = 0;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (inArray(array[i][j], notUnique, 20) == 0){
                notUnique[c] = array[i][j];
                unique[c][0] = array[i][j];
                unique[c][1]++;
                c++;
            }
            else {
                int index = indexArray(array[i][j], notUnique, 20);
                if (index != -1)
                unique[index][1]++;
            }
        }
    }
    int finalizedArray[20] = {0};
    int x = 0;
    printf("The answer to Q2 is: digitSum(");
    for (int i = 0; i < c; i++){
        if ( unique[i][1] == 1 ){
            if (i < c - 1)
                printf("%d, ", unique[i][0]);
            finalizedArray[x++] = unique[i][0];
        }
    }
    printf("%d", unique[c - 1][0]);
    printf(") = ");
    int answer = digitSum(finalizedArray, c);
    printf("%d\n", answer);
    printf("\n\n\n");
}

void Q1(int arr[], int y){
    int arr2[20] = {0};
    for (int i = y-1; i >= 0; i--){
        arr2[y-i - 1] = arr[i];
    }
    for (int i = 0; i < y; i++){
        arr[i] = arr2[i];
    }
}

void arrayTranspose(){
    int array1[3][2] = {
        {1, 2},
        {3, 4},
        {5, 6}
        };
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++){
            printf("%d ", array1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int array2[2][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++){
            array2[j][i] = array1[i][j];
        }
    }
     for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3; j++){
            printf("%d ", array2[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}


int main(){

    // {8, 9, 7, 10, 2}
    // I could do a sort of hash map for this as well
    int array[20][3] = {
        {3, 8, 9},
        {1, 3, 7},
        {10, 1, 2}
    };
    int array2[20][3] = {
        {2, 5},
        {1, 1},
        {17, 2}
    };
    int arr1[5] = {2, 5, 9, 7, 1};
    Q3();
    Q2(array, 20, 3);
    Q2(array2, 20, 2);
    print(arr1, 5);
    Q1(arr1, 5);
    print(arr1, 5);
    printf("\n");
    arrayTranspose();
}