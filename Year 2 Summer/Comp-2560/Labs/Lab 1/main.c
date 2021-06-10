#include <stdio.h>
#include <stdlib.h>
// Totally Forgot to give this its own folder in Lab1 Folder
int main(int argc, char *argv[]) {
    FILE *fd;
    char c;

    if (argc == 1) fd = stdin;
    else if ((fd = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error opening %s, exiting\n", argv[1]);
        exit(0); // <stdlib.h> is for exit(0) to make it work here.
    }
    while ((c = getc(fd)) != EOF) {
        if (c == '/') break; // This is so I can break out of the program easier then just forcefully terminating program
        putc(c, stdout);
    }

    exit(0);
}
