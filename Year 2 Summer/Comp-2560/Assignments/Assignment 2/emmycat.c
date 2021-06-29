#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/**
 * Holds stuff for arrays. Yippee No more having to send the size of an array. OOP is Better.
 */
typedef struct overheadString{
    unsigned int lenArr;
} overheadString;

/**
 * Structure for str holds information like the char array and length of string. as well as some array information.
 */
typedef struct str{
    char *stringContainer;
    unsigned int len;
    overheadString *lenFo;
} str;

void ERROR(char errorMessage[]){
    printf("ERROR: %s\n", errorMessage);
    exit(0);
}

/**
 * Writes string, Would be Private if I New how to make it Private.
 * @param container Takes a str which which contain the character array
 * @param positionStart Takes an int for index position inside str which will begin writing str.
 * @param word takes char array for word wanted to be added.
 * @return returns int for where ptr inside str finished at.
 */
int strWrite(str *container, int positionStart, const char word[]);

/**
 * Writes a String to str structure.
 * <p>
 *  This Writes a String taking an input of a char array before then writing the information needed to a str structure.
 * <\p>
 * @param newStr takes a char array for the str.
 * @return returns a malloc written string.
 */
str* String(char newStr[]);

/**
 * returns length of string
 * @param string takes str of what you want length of.
 * @return returns length of @param string.
 */
unsigned len(str *string);

/**
 * concatenates a single char array to a string
 * @param string takes a str to take @param arr
 * @param arr takes a char array to concatenate
 */
void concatSingle(str *string, char arr[]);

/**
 * concatenates a single char to a string
 * @param string takes a str to take @param chr
 * @param chr takes a char to concatenate
 */
void concatSingleChar(str *string, char chr);

/**
 * Gets the char array of a str.
 * @param string takes a str.
 * @return returns @param string char array.
 */
char *getStr(str *string);

/**
 * deallocates str structure. for cleaning if needed.
 * @param string does stringy things. Maybe even Stringledee dee Things.
 */
void deleteStr(str *string);

/**
 * Reads a file to a string structure. Funny Times ahead. Forgot to write this so this is what you get on my not so formal explanation.
 * @param fd takes an int for location on system i/o file. Takes a file opened with reading capabilities.
 * @return Returns a String written to the heap.
 */
str *readToStrSys(int fd);

/**
 * Will print a string / array of strings to the console.
 * <p>
 *      %s: for String
 *      %a: for Array of Strings
 *  For this Implementation %a does not function to save space but it does work trust me.
 * </p>
 * @param message
 * @param ...
 */
void printStr(const char message[], ...);

int main(int argc, char *argv[]) {
    if (argc == 1){
        printf("No Files Given\n");
        exit(0);
    }
    int fd = open(argv[1], 'r');
    str *String = readToStrSys(fd);
    printStr("%s\n", String);
    close(fd);
    deleteStr(String);
}

unsigned len(str *string){return string -> len;}

int strWrite(str *container, int positionStart, const char word[]){
    int c = 0;
    while (word[c] != '\0') {
        container -> stringContainer[positionStart + c] = word[c];
        c++;
    }
    return c;
}

char *getStr(str *string){return string -> stringContainer;}

str *StringArr(char newStr[], overheadString *lengthSizes){
    str *string = (str*) malloc(sizeof(str));
    string -> stringContainer = (char*) malloc((strlen(newStr) + 1) * sizeof(char));
    string -> lenFo = lengthSizes;
    if (string == NULL) ERROR("Unable to allocate Memory");
    string -> len = strWrite(string, 0, newStr);
    string -> lenFo -> lenArr++;
    string -> stringContainer[len(string)] = '\0';
    return string;
}

void concatSingleChar(str *string, char chr){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + 2) * sizeof(char));
    string -> stringContainer[len(string)] = chr;
    string -> len++;
    string -> stringContainer[len(string)] = '\0';
}

void concatSingle(str *string, char arr[]){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + strlen(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        string -> stringContainer[len(string)+i] = arr[i];
    }
    string -> stringContainer[len(string)+i] = '\0';
    string -> len += strlen(arr);
}

str* String(char newStr[]){
    overheadString *temp = (overheadString*) malloc(sizeof(overheadString));
    temp -> lenArr = 0;
    return StringArr(newStr, temp);
}

str *readToStrSys(int fd){
    lseek(fd, 0, SEEK_SET);
    char buffer[1];
    long ch;
    str *temp = String("");
    while ((ch = read(fd, buffer, 1)) > 0){
        if (ch == 0) break; // Useless probably because of while loop but meh
        concatSingleChar(temp, buffer[0]);
    }
    return temp;
}

void printStr(const char message[], ...){
    str *tempMessage = String("");
    va_list strList;
    va_start(strList, message);
    for (int i = 0; message[i] != '\0'; i++){
        if (message[i] == '%'){
            switch (message[i+1]){
                case 's': //I don't feel like limiting size at the moment, Might Later DUNNO.
                    concatSingle(tempMessage, getStr(va_arg(strList, str*)));
                    i++;
                    break;
//                case 'a': //I don't feel like limiting size at the moment, Might Later DUNNO.
//                    concatSingle(tempMessage, getStr(strArrToStr(va_arg(strList, str**))));
//                    i++; Takes more importing from header then worth it. Won't cause any issues though.
            }

        }
        else concatSingleChar(tempMessage, message[i]);
    }
    printf("%s", getStr(tempMessage));
    va_end(strList);
}

void deleteStr(str *string){
    free(string -> stringContainer);
    free(string -> lenFo);
    free(string);
}
