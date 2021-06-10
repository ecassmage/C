//#include "linkedList.h"  // Just some stuff I was working on for linked lists.
//#include "List.h"  // Useless since it is just an array of ints.
//#include "realString.h"  // Much nicer strings. keeps strings together as singular objects but still lets you look at individual characters.
/* ===========================================================================
COMP-1410 Lab 6
==============================================================================
Student name: Evan Morrison

Replace the error with a statement citing any sources of outside help:
None

=========================================================================== */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of structure for storing student information

typedef struct str{
    /// This was originally in its own header but since custom headers I am not sure are allowed I copied it into
    /// here for some reason
    char *string;
    unsigned int len;
} str;

typedef struct student {
    int id;
    char *name;  // This is Boring
    str *SName;  // This is a str type I built. It was build from the ground up to be a str.
    // Inspired by python strings, hence the name str. Sadly a little harder to use but still nice.
    // Also while I shouldn't be using str I just finished making it so I wanted to test it out while doing this lab
    // I made everything work with name as well so I am still doing the lab as asked.
}student;

typedef struct studentBody{
    /// Was never told I couldn't do this.
    student *student;  // This stores all the students.
    int lenC;  // This stores how many students are currently written in *student
    int lenT;  // This stores the amount of students *student can hold before stuff starts getting overwritten.
} studentBody;

void error(char arr[]){
    printf("%s\n", arr);
    assert(1 == 0);  // Literally can't be try so basically is the same as exit(0)
}

void ErrorCheckStudentBody(studentBody *studentGroup){
    for (int i = 0; i < studentGroup -> lenT; i++){
        if (&studentGroup -> student[i] == NULL){
            error("Out Of Memory ERROR: \n\tStudentBody has failed to allocate Memory\n");
        }
    }
}

int CLen(studentBody *arr) {return (arr -> lenC);}
int TLen(studentBody *arr) {return (arr -> lenT);}
int sizeDif(studentBody *arr) {return (arr -> lenT) - (arr -> lenC);}

struct student * create_student(int id, char * name);
void free_student(struct student * s);
bool change_name(struct student * s, char * new_name);
void printStudent(student *student);
void printStudents(studentBody *studentBodies);
void newStudentToRoster(studentBody *studentGroup, int id, char name[]);
int studentIndex(studentBody *studentGroup, student *studentKey);
void remove_student(studentBody *studentGroup, student *Student);
studentBody *makeStudentBody();
void printS(str *string);
str *stringWrite(char arr[]);
unsigned int stringLen(str *string);
unsigned int SLen(str *string);
unsigned int combinedSize(str *string, char arr[]);
void concatCalc(str *string, char arr[]);
char *string(str *String);
void newString(str *string, char replace[]);

void addStudentsToList(studentBody *studentSheet){
    // newStudentToRoster will call struct student * create_student(int id, char * name);
    // it just organizes adding the student to a list. This function is to organize the students
    // who will be added since I am really annoyed at C and don't feel like automating it.
    newStudentToRoster(studentSheet, 12345678, "Connor");
    newStudentToRoster(studentSheet, 12345679, "Grognak");
    newStudentToRoster(studentSheet, 12345354, "John");
    newStudentToRoster(studentSheet, 23423428, "Alice");
    newStudentToRoster(studentSheet, 34565324, "Eve");
    newStudentToRoster(studentSheet, 56456342, "Bob");
    newStudentToRoster(studentSheet, 67563423, "Mikel");
    newStudentToRoster(studentSheet, 89865731, "Matt");
    newStudentToRoster(studentSheet, 110043572, "Evan");
}

