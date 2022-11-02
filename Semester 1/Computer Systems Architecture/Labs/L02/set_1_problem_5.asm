; compute 10/4
; 2 bytes / 1 byte
; dividend in 2 bytes => ax
; divisor in 1 byte => bl

bits 32

global start

extern exit
import exit msvcrt.dll

segment code use32 class=code
start:
    mov ax, 10
    mov bl, 4
    div bl
    
    push dword 0
    call [exit]