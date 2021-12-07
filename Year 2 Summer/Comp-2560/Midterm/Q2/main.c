#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * Name: Evan Morrison
 * Student ID: 110043572
 * I make the program Calculate My Student ID VIA Line
 *
 */

void doWhatAChildDoesAndNotListenToItsParents(){
    printf("My Boring Parent: %d, My Cool Self: %d\n", getppid(), getpid());  // Prints Line of Stuff.
    exit(101);  // Exit status 101.
}
void doWhatAChildDoesAndNotListenToItsParentsDoWhatAChildDoesAndNotListenToItsParents(int statisimo){  // Double The Trouble
    printf("My Boring Parent: %d, My Cool Self: %d... Oh and My childs' Exit Status is: %d\n", getppid(), getpid(), statisimo);  // Prints Line of Stuff.
    exit(1);  // To make sure this is not being mistaken somehow for the other function.
}


int main() {
    char *IDUNNO = {"110043572"};  // This is my Student id as well. In String format to make summing it up easier. Thinking on it now though I could have just used an int array, but That also would have been a pain to write having to add commas everywhere.
    int i = 0;  // A lonely i in the Wilderness.
    for (int j = 0; IDUNNO[j] != '\0'; j++, i+= (int) (IDUNNO[i] - 48));  // <- This Calculates what my student id sum is
    i = i % 3;  // <- This Calculates what the remainder of the sum of my student id is
    pid_t Parent = getpid();  // This stores the Top Level Parent
    pid_t ChildrenSpecial;  // This stores the special child because it takes the longest to complete.
    unsigned SpecialChild = 0;  // Special Children boolean Will make sure only the special child can have a child.
    for (int j = 0; j < 3 && getpid() == Parent; j++){
        if (i == j) {
            SpecialChild = 1;  // Should Hopefully make sure only Special Children get to have new Children
            ChildrenSpecial = fork();  // <----- This is where the Special Are Made. I am using a loop for some reason, Not sure why.
            if (getpid() == Parent) continue;  // So That the parent doesn't copy over its own pid to ChildrenSpecial.
            ChildrenSpecial = getpid();  // This is so I don't need to make another Variable, Recycling is always good.
        }
        else {
            SpecialChild = 0;  // Should Hopefully make sure that Not Special Children get to have no new Children
            fork();  // <----- This is where the Not Special Two are Made. I am using a loop for some reason, Not sure why.
        }
    }

    if (SpecialChild && Parent != getpid()) {
        int statisimo;  // Status Collector.
        pid_t child = fork();  // Child of Child
        if (ChildrenSpecial == getpid()){
            waitpid(child, &statisimo, 0);  // Waits for Child to Finish to collect its status upon exiting.
            doWhatAChildDoesAndNotListenToItsParentsDoWhatAChildDoesAndNotListenToItsParents(statisimo >> 8);  // I make big long name because its funny.
        }
    }

    if (getpid() != Parent) doWhatAChildDoesAndNotListenToItsParents();  // I make slightly big long name because its slightly funny.
    else waitpid(ChildrenSpecial, NULL, 0);  // Waits for the slowest child who needs to have children to prevent issues with parent not appearing.

    return 0;
}
