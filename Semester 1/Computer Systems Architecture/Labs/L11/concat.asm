bits 32

global concat

segment code:
concat:
    push ebp
    mov ebp, esp
    
    mov esi, [ebp + 0x8]
    ;mov esi, [ebp + 12]
    
    find_empty_space:
        lodsb
        cmp al, 0
        jne find_empty_space
    
    dec esi
        
    mov edi, esi
    mov esi, [ebp + 0xC]
    
    store:
        lodsb
        
        cmp al, 0
        je add_space
        
        stosb
        
        cmp al, '.'
        je end_concat
        
        jmp store
    
    add_space:
        mov al, ' '
        stosb
    
    end_concat:
        pop ebp
        ret