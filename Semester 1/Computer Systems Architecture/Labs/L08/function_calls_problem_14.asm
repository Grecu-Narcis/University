bits 32

global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class = data:
    read_a_format db "%x", 0
    read_b_format db "%x", 0
    print_format db "%d", 0
    
    a resd 1
    b resd 1

segment code use32 class = code:
start:
    push a
    push read_a_format
    call [scanf]
    
    push dword 0
    call [exit]
    