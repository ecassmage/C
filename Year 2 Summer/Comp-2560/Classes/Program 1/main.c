#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <dirent.h>
//#include <fcntl.h>


int Program20(int argc, char *argv[]){
    FILE *fd;
    char c;

    if (argc == 1)
        fd = stdin;
    else if ((fd = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "Error opening %s, exiting\n", argv[1]);
        exit(0);
    }
    while ((c = getc(fd)) != EOF) {
        if (c == '/') break;
        putc(c, stdout);
    }
    exit(0);
}

void Program22(){
    printf("Hello, my PID is %d\n", getpid());
    printf("Hello, my PPID is %d\n", getppid());
    exit(0);
}


int main(int argc, char *argv[]) {
    Program20(argc, argv);
    Program22();
}
