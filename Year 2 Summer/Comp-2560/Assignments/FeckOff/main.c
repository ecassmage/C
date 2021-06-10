#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "str.h"

int main() {
    char word[] = {"TXTFILE.txt"};
    int fd = open(word, O_RDWR);
    printf("%d\n", SEEK_END);
    printf("%ld\n", lseek(fd, 0, SEEK_END));
    return 0;
}







