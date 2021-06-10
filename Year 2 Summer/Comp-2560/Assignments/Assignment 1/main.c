#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int openFile(char file[], char openChar){
    int fd = open(file, openChar);
    return fd;
}
int openNewFileWrite(char file[]){
    int fd = open(file, O_CREAT|O_WRONLY|O_TRUNC);
    return fd;
}


int lseekQuestion(int argc, char *argv[]){
    if (argc == 1) {
        printf("Did Not Receive File Name\n");
        exit(0);
    }
    int fd = openFile(argv[1], 'r');
    printf("The Size of the file Given is: %ld\n", lseek(fd, 0, SEEK_END));
    close(fd);
    return 0;
}


int writerSys(int argc, char *argv[]){
    char lines[] = {"101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005\n"};
    int fd = open("list1.txt", O_CREAT|O_WRONLY|O_TRUNC, 0700);
    if (fd == -1){printf("Ya Couldn't find your File, Sorry!!! :> \n");}
    write(fd, &lines, strlen(lines));
    close(fd);

    return 0;
}

int writerStand(int argc, char *argv[]){
    char lines[] = {"101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005\n"};
    FILE *fd = fopen("list2.txt", "w");
    if (fd == NULL) {printf("Ya Couldn't find your File, Sorry!!! :> \n");}
    fwrite(&lines, 1, strlen(lines), fd);
    fclose(fd);
    return 0;
}

int findLineCountSys(int argc, char *argv[]){
    int fd = open("main.c", 'r');
    char buffer;
    long ch = 0;
    int foundLines = 0;
    while ((ch = read(fd, &buffer, 1)) > 0) if (buffer == '\n') foundLines++;
    return foundLines+1;
}

int findLineCountStand(int argc, char *argv[]){
    FILE *fd = fopen("main.c", "r");
    long ch = 0;
    int foundLines = 0;
    while ((ch = getc(fd)) > 0) if (ch == '\n') foundLines++;
    return foundLines+1;
}

int appendEnd(int fd, char stringToAdd[]){

}

int Question6(int argc, char *argv[]){
    char txtFile[] = {"Thistxt.txt"};
    int fd = open(txtFile, O_RDWR);
}

int main(int argc, char *argv[]) {
    //lseekQuestion(argc, argv);
    writerSys(argc, argv);
    writerStand(argc, argv);
    printf("%d\n", findLineCountSys(argc, argv));
    printf("%d\n", findLineCountStand(argc, argv));
}