//
// Created by evanm on 2021-07-21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define numberOfRandoms 5  // Number each child needs to get for the parent
#define numberOfChildren 2  // Number of Children.
//#define Parent getpid()  // Interesting, This saves its own pid whether parent or child.
pid_t FirstAncestor;  // The First Ancestor

typedef struct{
    int seed;
    int randomSeed;
    unsigned long long current;
    unsigned long long previous;
    int iteration;
} Random;

int getRandSeed(Random *rand, int lowerBound, int upperBound, int boolean){
    // Why Dunno But it does produce half decent pseudo random numbers.
    if (boolean && rand -> randomSeed == 0) rand -> randomSeed = getRandSeed(rand, 1, 1000, 0);
    unsigned long long num = rand -> current;
    rand -> previous = rand -> current;
    num++;
    num += (rand -> current * 3) / rand -> previous;
    num *= (1 + rand -> current);
    num%rand->seed==0 && rand->previous%rand->seed==0 ? rand->seed++:num++;
    num += rand -> iteration % rand -> seed;
    if (boolean == 1 && num % (rand -> randomSeed % rand -> seed) == 0) num += rand->randomSeed;
    rand->previous = rand->current;
    rand->current = num;
    rand->iteration++;
    return (int) (rand -> current % (upperBound - lowerBound)) + lowerBound;
}

int getRandom(Random *rand, int lowerBound, int upperBound){
    // Why Dunno But it does produce half decent pseudo random numbers.
    return getRandSeed(rand, lowerBound, upperBound, 1);
}

Random *mkRandom(int seed){
    Random *rand = malloc(sizeof(Random));
    if (seed == 0) seed = (int) time(NULL);
    rand -> seed = seed;
    rand -> current = seed;
    rand -> previous = seed * 2 + 1;
    rand -> iteration = 1;
    rand -> randomSeed = 0;
    return rand;
}

void dummyFunction(){
    /// I do not know how to do it any other way so these dummy functions seem to be necessary for the moment.
}

void childTasks(int pipe[]){
    Random *rand = mkRandom(getpid());  // This is a randomizing structure.  takes its own pid as the seed.
    for (int i = 0; i < numberOfRandoms; i++){  // loop for number of random numbers needed.
        pause();  // Pauses the child waiting for parent to say it is good to go.
        int numTemp = getRandom(rand, 0, 100);  //  Gets a random number.
        write(pipe[1], &numTemp, sizeof(numTemp));  // writes to the pipe the number chosen.
        kill(FirstAncestor, 34);  // tells the parent that it has completed its task and that the parent can now read from the pipe.
    }
    exit(0);
}

int main() {
    int PipesForCoolStuff[2];  // This is the Pipe
    FirstAncestor = getpid();  // This saves the parent for all children. So that the children knows who the parent is.
    pid_t child[numberOfChildren];  // Will only be complete array if the Parent is Accessing this
    signal(34, dummyFunction);  // This is the go ahead signal being stored as a runtime signal
    if (pipe(PipesForCoolStuff) < 0)    exit(0);  // exits if the pipe failed or something.
    for (int i = 0; i < numberOfChildren; i++){  // loop to create the children.
        if (FirstAncestor == getpid()) child[i] = fork();  // creates the new child  // probably pointless to guard this with the if but meh.
        if (FirstAncestor != getpid()) childTasks(PipesForCoolStuff);  // sends the children on their way
    }
    sleep(1); // To give the children time to get in place.

    for (int i = 0; i < numberOfRandoms; i++){  // for number of random numbers.
        for (int j = 0; j < numberOfChildren; j++){ // for number of children.
            kill(child[j], 34);  // Tells the next child to go ahead
            pause();  // waits for child to write something to the pipe
            int num;  // creates an integer variable to collect from the pipe.
            read(PipesForCoolStuff[0], &num, sizeof(num));  // Reads from the pipe.
            printf("Child %d has returned the Number: %d\n", child[j], num);  //writes a quick message saying who was writing to the pipe.
        }
    }

    //
    // Reading the question again, it doesn't say that I am supposed to print the number right away so it could be asking for them to be all printed at the end. if so all that needs to happen is to
    // comment out int num;, read(PipesForCoolStuff[0], &num, sizeof(num)); and printf("Child %d has returned the Number: %d\n", child[j], num);
    //
    //      then add the next few lines. just above these comments here
    /*
      for (int i = 0; i < numberOfRandoms * numberOfChildren; i++){
          int num;
          read(PipesForCoolStuff[0], &num, sizeof(num));
          printf("The Number Returned is: %d\n", num);
      }
    */

    close(PipesForCoolStuff[1]);  // Closes the writing end of the pipe
    close(PipesForCoolStuff[0]);  // Closes the reading end of the pipe.
}