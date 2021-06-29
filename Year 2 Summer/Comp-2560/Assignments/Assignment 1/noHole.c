//
// Created by evanm on 2021-06-11.
//

#include <stdio.h>

int main(){
    char arr[] = {"file.nohole"};
    FILE *fd = fopen(arr, "w");
    for (int i = 0; i < 16394; i++){
        fwrite("a", 1, 1, fd);
    }
    fclose(fd);
}