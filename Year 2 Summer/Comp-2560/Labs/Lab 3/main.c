//filesize1v.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x8000 ? '1' : '0'), \
  (byte & 0x4000 ? '1' : '0'), \
  (byte & 0x2000 ? '1' : '0'),                            \
  (byte & 0x1000 ? '1' : '0'), \
  (byte & 0x800 ? '1' : '0'), \
  (byte & 0x400 ? '1' : '0'), \
  (byte & 0x200 ? '1' : '0'), \
  (byte & 0x100 ? '1' : '0'), \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

long long Pow(int num, int power){
    long long newNum = (long long) num;
    if (power == 0 && num != 0) return 1;
    else if (power == 0 && num == 0) return 0;
    for (int i = 1; i < power; i++){
        newNum *= num;
    }
    return newNum;
}

char *bin(signed int num, int binaryLength){
    char *binary = (char*) malloc((binaryLength+1) * sizeof(char));
    long long signed numChange = num;
    int neg = 0;
    if (num < 0){
        neg = 1;
        numChange *= -1;
        numChange--;
        num *= -1;
    } else if (num == 0) {
        for (int i = 0; i < binaryLength; i++) {
            binary[i] = '0';
        }
    }
    for (int i = 0; i <= binaryLength; i++){
        if(Pow(2, binaryLength-i-1) > numChange){
            if (neg){
                binary[i] = '1';
            }
            else{
                binary[i] = '0';
            }
        }
        else{
            if (neg) binary[i] = '0';
            else binary[i] = '1';
            numChange -= Pow(2, binaryLength-i-1);

        }
    }
    binary[binaryLength] = '\0';
    return binary;
}

int main(int argc, char *argv[]){
    FILE *fd;
    printf("%ld", 10L);
    exit(0);
    printf("Binary: %s\n\n", bin((unsigned char) '1', 8));
    printf("Binary: %s\n\n", bin((signed char) '1', 8));
    printf("Binary: %s\n\n", bin(49, 8));
    printf("Binary: %s\n\n", bin(-100, 8));
//    printf("Leading text "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(-1));
//    printf("Leading text "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(-2));
//    printf("Leading text "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(-3));
//    printf("Leading text "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(-4));
//    printf("Leading text "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(-5));
//    printf("Leading text "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(-6));
    for (signed int i = 100; i >= -100; i--){
        printf("%d: \t"BYTE_TO_BINARY_PATTERN"\t%s\n", i, BYTE_TO_BINARY(i), bin(i, 16));
    }
    exit(0);
    //unsigned char ch;  //what will happen if you uncomment this line and comment the 		//next line
    //signed int ch;
    char ch;
    int fileSize=-1;
    char argue[] = {"textFile.txt"};
    //fd = fopen(argv[1], "r");
    fd = fopen(argue, "r");
    printf("%d\n", sizeof(int));
    do{
        ch=getc(fd);  //0xFF
        fileSize++;
        printf("fileSize=%d\n", fileSize);
        printf("Char read is ch=%c, in hex ch=%#hhx EOF is %#x, Number is: %d, ", ch, ch, EOF, ch);
        printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(ch));
        printf("\n\n");
        sleep(1);
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(ch));
        printf("\t");
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((unsigned char)ch));
        //printf("%hhi, %hhi\n\n", (char) ch, (unsigned char) ch);
    } while(ch != EOF);  //ch =0x FF,  EOF=0x FFFF FFFF
    printf("%c, %d", EOF, EOF);
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((-1)));
    printf(" \nout of do while loop now.\n\n");
    printf("ch=%d EOF=%#x\n", ch, EOF);
    printf("size of char =%ld size of EOF=%ld\n", sizeof(char), sizeof(EOF));

    printf("Size of %s is %d\n", argv[1], fileSize);
}

//suggeson: levae all the printf statment in place
//run the code to observe the output
//then use gdb to find out the "bug"

/**
//filesize2.c
#include <stdio.h>


int main(int argc, char *argv[]){
    FILE *fd;

    char ch;

    int fileSize=-1;

    fd = fopen(argv[1], "r+");

    // fseek(fd, 10L, SEEK_SET);
    // putc(-1, fd);
    // rewind(fd);                 //try uncomment this block, to see what it does.

    do{
        ch=getc(fd);
        fileSize++;
        printf("fileSize=%d\n", fileSize);
    } while( ch != EOF);

    printf("Size of %s is %d\n", argv[1], fileSize);
}
*/