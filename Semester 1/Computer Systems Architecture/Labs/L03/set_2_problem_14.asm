bits 32

global start

extern exit
import exit msvcrt.dll

; c-b-(a+a)-b
; a - byte, b - word, c - dword, d - qword
; signed

segment data use32 class=data:
    a db 12
    b dw 18
    c dd 25
    
segment code use32 class=code:
start:
    mov ax, [b] ; ax = b
    cwde ; eax = b
    
    mov ebx, [c]
    sub ebx, eax ; ebx = c-b
    
    mov al, [a]
    cbw ; ax = a
    cwde ; eax = a
    
    add eax, eax ; eax = a + a
    
    sub ebx, eax ; ebx = c-b-(a+a)
    
    mov ax, [b] ; ax = b
    cwde ;eax = b
    
    sub ebx, eax ; ebx = c-b-(a+a)-b
    
    push dword 0
    call [exit]
    
    
