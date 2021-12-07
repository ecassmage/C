//
// Created by evanm on 2021-07-19.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";

int main()
{
    char *inbuf = calloc(strlen(msg1) + 1, 1);
    int p[2], i;

    if (pipe(p) < 0)
        exit(1);

    /* continued */
    /* write pipe */

    write(p[1], msg1, strlen(msg1));
    write(p[1], msg2, strlen(msg2));
//    close(p[1]);
    write(p[1], msg3, strlen(msg3));  // So Even if the pipe is closed on the writing end this will still work properly, but it will not be able to send the information through.
    write(p[1], msg3, strlen(msg3));  // So Even if the pipe is closed on the writing end this will still work properly, but it will not be able to send the information through.
    close(p[1]);  // Hmm, interesting, it seems that if you close the writing end of the pipe, when calling the read section it just re uses the last string that was past through.
    //If however close is not used then it will freeze waiting for something
    for (i = 0; i < 6; i++) {
        /* read pipe */
        read(p[0], inbuf, strlen(msg1));
        printf("%s\n", inbuf);
    }
    return 0;
}