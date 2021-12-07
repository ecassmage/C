//
// Created by evanm on 2021-07-22.
//

#include <stdio.h>

int main()
{
    FILE *p;
    char ch;

    /*p = popen("ver","r");   /* DOS */
    p = popen("ls","r"); /* Unix */
    if( p == NULL)
    {
        puts("Unable to open process");
        return(1);
    }
    while( (ch=fgetc(p)) != EOF)
        putchar(ch);
    pclose(p);

    return(0);
}