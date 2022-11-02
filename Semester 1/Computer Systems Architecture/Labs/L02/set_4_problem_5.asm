; [d-2*(a-b)+b*c]/2
; a, b, c - byte
; d- word

bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 5
    b db 3
    c db 8
    d dw 11
    
segment code use32 class=code
start:
    mov bl, [a] ; bl = a
    sub bl, [b] ; bl = a - b
    
    mov al, 2   ; al = 2
    mul bl      ; ax = 2 * (a - b)
    
    mov cx, [d] ; cx = d
    sub cx, ax  ; cx = d - 2 * (a - b)
    
    mov al, [b] ; al = b
    mul byte[c] ; ax = b * c
    
    add cx, ax  ; cx = d - 2*(a - b) + b * c
    mov ax, cx  ; ax = d - 2*(a - b) + b * c
    
    mov bl, 2   ; bl = 2
    div bl      
    
    push dword 0
    
    call [exit]