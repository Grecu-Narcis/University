bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a db 2
    b dw 1
    c dd 23
    x dq 100
    
    
; x+(2-a*b)/(a*3)-a+c; a-byte; b-word; c-doubleword; x-qword

segment code use32 class=code
start:
    mov al, [a]
    mov ah, 0
    
    mul word[b] ; dx:ax = a * b
    
    push dx
    push ax
    pop eax
    
    mov ebx, 2
    
    sub ebx, eax ; ebx = 2 - a*b

    mov al, 3
    mul byte[a] ; ax = a*3
    
    mov cx, ax ; cx = a*3
    
    push ebx
    pop ax
    pop dx ; dx:ax = 2-a*b
    
    div cx ; ax = (2-a*b)/(a*3)
    
    mov ebx, 0
    mov bx, ax ; ebx = (2-a*b)/(a*3)
    mov ecx, 0 ; ecx:ebx = (2-a*b)/(a*3)
    
    add ebx, [x]
    adc ecx, [x+4] ; ecx:ebx = x+(2-a*b)/(a*3)
    
    mov eax, 0
    mov al, [a] ; eax = a
    
    sub ebx, eax
    sbb ecx, 0 ; ecx:ebx = x+(2-a*b)/(a*3)-a
    
    add ebx, [c]
    adc ecx, 0
    
    push dword 0
    
    call [exit]