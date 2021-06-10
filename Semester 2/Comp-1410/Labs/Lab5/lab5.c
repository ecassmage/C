/* ===========================================================================
COMP-1410 Lab 5
==============================================================================
Student name: Evan Morrison

Replace the error with a statement citing any sources of outside help:
None

=========================================================================== */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define lengthStruct 10000  // Change up or down if you want more or less students. Warning higher numbers will take a seriously long time
#define names 40  // Don't change unless you add more names to the list of names.
#define printStructure false  // Will print all the students if true. Activate at your own risk.

// Definition of structure for storing student information
struct student {
    int id;
    char name[20];
    // int nameSize; If I was allowed I would add this to better iterate through a names characters if need be
};

// find_id(id, arr, n, found_name) searches for a student with given id in arr;
//   returns true if such a student is found and found_name is updated to
//   hold the student's name; otherwise returns false
// requires: arr has length n
//           students in arr have unique ids
//           found_name points to enough memory to hold a name
bool find_id(int id, struct student arr[], int n, char *found_name);

// find_name(name, arr, n, ids) searches for student(s) with given name in arr;
//   returns the number of students found and the array ids is updated to
//   contain the id numbers of those students
// requires: arr has length n
//           students in arr have unique ids
//           ids points to enough memory to hold the found student ids
int find_name(char * name, struct student arr[], int n, int ids[]);

// change_name(s, new_name) renames the student s to have the name given by
//   new_name
// requires: s points to a valid student that can be modified
//           new_name points to a valid string of length at most 19
void change_name(struct student * s, char * new_name);


int randomInt(int from, int to){
    return rand() % (to - from) + from;
}


void printStruct(struct student arrayOfStudents[]){
    for (int i = 0; i < lengthStruct; i++){
        printf("ID: %d, Name: %s\n", arrayOfStudents[i].id, arrayOfStudents[i].name);
    }
}


void makeObject(struct student arrayOfStudents[], char nameArray[][20], int namesUsed[]){  //// Not actual OOP just name.
    /* I am not sure if this is universal or just my machine but when debugging my work the strings and ints tend
     * to be just random values and not uniform so I tend to initialize them with what I want from the get go
     * 0 for ints and '\0' for chars. This makes it so I know what the value is before I even look at it and therefore
     * know what to look for if I need to exit. The debugger is showing my structs to have random values like
     * \a or - in the place of \000 for name so I had to take this approach to clean them up.
     */
    for (int numInArray = 0; numInArray < lengthStruct-1;){
        int randomName = randomInt(0, names);
        int randomID = randomInt(1000000, 10000000);
        bool alreadyUsed = false;
        for (int i = 0; i < lengthStruct-1 && arrayOfStudents[i].id != 0; i++){
            if (arrayOfStudents[i].id == randomID){
                alreadyUsed = true;
                break;
            }
        }
        if (alreadyUsed == 0){
            arrayOfStudents[numInArray].id = randomID;
            strcpy(arrayOfStudents[numInArray].name, nameArray[randomName]);
            namesUsed[randomName]++;
            numInArray++;
        }
    }
    arrayOfStudents[lengthStruct-1].id = 110043572;
    strcpy(arrayOfStudents[lengthStruct-1].name, "Evan");
    namesUsed[0]++;
    if (printStructure == 1)
        printStruct(arrayOfStudents); // This will print every id and student name for you, enable at your own risk.
}


void assertFindId(struct student arrayOfStudents[]){
//    static struct student arrayOfStudents[lengthStruct] = {0, "\0"};
//    makeObject(arrayOfStudents);
    char found_name[20] = {0};
    for (int i = 0; i < lengthStruct; i++){
        int randNum = randomInt(0, lengthStruct);
        // bool TruthValue = find_id(arrayOfStudents[randNum].id, arrayOfStudents, lengthStruct, found_name);
        assert(find_id(arrayOfStudents[randNum].id, arrayOfStudents, lengthStruct, found_name) == 1);
        // assert(TruthValue == 1);
        assert(strcmp(arrayOfStudents[randNum].name, found_name) == 0);
    }
    assert(find_id(1123, arrayOfStudents, lengthStruct, found_name) == 0); // these should test failure to find
    assert(find_id(14, arrayOfStudents, lengthStruct, found_name) == 0); // these should test failure to find
    assert(find_id(113234223, arrayOfStudents, lengthStruct, found_name) == 0); // these should test failure to find
    printf("We searched for and found the id %d times and managed to record the name everytime as well!!!\n", lengthStruct);
}


