#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

void sort_bubble(int array[]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE - i; j++){
            if (array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

signed long long int hashSearch(long long int array[][2], long long int n){
    if (array[n][1] == 1){
        return array[n][0];
    }
    else{
        printf("We looked for the value: %lld and found nothing.\n", n);
        return -1;
    }
}

void make_array(int array[], long long int array2[][2]){
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++){
        int temp = rand() % 1000;
        array[i] = temp;
        array2[temp][0] = temp, array2[temp][1] = 1;
    }
}

int binarySearchRecurs(int array[], int first, int last, int key){
    int middle = (first + last) / 2;
    if (first - last > 1 || first - last < -1)
        if (array[middle] == key){
            return array[middle];
        }
    if (array[middle] > key){
        last = middle;
    }
    else{
        first = middle;
    }
    return binarySearchRecurs(array, first, last, key);
}

int buildBinarySearchRecurs(int array[], int size, int term){
    int first = 0;
    int last = size;
    //int middle = (first + last) / 2;
    //int c = 0;
    return binarySearchRecurs(array, first, last, term);
}

void binarySearch2(const int array[], int size, int term){
    int first = 0;
    int last = size;
    int middle = (first + last) / 2;
    int c = 0;
    while (first - last > 1 || first - last < -1){
        c++;
        if (array[middle] > term){
            last = middle;
        }
        else{
            first = middle;
        }
        middle = (first + last) / 2;
    }
    printf("\n%d, %d: %d\n", term, array[middle], c);
}

void binarySearch(const int array[], int size, int term){
    int first = 0;
    int last = size;
    int middle = (first + last) / 2;
    int c = 0;
    while (c < size){
        c++;
        if (array[middle] > term){
            last = middle;
        }
        else if (array[middle] < term){
            first = middle;
        }
        else{
            break;
        }
        middle = (first + last) / 2;
    }
    printf("\n%d, %d: %d\n", term, array[middle], c);
}

int main(){
    int array[SIZE];
    long long int array2[100000][2];
    for (int i = 0; i<100000; i++){
        for (int j = 0; j < 2; j++){
            printf("%lld ", array2[i][j]);
        }
        printf("\n");
    }
    make_array(array, array2);
    sort_bubble(array);
    int numArrElements = sizeof(array) / sizeof(array[0]);
    double start = clock();
    binarySearch(array, numArrElements, 67);
    printf("Time: %f\n", (clock()/start));
    binarySearch2(array, numArrElements, 67);
    printf("Time: %f\n", (clock()/start));
    printf("%d\n", buildBinarySearchRecurs(array, numArrElements, 72));
    long long int val = hashSearch(array2, 55);
    printf("val: %lld\n", val);
    return 0;
}
