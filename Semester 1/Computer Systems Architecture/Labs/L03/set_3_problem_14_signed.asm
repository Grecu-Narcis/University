bits 32

global start

extern exit
import exit msvcrt.dll

; x+(2-a*b)/(a*3)-a+c; a-byte; b-word; c-doubleword; x-qword

segment data use32 class=data:
    a db 25
    b dw 43
    c dd 173
    x dq 3428
    
segment code use32 class=code:
start:
    mov byte [a], 500
    cbw ; ax = a
    
    imul word[b] ; dx:ax = a*b
    
    push dx
    push ax
    pop eax ; eax = a*b
    
    mov ebx, 2
    sub ebx, eax ; ebx = 2 - a*b
    
    mov al, 3
    imul byte[a] ; ax = a*3
    
    mov cx, ax ; cx = a*3
    
    push ebx
    pop ax
    pop dx ; dx:ax = (2-a*b)
    
    idiv cx ; ax = (2-a*b)/(a*3)
    
    cwde
    cdq ; edx:eax = (2-a*b)/(a*3)
    
    add eax, [x]
    adc edx, [x+4] ; edx:eax = x+(2-a*b)/(a*3)
    
    mov ebx, eax
    mov ecx, edx ; ecx:ebx = x+(2-a*b)/(a*3)
    
    mov al, [a]
    cbw
    cwde
    cdq ; edx:eax = a
    
    sub ebx, eax
    sbb ecx, edx ; ecx:ebx = x+(2-a*b)/(a*3)-a
    
    mov eax, [c]
    cdq ; edx:eax = c
    
    add ebx, eax
    adc ecx, edx ; ecx:ebx = x+(2-a*b)/(a*3)-a+c
    
    push dword 0
    call [exit]