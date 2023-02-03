bits 32

global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class = data:
    read_format db "%x", 0
    print_format db "%d", 0
    a resd 1
    b resd 1
    rez resd 1

segment code use32 class = code:
start:
    push a
    push read_format
    call [scanf]
    
    add esp, 4*2
    
    push b
    push read_format
    call [scanf]
    
    add esp, 4*2
    
    mov eax, [a]
    add eax, [b]
    
    mov [rez], eax
    
    push dword [rez]
    push print_format
    
    call [printf]
    
    add esp, 4*2
    
    push dword 0
    call [exit]
    