void assertAddNewStudentsWork(studentBody *studentSheet){

    student *tempStudent = create_student(100100100, "Jim Pickens");
    assert(strcmp(tempStudent -> name, "Jim Pickens") == 0);
    assert(strcmp(string(tempStudent -> SName), "Jim Pickens") == 0);
    assert(tempStudent -> id == 100100100);
    newStudentToRoster(studentSheet, 100100100, "Jim Pickens");

    tempStudent = create_student(506587209, "This is definitely a name, don't be uncultured");
    assert(strcmp(tempStudent -> name, "This is definitely a name, don't be uncultured") == 0);
    assert(strcmp(string(tempStudent -> SName), "This is definitely a name, don't be uncultured") == 0);
    assert(tempStudent -> id == 506587209);
    newStudentToRoster(studentSheet, 506587209, "This is definitely a name, don't be uncultured");

    tempStudent = create_student(12131, "Why would you ever think this was not a name, just look it up, who knows maybe it truly is a real name");
    assert(strcmp(tempStudent -> name, "Why would you ever think this was not a name, just look it up, who knows maybe it truly is a real name") == 0);
    assert(strcmp(string(tempStudent -> SName), "Why would you ever think this was not a name, just look it up, who knows maybe it truly is a real name") == 0);
    assert(tempStudent -> id == 12131);
    newStudentToRoster(studentSheet, 12131, "Why would you ever think this was not a name, just look it up, who knows maybe it truly is a real name");

    tempStudent = create_student(110043572, "Evan");
    assert(strcmp(tempStudent -> name, "Evan") == 0);
    assert(strcmp(string(tempStudent -> SName), "Evan") == 0);
    assert(tempStudent -> id == 110043572);
    newStudentToRoster(studentSheet, 110043573, "Evan The Copy");

    tempStudent = create_student(110043572, "Evan Morrison");
    assert(strcmp(tempStudent -> name, "Evan Morrison") == 0);
    assert(strcmp(string(tempStudent -> SName), "Evan Morrison") == 0);
    assert(tempStudent -> id == 110043572);
    newStudentToRoster(studentSheet, 110043572, "Evan Morrison The Copy");

    tempStudent = create_student(123454321, "This right here is all 1 name okay. Everything below is included.\n"
                                            "You are to complete this assignment without any collaboration except with the course staff.\n"
                                            "This assignment is to be kept private and not shared.\n"
                                            "Proper Submission [1 mark]: Modify the provided lab6.c appropriately and submit two files\n"
                                            "named lab6.c and lab6.txt to the lab 6 submission form on Blackboard. Your lab6.c file\n"
                                            "should be a properly-indented file that correctly compiles. Your lab6.txt should be a plain text\n"
                                            "file. At the top of lab6.c include your name and cite any outside sources that you used while\n"
                                            "working on this lab.\n"
                                            "Part 1: Coding [10 marks]. In the previous lab you used structures for recording student information. However, student names were limited to 20 characters. In many applications this would be a\n"
                                            "significant drawback and in this lab we will use dynamic memory allocation to avoid this limitation.\n"
                                            "This lab uses the following updated structure definition for recording student information:\n"
                                            "struct student {\n"
                                            "int id;\n"
                                            "char * name;\n"
                                            "};\n"
                                            "Complete an implementation for the following prototype of a function that creates a new student\n"
                                            "record using dynamic memory allocation. If not enough memory is available to be allocated for\n"
                                            "either the name or student structure then the program should halt (you can use either assert or\n"
                                            "exit for this).\n"
                                            "// create_student(id, name) creates a new student record with given id and name;\n"
                                            "// allocates memory to store structure and name (caller must free)\n"
                                            "// requires: name is a valid string\n"
                                            "struct student * create_student(int id, char * name);\n"
                                            "Next, complete an implementation for the following prototype of a function that releases the\n"
                                            "memory that has been allocated for a student record created using create_student. Ensure that\n"
                                            "your implementation does not leak memory.\n"
                                            "// free_student(s) frees the memory associated with the student record s\n"
                                            "// requires: s is a student record created using dynamic memory allocation\n"
                                            "void free_student(struct student * s);\n"
                                            "1\n"
                                            "University of Windsor COMP-1410 - Winter 2021 School of Computer Science\n"
                                            "Finally, complete an implementation of a function that changes the name of a given student. The\n"
                                            "function should use malloc or realloc to allocate enough memory to store the new name. If the\n"
                                            "memory allocation fails then return false and do not change the student’s name; otherwise return\n"
                                            "true if the student’s name was successfully returned.\n"
                                            "// change_name(s, new_name) renames the student s to have the name given by\n"
                                            "// new_name; allocates memory to hold new_name (caller must free)\n"
                                            "// returns true if the name was successfully changed and false otherwise\n"
                                            "// requires: s points to a valid student and new_name points to a valid\n"
                                            "// string created using dynamic memory allocation\n"
                                            "bool change_name(struct student * s, char * new_name);\n"
                                            "Part 2: Testing [6 marks]. Use assert and strcmp to test your functions from part 1. Create\n"
                                            "at least three student records using create_student, including one that contains your own name\n"
                                            "and student ID. Test that change_name works correctly (you do not need to test the case when the\n"
                                            "memory allocation fails), and then release the allocated memory using free_student.\n"
                                            "Part 3: Writing [8 marks]. In your own words, briefly explain the logic behind your implementations of the functions that you completed in part 1. Your explanation should be concise, clear, and\n"
                                            "communicate an understanding of how your implementations work.\n"
                                            "Using big O notation what are the running times of create_student, free_student, and change_name\n"
                                            "applied to a student with a name of length n? (In the last case you can assume that n is an upper\n"
                                            "bound on both the student’s new and old names.) Explain your reasoning. You can assume that\n"
                                            "malloc and free run in O(1) operations and realloc applied to a block of memory of length n runs\n"
                                            "in O(n) operations. Smiley Face :P");
    assert(strcmp(tempStudent -> name, "This right here is all 1 name okay. Everything below is included.\n"
                                       "You are to complete this assignment without any collaboration except with the course staff.\n"
                                       "This assignment is to be kept private and not shared.\n"
                                       "Proper Submission [1 mark]: Modify the provided lab6.c appropriately and submit two files\n"
                                       "named lab6.c and lab6.txt to the lab 6 submission form on Blackboard. Your lab6.c file\n"
                                       "should be a properly-indented file that correctly compiles. Your lab6.txt should be a plain text\n"
                                       "file. At the top of lab6.c include your name and cite any outside sources that you used while\n"
                                       "working on this lab.\n"
                                       "Part 1: Coding [10 marks]. In the previous lab you used structures for recording student information. However, student names were limited to 20 characters. In many applications this would be a\n"
                                       "significant drawback and in this lab we will use dynamic memory allocation to avoid this limitation.\n"
                                       "This lab uses the following updated structure definition for recording student information:\n"
                                       "struct student {\n"
                                       "int id;\n"
                                       "char * name;\n"
                                       "};\n"
                                       "Complete an implementation for the following prototype of a function that creates a new student\n"
                                       "record using dynamic memory allocation. If not enough memory is available to be allocated for\n"
                                       "either the name or student structure then the program should halt (you can use either assert or\n"
                                       "exit for this).\n"
                                       "// create_student(id, name) creates a new student record with given id and name;\n"
                                       "// allocates memory to store structure and name (caller must free)\n"
                                       "// requires: name is a valid string\n"
                                       "struct student * create_student(int id, char * name);\n"
                                       "Next, complete an implementation for the following prototype of a function that releases the\n"
                                       "memory that has been allocated for a student record created using create_student. Ensure that\n"
                                       "your implementation does not leak memory.\n"
                                       "// free_student(s) frees the memory associated with the student record s\n"
                                       "// requires: s is a student record created using dynamic memory allocation\n"
                                       "void free_student(struct student * s);\n"
                                       "1\n"
                                       "University of Windsor COMP-1410 - Winter 2021 School of Computer Science\n"
                                       "Finally, complete an implementation of a function that changes the name of a given student. The\n"
                                       "function should use malloc or realloc to allocate enough memory to store the new name. If the\n"
                                       "memory allocation fails then return false and do not change the student’s name; otherwise return\n"
                                       "true if the student’s name was successfully returned.\n"
                                       "// change_name(s, new_name) renames the student s to have the name given by\n"
                                       "// new_name; allocates memory to hold new_name (caller must free)\n"
                                       "// returns true if the name was successfully changed and false otherwise\n"
                                       "// requires: s points to a valid student and new_name points to a valid\n"
                                       "// string created using dynamic memory allocation\n"
                                       "bool change_name(struct student * s, char * new_name);\n"
                                       "Part 2: Testing [6 marks]. Use assert and strcmp to test your functions from part 1. Create\n"
                                       "at least three student records using create_student, including one that contains your own name\n"
                                       "and student ID. Test that change_name works correctly (you do not need to test the case when the\n"
                                       "memory allocation fails), and then release the allocated memory using free_student.\n"
                                       "Part 3: Writing [8 marks]. In your own words, briefly explain the logic behind your implementations of the functions that you completed in part 1. Your explanation should be concise, clear, and\n"
                                       "communicate an understanding of how your implementations work.\n"
                                       "Using big O notation what are the running times of create_student, free_student, and change_name\n"
                                       "applied to a student with a name of length n? (In the last case you can assume that n is an upper\n"
                                       "bound on both the student’s new and old names.) Explain your reasoning. You can assume that\n"
                                       "malloc and free run in O(1) operations and realloc applied to a block of memory of length n runs\n"
                                       "in O(n) operations. Smiley Face :P") == 0);
    assert(strcmp(string(tempStudent -> SName), "This right here is all 1 name okay. Everything below is included.\n"
                                                "You are to complete this assignment without any collaboration except with the course staff.\n"
                                                "This assignment is to be kept private and not shared.\n"
                                                "Proper Submission [1 mark]: Modify the provided lab6.c appropriately and submit two files\n"
                                                "named lab6.c and lab6.txt to the lab 6 submission form on Blackboard. Your lab6.c file\n"
                                                "should be a properly-indented file that correctly compiles. Your lab6.txt should be a plain text\n"
                                                "file. At the top of lab6.c include your name and cite any outside sources that you used while\n"
                                                "working on this lab.\n"
                                                "Part 1: Coding [10 marks]. In the previous lab you used structures for recording student information. However, student names were limited to 20 characters. In many applications this would be a\n"
                                                "significant drawback and in this lab we will use dynamic memory allocation to avoid this limitation.\n"
                                                "This lab uses the following updated structure definition for recording student information:\n"
                                                "struct student {\n"
                                                "int id;\n"
                                                "char * name;\n"
                                                "};\n"
                                                "Complete an implementation for the following prototype of a function that creates a new student\n"
                                                "record using dynamic memory allocation. If not enough memory is available to be allocated for\n"
                                                "either the name or student structure then the program should halt (you can use either assert or\n"
                                                "exit for this).\n"
                                                "// create_student(id, name) creates a new student record with given id and name;\n"
                                                "// allocates memory to store structure and name (caller must free)\n"
                                                "// requires: name is a valid string\n"
                                                "struct student * create_student(int id, char * name);\n"
                                                "Next, complete an implementation for the following prototype of a function that releases the\n"
                                                "memory that has been allocated for a student record created using create_student. Ensure that\n"
                                                "your implementation does not leak memory.\n"
                                                "// free_student(s) frees the memory associated with the student record s\n"
                                                "// requires: s is a student record created using dynamic memory allocation\n"
                                                "void free_student(struct student * s);\n"
                                                "1\n"
                                                "University of Windsor COMP-1410 - Winter 2021 School of Computer Science\n"
                                                "Finally, complete an implementation of a function that changes the name of a given student. The\n"
                                                "function should use malloc or realloc to allocate enough memory to store the new name. If the\n"
                                                "memory allocation fails then return false and do not change the student’s name; otherwise return\n"
                                                "true if the student’s name was successfully returned.\n"
                                                "// change_name(s, new_name) renames the student s to have the name given by\n"
                                                "// new_name; allocates memory to hold new_name (caller must free)\n"
                                                "// returns true if the name was successfully changed and false otherwise\n"
                                                "// requires: s points to a valid student and new_name points to a valid\n"
                                                "// string created using dynamic memory allocation\n"
                                                "bool change_name(struct student * s, char * new_name);\n"
                                                "Part 2: Testing [6 marks]. Use assert and strcmp to test your functions from part 1. Create\n"
                                                "at least three student records using create_student, including one that contains your own name\n"
                                                "and student ID. Test that change_name works correctly (you do not need to test the case when the\n"
                                                "memory allocation fails), and then release the allocated memory using free_student.\n"
                                                "Part 3: Writing [8 marks]. In your own words, briefly explain the logic behind your implementations of the functions that you completed in part 1. Your explanation should be concise, clear, and\n"
                                                "communicate an understanding of how your implementations work.\n"
                                                "Using big O notation what are the running times of create_student, free_student, and change_name\n"
                                                "applied to a student with a name of length n? (In the last case you can assume that n is an upper\n"
                                                "bound on both the student’s new and old names.) Explain your reasoning. You can assume that\n"
                                                "malloc and free run in O(1) operations and realloc applied to a block of memory of length n runs\n"
                                                "in O(n) operations. Smiley Face :P") == 0);
    assert(tempStudent -> id == 123454321);
    newStudentToRoster(studentSheet, 123454321, "This right here is all 1 name okay. Everything below is included.\n"
                                                "You are to complete this assignment without any collaboration except with the course staff.\n"
                                                "This assignment is to be kept private and not shared.\n"
                                                "Proper Submission [1 mark]: Modify the provided lab6.c appropriately and submit two files\n"
                                                "named lab6.c and lab6.txt to the lab 6 submission form on Blackboard. Your lab6.c file\n"
                                                "should be a properly-indented file that correctly compiles. Your lab6.txt should be a plain text\n"
                                                "file. At the top of lab6.c include your name and cite any outside sources that you used while\n"
                                                "working on this lab.\n"
                                                "Part 1: Coding [10 marks]. In the previous lab you used structures for recording student information. However, student names were limited to 20 characters. In many applications this would be a\n"
                                                "significant drawback and in this lab we will use dynamic memory allocation to avoid this limitation.\n"
                                                "This lab uses the following updated structure definition for recording student information:\n"
                                                "struct student {\n"
                                                "int id;\n"
                                                "char * name;\n"
                                                "};\n"
                                                "Complete an implementation for the following prototype of a function that creates a new student\n"
                                                "record using dynamic memory allocation. If not enough memory is available to be allocated for\n"
                                                "either the name or student structure then the program should halt (you can use either assert or\n"
                                                "exit for this).\n"
                                                "// create_student(id, name) creates a new student record with given id and name;\n"
                                                "// allocates memory to store structure and name (caller must free)\n"
                                                "// requires: name is a valid string\n"
                                                "struct student * create_student(int id, char * name);\n"
                                                "Next, complete an implementation for the following prototype of a function that releases the\n"
                                                "memory that has been allocated for a student record created using create_student. Ensure that\n"
                                                "your implementation does not leak memory.\n"
                                                "// free_student(s) frees the memory associated with the student record s\n"
                                                "// requires: s is a student record created using dynamic memory allocation\n"
                                                "void free_student(struct student * s);\n"
                                                "1\n"
                                                "University of Windsor COMP-1410 - Winter 2021 School of Computer Science\n"
                                                "Finally, complete an implementation of a function that changes the name of a given student. The\n"
                                                "function should use malloc or realloc to allocate enough memory to store the new name. If the\n"
                                                "memory allocation fails then return false and do not change the student’s name; otherwise return\n"
                                                "true if the student’s name was successfully returned.\n"
                                                "// change_name(s, new_name) renames the student s to have the name given by\n"
                                                "// new_name; allocates memory to hold new_name (caller must free)\n"
                                                "// returns true if the name was successfully changed and false otherwise\n"
                                                "// requires: s points to a valid student and new_name points to a valid\n"
                                                "// string created using dynamic memory allocation\n"
                                                "bool change_name(struct student * s, char * new_name);\n"
                                                "Part 2: Testing [6 marks]. Use assert and strcmp to test your functions from part 1. Create\n"
                                                "at least three student records using create_student, including one that contains your own name\n"
                                                "and student ID. Test that change_name works correctly (you do not need to test the case when the\n"
                                                "memory allocation fails), and then release the allocated memory using free_student.\n"
                                                "Part 3: Writing [8 marks]. In your own words, briefly explain the logic behind your implementations of the functions that you completed in part 1. Your explanation should be concise, clear, and\n"
                                                "communicate an understanding of how your implementations work.\n"
                                                "Using big O notation what are the running times of create_student, free_student, and change_name\n"
                                                "applied to a student with a name of length n? (In the last case you can assume that n is an upper\n"
                                                "bound on both the student’s new and old names.) Explain your reasoning. You can assume that\n"
                                                "malloc and free run in O(1) operations and realloc applied to a block of memory of length n runs\n"
                                                "in O(n) operations. Smiley Face :P");

}

