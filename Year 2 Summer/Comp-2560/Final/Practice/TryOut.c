//
// Created by evanm on 2021-08-12.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
    char buf[11] = {'\0'};
    //char buffer;
    //FILE *temp = freopen("File.txt", "w+", stdout);

    //system("stty raw");
    //sleep(3);
    for (int i = 0; i < 1; i++){
        system("stty raw");
        fread(buf, 10, 1, stdin);
        system("stty cooked");
        fwrite(buf, 10, 1, stdout);
    }
    //char eof = EOF;
    //fwrite(&eof, 2, 1, stdout);

    //printf("%s\n", buf);
    //fwrite(buf, 10, 1, stdout);

}