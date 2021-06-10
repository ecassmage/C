#include <stdio.h>
#include <stdlib.h>
// ▼ Needed to access time
#include <time.h>
#include <assert.h>
#define PerceivedMaxStupid 10000

void print(int x){
    printf("This is valued at: %d, So behave yourself.\n", x);
}

void cleanArray(int x, int arr[], int n){ // Clean array in digits
    int removeX = x % 10;
    arr[n] = (int) removeX;
    if (removeX == 9)
        return;
    x = (x - removeX) / 10;
    if (x >= 10) {
        cleanArray(x, arr, n + 1); // Recursion Is here
    }
    else{
        arr[n + 1] = (int) x; // Almost had a catastrophe where this ignore the first digit so this was added.
    }
}

int max_digit(int x){ // Finds the largest digit in the number
    int arr[20] = {0};
    cleanArray(x, arr, 0);
    int largestBeastNumber = 0;
    for (int i = 0; i < 10; i++){
        if (arr[i] == 9)//straight returns 9 since 9 is biggest absolute
            return arr[i];
        else if (arr[i] > largestBeastNumber){
            largestBeastNumber = arr[i];
        }
    }
    return largestBeastNumber;
}

int generateStupidity(int *x){
    srand(time(NULL)); // Seeds the randomizer to your machine time or something
    int numOfRandomNumbers = rand() % 999999999; // My stupid generator, Generates stupids like me
    *x = max_digit(numOfRandomNumbers);
    return numOfRandomNumbers;
}

void asserts(){
    assert(max_digit(123456789) == 9);
    assert(max_digit(34345345) == 5);
    assert(max_digit(145678976) == 9);
    assert(max_digit(0) == 0);
    assert(max_digit(112233) == 3);
    assert(max_digit(6543) == 6);
    assert(max_digit(76575410) == 7);
    assert(max_digit(878687652) == 8);
}

int main() {
    int whateverYouWant = 34533942;
    for (int jokes = 0; jokes < PerceivedMaxStupid; jokes++){
        int x;
        int tempo = generateStupidity(&x);
        assert(max_digit(tempo) == x);
    }
    asserts();
    int longBoy = max_digit(whateverYouWant);
    print(longBoy);
    printf("If you are reading this then I have failed to crash this program.\n");
}