void assertChangingNamesWorks(studentBody *studentSheet){

    change_name(&studentSheet -> student[0], "This is definitely a new Name");
    assert(strcmp(studentSheet -> student[0].name, "This is definitely a new Name") == 0);
    assert(strcmp(string(studentSheet -> student[0].SName), "This is definitely a new Name") == 0);

    change_name(&studentSheet -> student[1], "Grognak The Destroyer, Attorney at Law, Esquire, M.D.");
    assert(strcmp(studentSheet -> student[1].name, "Grognak The Destroyer, Attorney at Law, Esquire, M.D.") == 0);
    assert(strcmp(string(studentSheet -> student[1].SName), "Grognak The Destroyer, Attorney at Law, Esquire, M.D.") == 0);

    change_name(&studentSheet -> student[2], "John Wilson");
    assert(strcmp(studentSheet -> student[2].name, "John Wilson") == 0);
    assert(strcmp(string(studentSheet -> student[2].SName), "John Wilson") == 0);

    change_name(&studentSheet -> student[3], "Was This is A bad Idea");
    assert(strcmp(studentSheet -> student[3].name, "Was This is A bad Idea") == 0);
    assert(strcmp(string(studentSheet -> student[3].SName), "Was This is A bad Idea") == 0);

    change_name(&studentSheet -> student[4], "This is definitely a Bad Idea");
    assert(strcmp(studentSheet -> student[4].name, "This is definitely a Bad Idea") == 0);
    assert(strcmp(string(studentSheet -> student[4].SName), "This is definitely a Bad Idea") == 0);

    change_name(&studentSheet -> student[5], "Bobby");
    assert(strcmp(studentSheet -> student[5].name, "Bobby") == 0);
    assert(strcmp(string(studentSheet -> student[5].SName), "Bobby") == 0);

    change_name(&studentSheet -> student[6], "Michael");
    assert(strcmp(studentSheet -> student[6].name, "Michael") == 0);
    assert(strcmp(string(studentSheet -> student[6].SName), "Michael") == 0);

    change_name(&studentSheet -> student[7], "Matt Matt");
    assert(strcmp(studentSheet -> student[7].name, "Matt Matt") == 0);
    assert(strcmp(string(studentSheet -> student[7].SName), "Matt Matt") == 0);

    change_name(&studentSheet -> student[8], "Evan Morrison");
    assert(strcmp(studentSheet -> student[8].name, "Evan Morrison") == 0);
    assert(strcmp(string(studentSheet -> student[8].SName), "Evan Morrison") == 0);

    change_name(&studentSheet -> student[9], "The Dear Leader Jim Pickens");
    assert(strcmp(studentSheet -> student[9].name, "The Dear Leader Jim Pickens") == 0);
    assert(strcmp(string(studentSheet -> student[9].SName), "The Dear Leader Jim Pickens") == 0);

    change_name(&studentSheet -> student[10], "France has won more conflicts then any other nation in Europe and possibly even the world and yet are laughed at for surrendering");
    assert(strcmp(studentSheet -> student[10].name, "France has won more conflicts then any other nation in Europe and possibly even the world and yet are laughed at for surrendering") == 0);
    assert(strcmp(string(studentSheet -> student[10].SName), "France has won more conflicts then any other nation in Europe and possibly even the world and yet are laughed at for surrendering") == 0);

    change_name(&studentSheet -> student[11], "World War 2 never Technically ended as Japan and Soviet Russia never signed a peace treaty even to this day");
    assert(strcmp(studentSheet -> student[11].name, "World War 2 never Technically ended as Japan and Soviet Russia never signed a peace treaty even to this day") == 0);
    assert(strcmp(string(studentSheet -> student[11].SName), "World War 2 never Technically ended as Japan and Soviet Russia never signed a peace treaty even to this day") == 0);

    change_name(&studentSheet -> student[12], "Alexander the great made an island into a peninsula so that he could properly siege it");
    assert(strcmp(studentSheet -> student[12].name, "Alexander the great made an island into a peninsula so that he could properly siege it") == 0);
    assert(strcmp(string(studentSheet -> student[12].SName), "Alexander the great made an island into a peninsula so that he could properly siege it") == 0);

    change_name(&studentSheet -> student[13], "The Medieval era lasted from the fall of the Roman Empire to the fall of the Roman Empire");
    assert(strcmp(studentSheet -> student[13].name, "The Medieval era lasted from the fall of the Roman Empire to the fall of the Roman Empire") == 0);
    assert(strcmp(string(studentSheet -> student[13].SName), "The Medieval era lasted from the fall of the Roman Empire to the fall of the Roman Empire") == 0);

    change_name(&studentSheet -> student[14], "Well that old name was an eye sore. Sorry about that.");
    assert(strcmp(studentSheet -> student[14].name, "Well that old name was an eye sore. Sorry about that.") == 0);
    assert(strcmp(string(studentSheet -> student[14].SName), "Well that old name was an eye sore. Sorry about that.") == 0);
}

