%include "utils/printf32.asm"

section .data
    num dd 55555123
;;  TODO d: declare byte_array so that PRINT_HEX shows babadac 
    byte_array db 20
    string_format db '%s', 10, 0
	string_b db "123456789" , 0
    
section .text
global main
extern printf

; TODO b: implement array_reverse
array_reverse:
    push ebp
    mov ebp, esp
    
    mov eax, dword [ebp + 8]    ; char *
    mov ebx, dword [ebp + 12]   ; length
    
    xor ecx, ecx
    
loop_push:
    push word [eax + ecx]   ; push cate 2 litere
    inc ecx
    
    cmp ecx, ebx
    jl loop_push
    
    xor ecx, ecx
    xor edx, edx
loop_pop:
    pop dx
    xor dh, dh
    
    ; interschimbare cu 3 xor-uri
    
    xor byte [eax + ecx], dl    ; interschimba byte [eax + ecx], dl
    xor dl, byte [eax + ecx]
    xor byte [eax + ecx], dl
    
    inc ecx
    cmp ecx, ebx
    jl loop_pop
    
    leave
    ret
    
; TODO c: implement pow_arraypowArray
pow_array:

main:
    push ebp
    mov ebp, esp

    ;TODO a: allocate on array of 20 byte elements and initializate it incrementally starting from 'A'

    sub esp, 21
    xor ecx, ecx
    xor edx, edx

    mov dl, 'A'

loop_a:
    mov [esp + ecx], dl
    inc ecx
    inc edx
    
    cmp ecx, 20
    jl loop_a
    
    push esp
    push string_format
    call printf
    add esp, 8

    ;TODO b: call array_reverse and print reversed array
    push 10
    push string_b
    call array_reverse
    add esp, 8
    
    xor ecx, ecx
    
loop_print:
    mov ebx, [string_b + ecx]
    PRINTF32 `%c\x0`, ebx
    inc ecx
    cmp ecx, 10
    jl loop_print
    PRINTF32 `\n\x0`
    
    ;TODO c: call pow_array and print the result array

	;;  TODO d: this print of an uint32_t should print babadac 
	;; PRINTF32 `%x\n\x0`, byte_array 

    xor eax, eax
    leave
    ret
