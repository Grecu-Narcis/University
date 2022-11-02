bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data:
    a dd 10010111000110100100011100101111b
    b dd 10110000010011011010010111110010b
    
    ;    10011011010010111110010000000000b
    ; bits 1-6 are 0's
    ; bit 17 is 1
    ; bit 18 is 0
    ; c should be 01000000b = 64
    c db 0
    
;Given the doubleword A, obtain the integer number n represented on the bits 14-17 of A. 
;Then obtain the doubleword B by rotating A n positions to the left. 
;Finally, obtain the byte C as follows:
;the bits 0-5 of C are the same as the bits 1-6 of B
;the bits 6-7 of C are the same as the bits 17-18 of B
    
segment code use32 class=code:
start:
    mov eax, [a]
    and eax, 111100000000000000b ; isolate bits 14-17
    shr eax, 14 ; get the bits on the low part
    
    mov cl, al ; get the value of n`
    
    mov ebx, [b]
    shl ebx, cl ; shift b with n position to the left
    
    mov eax, ebx
    
    and eax, 1111110b ; isolate bits 1-6
    shr eax, 1 ; get the bits in position 0-5 to put them in c
    
    or [c], al ; put the bits in c
    
    mov eax, ebx
    
    and eax, 1100000000000000000b ; isolate bits 17-18
    shr eax, 11 ; get them on position 6-7 to put them in c
    
    or [c], al ; put the bits in c
    
    ; mov c in a register to see the value
    mov dl, [c] ; 01000000b
    
    push dword 0
    
    call [exit]
    