void freeEntireStudentBody(studentBody *studentSheet){
    /*for (int i = CLen(studentSheet)-1; 0 <= i; i--){
        remove_student(studentSheet, &studentSheet -> student[i]);
    }*/
    /// Didn't work, I would assume because I was trying to deallocate space that wasn't deallocatable in the way I was trying
    free(studentSheet -> student);
    free(studentSheet);
    student *tempPtr = create_student(970640310, "Temp Name");
    free_student(tempPtr);

}

int main(void) {
    // Implement your test code here
    studentBody *studentSheet = makeStudentBody();
    addStudentsToList(studentSheet);
    assertAddNewStudentsWork(studentSheet);
    printStudents(studentSheet);
    printf("\n\n");
    assertChangingNamesWorks(studentSheet);
    printStudents(studentSheet);
    freeEntireStudentBody(studentSheet);
    printf("\n\nI will now print all the students currently not freed from their eternal prison:\n");
    //printStudents(studentSheet);
    printf("Just Kidding can't actually print it since It doesn't exist anymore.\n");
    printf("\nProgram has completed Successfully\n\n");
}

void printStudent(student *student){
    printf("< Student ID -> %d > : < Student Name -> %s >\n", student -> id, student -> name);
}

void printStudents(studentBody *studentBodies){
    for (int i = 0; i < CLen(studentBodies); i++){
        printf("< Student: %d: Student ID -> %d > : < Student Name -> %s >\n", i, studentBodies -> student[i].id, studentBodies -> student[i].name);
    }

}

