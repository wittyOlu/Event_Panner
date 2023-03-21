#include <stdio.h>

int main(int argc, char *argv[]) {
    int i =0;
    char buff[10]; //array check
    char *arg1;
    if (argc < 2)
    return -1;
    arg1 = argv[1];
    while (arg1[i] != '\0') {
        buff[i] = arg1[i];
        i++;
    }
    buff[i] = '\0';
    printf("buff = %s\n", buff);
}