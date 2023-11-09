%include "utils/printf32.asm"

section .data
    num dd 55555123

section .text
    global main
    extern printf

main:
    push ebp
    mov ebp, esp
  
    ;TODO a: print least significant 2 bits of the second most significant byte of num
    
    mov eax, [num]
    shr eax, 16
    and eax, 0x03
    
    cmp eax, 0x00 
    je print_00
    
    cmp eax, 0x01 
    je print_01

    cmp eax, 0x02 
    je print_10

    cmp eax, 0x03
    je print_11

print_00:
    PRINTF32 `%d%d\n\x0`, 0, 0
    jmp finish_a

print_01:
    PRINTF32 `%d%d\n\x0`, 0, 1
    jmp finish_a

print_10:
    PRINTF32 `%d%d\n\x0`, 1, 0
    jmp finish_a
    
print_11:
    PRINTF32 `%d%d\n\x0`, 1, 1
    jmp finish_a
    
finish_a:
    ;TODO b: print number of bits set on odd positions
    
    xor ebx, ebx    ; contorul pt biti
    xor ecx, ecx
    xor edx, edx    ; nr care contine puterile lui 2
    
    add ecx, 15
    
    add edx, 0x01
    mov eax, [num]

    and eax, edx
    jz loop_b

    inc ebx

loop_b:
    shl edx, 2
    mov eax, [num]
    
    and eax, edx
    jz continue_loop_b
    
    inc ebx
    
continue_loop_b:
    loop loop_b
    
    PRINTF32 `%d\n\x0`, ebx

    ;TODO c: print number of groups of 3 consecutive bits set

    xor edi, edi    ; contor de biti de 1 unul langa altul
    xor ebx, ebx    ; contor de grupari de biti de 1
    xor edx, edx    ; masca noastra pentru and

    add edx, 0x01
    mov eax, [num]
    and eax, edx
    jz loop_c
    
    inc edi 
    
loop_c:
    shl edx, 1
    mov eax, [num]
    and eax, edx
    jz not_1
     
    inc edi
    cmp edi, 3
    jne continue_loop_c
    
    inc ebx
    dec edi
    jmp continue_loop_c
    
not_1:
    xor edi, edi
    
continue_loop_c:
    loop loop_c
    
    PRINTF32 `%d\n\x0`, ebx     ; dureaza vreo 10 s sa ruleze 

    xor eax, eax
    leave
    ret