void newStudentToRoster(studentBody *studentGroup, int id, char name[]){
    if (CLen(studentGroup) == TLen(studentGroup)){
        studentGroup -> student = (student*) realloc(studentGroup -> student, (TLen(studentGroup) * 10) * sizeof(student));
        studentGroup -> lenT *= 10;
        ErrorCheckStudentBody(studentGroup);
    }
    studentGroup -> student[CLen(studentGroup)] = *create_student(id, name);
    studentGroup -> lenC++;
}

int studentIndex(studentBody *studentGroup, student *studentKey){
    for (int i = 0; i < studentGroup -> lenC; i++){
        if (&studentGroup -> student[i] == studentKey){
            return i;
        }
    }
    error("Index ERROR: \n\tKey could not be located inside array\n");
    return 0; /// Won't reach, just here to remove annoying warning.
}

void remove_student(studentBody *studentGroup, student *Student){
    free_student(Student);
    for (int i = studentIndex(studentGroup, Student)+1; i < CLen(studentGroup); i++){
        studentGroup -> student[i-1] = studentGroup -> student[i];
    }
    studentGroup -> lenC--;
    if (CLen(studentGroup) > 0 && TLen(studentGroup) / CLen(studentGroup) >= 15){
        studentGroup -> student = (student*) realloc(studentGroup -> student, (TLen(studentGroup) / 10) * sizeof(student));
        studentGroup -> lenT /= 10;
        ErrorCheckStudentBody(studentGroup);
    }
}

