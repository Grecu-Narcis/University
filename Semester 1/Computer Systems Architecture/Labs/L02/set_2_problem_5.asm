; a, b, c, d - bytes
; (c - a - d) + (c - b) - a

; (10 - 6 - 7) + (10 - 3) - 6 = -3 + 7 - 6 = -2

bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 6
    b db 3
    c db 10
    d db 7
    
segment code use32 class=code
start:
    mov al, [c] ; al = c
    sub al, [a] ; al = c - a
    sub al, [d] ; al = c - a - d
    
    mov bl, [c] ; bl = c
    sub bl, [b] ; bl = c - b
    
    add al, bl  ; al = (c - a - d) + (c - b)
    sub al, [a] ; al = (c - a - d) + (c - b) - a
    
    push dword 0
    
    call [exit]