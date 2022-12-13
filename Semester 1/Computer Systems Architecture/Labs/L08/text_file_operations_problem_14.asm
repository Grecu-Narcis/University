bits 32

global start

extern exit, fopen, fprintf, fclose

import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class = data
    filename db 'fisier.txt', 0
    access_mode db 'w', 0
    format db '%s', 0
    text db 'AnAareMERE23', 0
    len_text equ $ - text
    
    file_descriptor resd 1
    
segment code use32 class = code
start:
    mov esi, text
    mov edi, text
    
    cld
    
    mov ecx, len_text
    
    parse_text:
        lodsb
        
        cmp al, 'A'
        jb no_change
        
        cmp al, 'Z'
        jg no_change
        
        sub al, 'A' ; al = al - 'A'
        add al, 'a'
        
        no_change:
            stosb
        
        loop parse_text
        
    push dword access_mode
    push dword filename
    call [fopen]
    
    add esp, 4 * 2
    
    cmp eax, 0
    je final
    
    mov [file_descriptor], eax
    
    push dword text
    push dword format
    push dword [file_descriptor]
    call [fprintf]
    
    add esp, 4 * 3
    
    push dword [file_descriptor]
    call [fclose]
    
    add esp, 4
    
    final:
        push dword 0
        call [exit]