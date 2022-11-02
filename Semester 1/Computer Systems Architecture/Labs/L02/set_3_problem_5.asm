; a, b, c, d - word
; (c + b + b)-(c + a + d)

bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dw 100
    b dw 53
    c dw 12
    d dw 14
    
segment code use32 class=code
start:
    mov ax, [c] ; ax = c
    add ax, [b] ; ax = c + b
    add ax, [b] ; ax = c + b + b
    
    mov bx, [c] ; bx = c
    add bx, [a] ; bx = c + a
    add bx, [d] ; bx = c + a + d
    
    sub ax, bx  ; ax = (c + b + b) - (c + a + d)
    
    push dword 0
    call [exit]