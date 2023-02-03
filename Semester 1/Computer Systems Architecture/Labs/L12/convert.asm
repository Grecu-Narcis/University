bits 32

global _convert

segment code:
_convert:
    ; this function will convert a base 2 integer to a base 10 one    
    push ebp
    mov ebp, esp
        
    ; [ebp + 8] -> number in base 2
    
    mov eax, [ebp + 8]
    
    ; we will construct the number in base 10 in ebx
    mov ebx, 0
    ; in ecx we will store powers of 2
    mov ecx, 1
    
    get_digit:
        mov edx, 0
        mov esi, 10
        
        div esi
        
        ; edx = last digit in base 2
        
        cmp edx, 0
        je no_add
        
        add ebx, ecx
        
        no_add:
            shl ecx, 1
            cmp eax, 0
            
            jne get_digit
                
    pop ebp
    
    mov eax, ebx
    
    ret
        