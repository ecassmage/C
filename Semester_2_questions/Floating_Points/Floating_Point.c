#include<stdio.h>


int main(){
    float floating_point[1000];
    int size = 0;
    while (size <= 2 || size >= 1000){
        printf("Enter Wanted amount of nums: ");
        scanf("%d", &size);
        if (size <= 2 || size >= 1000)
            printf("%d is not within bounds(bounds are anything > 2)\n", size);
    }
    for (int i = 0; i < size; i++){
        printf("Number %d: ", i + 1);
        scanf("%f", &floating_point[i]);
    }
    for (int i = 0; i < size; i++){
        printf("%f\n", floating_point[i]);
    }
    float max = floating_point[0], max2 = floating_point[0], min = floating_point[0], min2 = floating_point[0], average = floating_point[0];
    for (int i = 1; i < size; i++){
        float float_check = floating_point[i];
        average += float_check;
        if (float_check <= min){
            min2 = min;
            min = float_check;
        }
        else if (float_check <= min2){
            min2 = float_check;
        }
        else if (float_check >= max){
            max2 = max;
            max = float_check;
        }
        else if (float_check >= max2){
            max2 = float_check;
        }
    }
    average -= (max2 + min2);
    average /= (size - 2);
    printf("Max: %.1f, Max2: %.1f, Min: %.1f, Min2: %.1f\nAverage: %.3f", max, max2, min, min2, average);
}