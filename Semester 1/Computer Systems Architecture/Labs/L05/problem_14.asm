bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data:
    s db 1, 3, -2, -5, 3, -8, 5, 0
    lens equ $ - s
    
    d1 resb lens
    d2 resb lens
    
    lend1 dd 0
    lend2 dd 0
    
;A byte string S is given. Obtain the string D1 which contains all the positive numbers of S 
;and the string D2 which contains all the negative numbers of S.
;Example:
;S: 1, 3, -2, -5, 3, -8, 5, 0
;D1: 1, 3, 3, 5, 0
;D2: -2, -5, -8
    
segment code use32 class=code:
start:
    mov ecx, lens
    cmp ecx, 0
    
    jz end_program

    mov esi, 0
    mov edi, 0
    
    add_positive:
        mov al, [s + esi] ; get the current element
        cmp al, 0
        
        jl negative ; if the current element is negative
        
        mov byte [d1 + edi], al
        inc edi
        
        negative:
            
        inc esi
        
        loop add_positive
        
    mov [lend1], edi ; length of d1
    
    cmp edi, lens
    je end_program ; if all elements are positive, then we don't have to look for negative numbers
    
    mov esi, 0
    mov edi, 0
    
    add_negative:
        mov al, [s + esi]
        cmp al, 0
        
        jge positive ; if current number is >= 0
        
        mov [d2 + edi], al
        inc edi
        
        positive:
            inc esi
            
            cmp esi, lens
            jb add_negative  
        
    mov [lend2], edi
    
    end_program:
        push dword 0
        call [exit]
    