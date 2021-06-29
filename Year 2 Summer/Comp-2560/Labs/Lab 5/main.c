#include <stdio.h>
#include "stringio.h"
#include "stringArr.h"
#include <string.h>

int main() {
    printf("Hello, World!\n");
    str *string = String("This is a String");
    FILE *fd = fopen("Hello.txt", "r+");
    str *string2 = readToStrStd(fd);
    concatSingle(string, " a");
    concatSingle(string, " Hello");
    writeStrStd(fd, string);
    if (len(string2) != strlen(getStr(string2))) printf("%d, %d\n", len(string2), strlen(getStr(string2)));
    if (len(string) != strlen(getStr(string))) printf("%d, %d\n", len(string), strlen(getStr(string)));
    fclose(fd);

    strArray *arr = Array("");
    append(arr, "Hello");
    append(arr, "Hello2");
    append(arr, "Hello3");
    append(arr, "Hello4");
    append(arr, "Hello5");
    append(arr, "Hello6");
    return 0;
}
