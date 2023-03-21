#include <stdio.h>
#include <string.h>

_Bool IsPasswordOkay(void) {
    char Password[12]; //range check
    

    
        return(1); // boolean true or false
    else
        return(0); // boolean true or false
}

int main(void) {

    _Bool PwStatus;
    puts("Enter Password:");
    PwStatus = IsPasswordOkay();
    if (!PwStatus) {
        puts("Access denied");
        return -1;
    }
    else
        puts("Access granted");
    return 0;
}