bool SubAssertFindNames(struct student arrayOfStudents[], const int idArray[], int length, char name[]){
    int iterationThroughCurrently = 0;
    for (int idInIdArr = 0; idInIdArr < lengthStruct; idInIdArr++){
        if (arrayOfStudents[idInIdArr].id == idArray[iterationThroughCurrently]){
            if (strcmp(arrayOfStudents[idInIdArr].name, name) == 0){
                iterationThroughCurrently++;
            }
            else return false;
        }
    }
    if (iterationThroughCurrently == length) return true; else return false;
}


void assertFindNames(struct student arrayOfStudents[], char nameArray[][20], int namesUsed[]){
    // namesUsed holds a count of every name used in the writing of the arrayOfStudents, it can be trusted to be correct
    int arrOfId[lengthStruct] = {0};
    for (int i = 0; i < lengthStruct; i++){
        int randNum = randomInt(0, names);
        int number = find_name(nameArray[randNum], arrayOfStudents, lengthStruct, arrOfId);
        assert(find_name(nameArray[randNum], arrayOfStudents, lengthStruct, arrOfId) == namesUsed[randNum]);
        assert(SubAssertFindNames(arrayOfStudents, arrOfId, namesUsed[randNum], nameArray[randNum]) == 1);
        // if SubAssertFindNames returns true it means every id has the correct name attached to it
    }

    assert(find_name("NotAName", arrayOfStudents, lengthStruct, arrOfId) == 0);
    assert(arrOfId[0] == 0);

    assert(find_name("NotAName52", arrayOfStudents, lengthStruct, arrOfId) == 0);
    assert(arrOfId[0] == 0); // 0 means that none of the elements have been filled since 0 is not a valid id and you have to start with filling index 0

    printf("We searched for and found the names %d times and managed to record all the id's as well!!!\n", lengthStruct);
}


void assertChangeNames(struct student arrayOfStudents[], char nameArray[][20]){
    for (int i = 0; i < lengthStruct; i++){
        int randName = randomInt(0, names);
        int randStudent = randomInt(0, lengthStruct);
        change_name(&arrayOfStudents[randStudent], nameArray[randName]);
        assert(strcmp(arrayOfStudents[randStudent].name, nameArray[randName]) == 0);
    }
    printf("We Successfully changed %d names\n", lengthStruct);
}


void assertsMainFrame(){
    char nameArray[names][20] = {
            "Evan", "Bob", "Alice", "Eve", "John", "Mikel", "Michael", "Jack", "Matt", "Matthew", "Alexander",
            "Clarisse", "Jennifer", "Margaret", "Karen", "Isaac", "Brady", "Umar", "Janet", "Laila", "Zachary",
            "Ali", "Allie", "Parth", "Mohammad", "Caden", "Gabriela", "Gabrielle", "Jasper", "Owen", "Ryan",
            "Jeremie", "Sam", "Keyana", "Eden", "Selena", "Chloe", "Sally", "Archie", "Jenny"
    };
    static struct student arrayOfStudents[lengthStruct] = {0, "\0"};
    int numsInArray[names] = {0};
    makeObject(arrayOfStudents, nameArray, numsInArray);
    assertFindId(arrayOfStudents);
    assertFindNames(arrayOfStudents, nameArray, numsInArray);
    assertChangeNames(arrayOfStudents, nameArray);
}


int main(void) {
    srand(time(NULL));
    // Implement your test code here
    assertsMainFrame(); // manages the program from the shadows. OOOOHHH
    printf("All tests passed successfully.\n");
}


bool find_id(int id, struct student arr[], int n, char *found_name){
    ////  arr[i].name[0] != '\0' catches breaks on first element which doesn't currently have a name
    //// and i < n breaks upon no element being left in the memory.
    //// Also if you actually wanted this to be O(n) you should have made char *found_name, char **found_name
    for (int i = 0; arr[i].name[0] != '\0' && i < n; i++){ //// This arr[i].id != 0 will stop program from checking unused array elements.
        if (arr[i].id == id){
            strcpy(found_name, arr[i].name);
            // printf("ID < %d > was found\n", id); // Nice little found me message
            return true;
        }
    }
    // printf("ID < %d > was not found\n", id);  // Warning that something wasn't found
    return false;
}


int find_name(char * name, struct student arr[], int n, int ids[]){
    memset(ids, 0, n); // Cleaning out any old ids still remaining in the array
    int count = 0;
    for (int i = 0; arr[i].name[0] != '\0' && i < n; i++){
        if (strcmp(name, arr[i].name) == 0){
            ids[count] = arr[i].id;
            count++;
        }
    }
    return count;
}


void change_name(struct student *s, char *new_name){
    //// This is O(20)
    // strcpy((*s).name, new_name); // I like this better
    for (int i = 0; i < 20; i++) s -> name[i] = *(new_name + i);
}
















