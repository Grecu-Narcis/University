; a*(b+c)+34
; a, b, c - byte

bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 5
    b db 3
    c db 7
    
segment code use32 class=code
start:
    mov bl, [b] ; bl = b
    add bl, [c] ; bl = b + c
    
    mov al, [a] ; al = a
    mul bl ; ax = a * (b + c)
    
    add ax, 34; ax = a * (b + c) + 34
    
    push dword 0
    call [exit]