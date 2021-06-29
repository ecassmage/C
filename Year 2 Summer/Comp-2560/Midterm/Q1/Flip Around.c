//
// Created by evanm on 2021-06-28.
//

/*
//Student ID: 110043572
// Name: Evan Morrison
// Lab Section: Lab 51
//1+1+0 = 2 even Standard
//0+4+3 = 7 odd System
//5+7+2 = 14 even Standard

// Show File3 with System Since Standard is twice and System is once.

I think this is what I am Asked for.
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/// file3 = Rfile1.txtRfile2.txt

typedef struct string{
    char *chr;
    unsigned len;
} str;

str *string(char *chr){
    str *temp = (str*) malloc(sizeof(str));
    temp -> chr = (char*) malloc((strlen(chr)+1) * sizeof(char));
    for (int i = 0; chr[i] != '\0'; i++){
        temp -> chr[i] = chr[i];
    }
    temp -> len = strlen(chr);
    return temp;
}



void concat(str *string, char *word){
    string -> chr = (char*) realloc(string -> chr, ((string -> len + strlen(word) + 1) * sizeof(char)));

    for (unsigned i = 0; i < strlen(word); i++){
        string -> chr[i + string -> len] = word[i];
    }

    string -> len = string -> len + strlen(word);
    string -> chr[string -> len] = '\0';
}
char charAt(str *string, unsigned index){
    return string -> chr[index];
}

str *readFile(FILE *fd){
    char buffer[2] = {'\0'};
    str *temp = string(""); // Annoying that I need "" for now don't have time to add a workaround to that.
    for (int i = 0; fread(buffer, 1, 1, fd) != 0; i++){  // Damn you Carriage stuff.,!!!!! \r
        concat(temp, buffer);
    }
    return temp;
}

str *readFileSys(int fd){
    char buffer[2] = {'\0'};
    str *temp = string(""); // Annoying that I need "" for now don't have time to add a workaround to that.
    for (int i = 0; read(fd, buffer, 1) != 0; i++){  // Damn you Carriage stuff.,!!!!! \r
        concat(temp, buffer);
    }
    return temp;
}

str *cleanCarriage(str *String){
    // I could just return temp but meh.
    str *temp = string("");
    for (int i = 0; i < String -> len; i++){
        if ((charAt(String, i) == '\r' && charAt(String, i+1) == '\n')){
            concat(temp, "\n");
            i++;
        }
        else{
            char chr[2] = {charAt(String, i), '\0'};
            concat(temp, chr);
        }
    }
    free(String -> chr);
    free(String);
    return temp;
}


str *reverse(str *String){
    str *forwards = string("");
    for (int i = String -> len - 1; i >= 0; i--){
        char chr[2] = {charAt(String, i), '\0'};
        concat(forwards, chr);
    }
    free(String -> chr);
    free(String);
    return forwards;
}


void writeStand(FILE *fd, str *string1, str *string2){

    fwrite(string1 -> chr, sizeof(char), string1 -> len, fd);
    fwrite(string2 -> chr, sizeof(char), string2 -> len, fd);

}
int main(int argc, char *argv[]) {
    if(argc != 2) {
        write(STDOUT_FILENO, "There is not enough files given, Please Add more next time!!!\n", strlen("There is not enough files given, Please Add more next time!!!\n"));
        return 0;
    }
    int f3Again = open(argv[1], O_RDONLY);
    str *file3 = readFileSys(f3Again);
    file3 = reverse(cleanCarriage(file3));
    write(STDOUT_FILENO, file3 -> chr, file3 -> len);
    return 0;
}

