#include <stdio.h>
#include <string.h>

int main() {
    printf("Hello, World!\n");
    int number = 0;  // Collects the number of semi-unique codes.
    for (int i = 0; i < 256; i++){  // I complete 256 different checks because I feel like I read somewhere that you can only go up to 255 with signal exits.
        printf("%d -> ", i);  // For Visual Effects, easier for counting what number you are on in the prints
        if (strncmp(strsignal(i), "Unknown signal", strlen("Unknown signal")) != 0){  // Basically This catches anything the strsignal determines to be unknown.
            number++;
            printf("Good >> ");  // Just some flavor text
        }
        else printf("Bad >> ");  // Just some flavor text
        printf("Signal Input: %s\n", strsignal(i));  // Just some flavor text
    }
    printf("What is the Number: %d\n", number);  // This outputs the number of different signals at I would say 64
    // But I am not sure if Real-time signal is counted since it just is spammed, so ignore that and we get 32 if we merge all of the Real-time signals together.
    // Saying that though User defined signal is spammed twice, the number could also be 31 if we merge both the User defined signals together.
    // Everything after this is just Unknown Signals so nothing here. You can probably add stuff to this but that isn't what we are doing so.
    return 0;
}


// EMT instruction
// Urgent I/O condition