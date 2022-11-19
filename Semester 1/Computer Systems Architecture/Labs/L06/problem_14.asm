bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data:
    s dd 12345607h, 1a2b3c15h
    len_s equ ($-s)/4 ; we divide by 4 because s contains dwords
    d times len_s*4 db 0 ; for every element in s we have 4 elements in d (1 dword = 4 bytes)
    len_d equ $-d


;Given an array S of doublewords, build the array of bytes D 
;formed from bytes of doublewords sorted as unsigned numbers in ascending order.
;Example:
; s DD 12345607h, 1A2B3C15h
; d DB 07h, 12h, 15h, 1Ah, 2Bh, 34h, 3Ch, 56h


segment code use32 class=code:
start:
    mov esi, s
    mov edi, d
    
    mov ecx, len_d
    cmp ecx, 0
    jz end_program
    
    cld

    add_bytes:
        lodsb ; al = [esi], esi += 1
        stosb
        
        loop add_bytes
        
    ; here we sort the string d
    mov ebx, 0 ; flag to know if we did any swaps
    
    cld
    first_loop:
       mov ebx, 0
       
       mov esi, d
       mov ecx, len_d - 1
       
       second_loop:
        mov al, [esi] ; al = d[0]
        mov ah, [esi + 1] ; ah = d[1]
        
        cmp al, ah
        jbe no_swap
        
        xchg al, ah
        mov [esi], al
        mov [esi + 1], ah
        mov ebx, 1
        
        no_swap:
            inc esi ; go on the next element
            loop second_loop
            
            cmp ebx, 0
            jnz first_loop
        
    end_program:
        push dword 0
        call [exit]