bits 32

global start

extern exit, printf, scanf
extern concat

import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data:
    int_format db "%d", 0
    string_format db "%s", 0
    
    n resd 1
    cuvant times 20 db 0
    prop times 100 db 0

segment code:
start:
    push dword n
    push dword int_format
    
    call [scanf]
    add esp, 4*2
    
    mov ecx, [n]
    mov edx, 1 ; store the number of current sentence
    cld
    
    mov ebx, 0 ; store the number of the current word
    
    read_sentence:
        read_word:
            pushad
            
            ; read the word
            push dword cuvant
            push dword string_format
            
            call [scanf]
            add esp, 4*2
            
            popad
            
            add ebx, 1
            cmp ebx, edx ; check if this is the word we want from the current sentence
            
            jne check_for_dot
            
            push dword cuvant
            push dword prop
            
            call concat
            add esp, 4*2
            
            check_for_dot: ; check if the word contain '.', meaning that we move to the next sentence
                push ecx
                mov ecx, 20
                mov esi, cuvant
                loop_dot:
                   lodsb
                   cmp al, '.'
                   
                   je end_of_sentence
                   
                   loop loop_dot
            
            mov ecx, 20
            mov edi, cuvant
            mov al, 0
            fill: ; restoring the memory area to 0 for the next word
                stosb
                loop fill
                
            pop ecx
            jmp read_word
            
            end_of_sentence: 
                mov ebx, 0
                add edx, 1
                
                mov ecx, 20
                mov edi, cuvant
                mov al, 0
                fill_1:
                    stosb
                    loop fill_1
                    
                pop ecx
                
                loop read_sentence
    
    push dword prop
    push dword string_format
    
    call [printf]
    
    add esp, 4*2
    
    push dword 0
    call [exit]                  
               