void free_student(struct student * s){
    free(s);
}

studentBody *makeStudentBody(){
    studentBody *studentSheet = (studentBody*) calloc(1, sizeof(studentBody));
    studentSheet -> student = (student*) calloc(1, sizeof(student));
    studentSheet -> lenT = 1;
    studentSheet -> lenC = 0;
    return studentSheet;
}

struct student * create_student(int id, char * name){
    student *temp = (student*) calloc(1, sizeof(student)); // calloc() sets everything to default so I like it more.
    temp -> name = (char*) calloc(strlen(name) + 1, sizeof(char)); // To guarantee that it has \0
    if (temp == NULL){
        error("Out Of Memory ERROR: \n\tstruct student failed to find required space\n");
    }
    if (temp -> name == NULL){
        error("Out Of Memory ERROR: \n\tchar array failed to find required space\n");
    }
    strcpy(temp -> name, name);
    temp -> SName = stringWrite(name);
    temp -> id = id;
    return temp;
}

bool change_name(struct student * s, char * new_name) {
    s->name = (char *) realloc(s->name, (1 + strlen(new_name)) * sizeof(char));
    if (s -> name == NULL){
        printf("Out Of Memory: \n\tchar array failed to find required space\n");
        return false;
    }
    int i = 0;
    for (; new_name[i] != '\0'; i++) {
        s->name[i] = new_name[i];
    }
    s->name[i] = '\0';
    newString(s -> SName, new_name);
    return true;
}

