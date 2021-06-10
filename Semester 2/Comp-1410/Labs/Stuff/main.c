#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define arraySize 7
int main() {
    int arr[arraySize ] = {0};
    int skip = 0;
    srand(time(NULL));
    for (int j = 0; j < arraySize;){
        skip = 0;
        int r = (rand() % 9) + 1;
        for (int i = 0; i < arraySize; i++){
            if (arr[i] == r){
                skip = 1;
                break;
            }
        }
        if (skip == 0){
            arr[j] = r;
            j++;
        }
    }
    for (int j = 0; j < arraySize; j++){
        printf("%d, ", arr[j]);
    }
}
