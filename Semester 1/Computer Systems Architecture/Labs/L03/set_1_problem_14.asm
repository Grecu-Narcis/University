bits 32

global start

extern exit
import exit msvcrt.dll

; (a+d)-(c-b)+c
; a - byte, b - word, c - dword, d - qword
; unsigned

segment data use32 class=data:
    a db 12
    b dw 31
    c dd 87
    d dq 5
    
segment code use32 class=code:
start:
    mov ebx, 0
    mov bl, [a] ; ebx = a
    
    mov eax, [d] 
    mov edx, [d+4] ; edx:eax = d
    
    add eax, ebx
    adc edx, 0 ; edx:eax = (a+d)
    
    mov ecx, [c]
    mov ebx, 0 ; ebx = 0
    mov bx, [b] ; bx = b
    sub ecx, ebx ; ecx = (c-b)
    
    sub eax, ecx
    sbb edx, 0
    
    add eax, [c]
    adc edx, 0
    
    push dword 0
    call [exit]