void printS(str *string){
    printf("%s\n", string -> string);
}

str *stringWrite(char arr[]){
    str *temp = (str*) calloc(1, sizeof(str));
    if (strlen(arr) == 0) {
        temp -> string = (char*) calloc(1, sizeof(char));
        return temp;
    }
    temp -> string = (char*) calloc(strlen(arr) + 1, sizeof(char));
    int i = 0;
    for (; arr[i] != '\0'; i++){
        temp -> string[i] = arr[i];
    }
    temp -> string[i] = '\0';
    temp -> len = strlen(arr);

    return temp;
}

unsigned int stringLen(str *string){
    unsigned int c = 0;
    while (string -> string[c] != '\0') c++;
    return c;
}

unsigned int SLen(str *string){
    return string -> len;
}

unsigned int combinedSize(str *string, char arr[]){
    return stringLen(string) + strlen(arr);
}

void concatCalc(str *string, char arr[]){
    string -> string = (char*) realloc(string -> string, (combinedSize(string, arr)+1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        string -> string[SLen(string)+i] = arr[i];
    }
    string -> string[SLen(string)+i] = '\0';
    string -> len += strlen(arr);
}

char *string(str *String){
    return String -> string;
}

void newString(str *string, char replace[]){
    string -> string = (char*) realloc(string -> string, (1 + strlen(replace)) * sizeof(char));
    int i = 0;
    for (; replace[i] != '\0'; i++){
        string -> string[i] = replace[i];
    }
    string -> string[i] = '\0';
    string -> len = stringLen(string);
}
