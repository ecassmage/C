//
// Created by evanm on 2021-08-16.
//

#ifndef PIPO_H
#define PIPO_H

#ifndef _STDIO_H_
#include <stdio.h>
#endif
#ifndef _UNISTD_H_
#include <unistd.h>
#endif
#ifndef _FCNTL_H
#include <fcntl.h>
#endif
#ifndef _STRING_H_
#include <string.h>
#endif
#ifndef _STDLIB_H_
#include <stdlib.h>
#endif

/**
 * Will take a pipe and read the contents before writing it to the output given through fDesc. Escape characters can be customized by adding EC to the end of readWritePipe.
 * @param fDesc Takes a fd for the output.
 * @param fd Takes the Pipe fd.
 * @param includeEscapeCharacter include the escape character in writing to fDesc.
 * @param escapeCharacters char array holding all characters wanted to catch to stop read/writing.
 * @return number of characters written to fDesc.
 */
int readWritePipeECI(int fDesc, int fd[], int includeEscapeCharacter, char *escapeCharacters){
    if (includeEscapeCharacter != 0 && includeEscapeCharacter != 1) exit(0);
    char buf;
    int KeepLoopRunning = 1;
    unsigned num = 0;
    while (read(fd[0], &buf, 1) > 0 && num >= 0){
        if (includeEscapeCharacter == 1) {
            write(fDesc, &buf, 1);
            num++;
        }
        for (int i = 0; i < strlen(escapeCharacters); i++) {
            if (buf == escapeCharacters[i]) {
                KeepLoopRunning = 0;
                break;
            }
        }
        if (!KeepLoopRunning) break;
        if (includeEscapeCharacter == 0) {
            write(fDesc, &buf, 1);
            num++;
        }
    }
    return (int) num;
}

int readWritePipeEC(int fDesc, int fd[], char *escapeCharacters){
    return readWritePipeECI(fDesc, fd, 1, escapeCharacters);
}


int readWritePipe(int fDesc, int fd[]){
    return readWritePipeECI(fDesc, fd, 1, "\n");
}

void writeToPipe(int fd[], char *message){
    write(fd[1], message, strlen(message));
}
void writeToPipenl(int fd[], char *message){
    writeToPipe(fd, message);
    write(fd[1], "\n", 1);
}

#endif //PIPO_H
