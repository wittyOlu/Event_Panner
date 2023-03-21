#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getComment(unsigned int len, char *src) {
    unsigned int size;
    size = len-2; // a signed variable of -1 is stored in a signed memory for a while
    char *comment = malloc(size + 1); // creating an array for no reason
    memcpy(comment, src, size); //trying to 
/* 
    carry out a range check here, using if, range and abort.
*/

    printf("%s\n", comment);
}

int main (void) {
    
    getComment(1, "Nextweek Practical");

    return 0;
}