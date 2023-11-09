%include "printf32.asm"
extern printf

section .data
M dd -20
N dd 90

arr dd -30, -20, -10, 40, 50, 60, 70, 80, 90, 100
len equ 10

section .bss
in_len: resd 1
; TODO b: Declarati variabla de tip `double word` cu numele `in_len`
res: resd len
; TODO c: Declarati vectorul de intregi (`double word`) `res` cu maximum `len` elemente

section .text
    global main

main:
    push ebp
    mov ebp, esp

    ; TODO a: Determinați cum este plasat numarul arr[0] relativ la intervalul [M, N], unde M < N. Afisati:
    ; -1 (arr[0] < M)
    ; 0 (M <= arr[0] <= N)
    ; 1 (arr[0] > N)
    
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    mov eax, [M]    ; eax = M
    mov ecx, [N]    ; ecx = N
    mov edx, [arr]  ; edx = arr[0]
    
    cmp edx, M
    jl mai_mic
    cmp edx, N
    jg mai_mare
    
mijloc:
    mov ebx, 0
    jmp gata_a
    
mai_mic:
    mov ebx, -1
    jmp gata_a
    
mai_mare:
    mov ebx, 1
    jmp gata_a
    
gata_a:
    PRINTF32 `%d\n\x0`, ebx
    ; TODO b: Calculati si afisati numarul elementelor din vectorul `arr` care se gasesc
    ; in intervalul [M, N]. Retineti aceasta valoare in variabila `in_len` din sectiunea `.bss`.

    xor ebx, ebx
    xor edx, edx
    xor esi, esi
    lea edi, [arr]
    lea esi, [len]
    ; mov esi, len   // asemenea
for:
    cmp edx, esi
    je gata_b
    cmp [edi + 4*edx], eax
    jl maimic
    cmp [edi + 4*edx], ecx
    jg maimare
    inc ebx
    inc edx
    jmp for
    
maimic:
    inc edx
    jmp for

maimare:
    inc edx
    jmp for

gata_b:
    mov [in_len], ebx
    push ebx
    push ebx
    PRINTF32 `%d\n\x0`, [in_len]
    
    ; TODO c: Completati vectorul `res` de dimensiune maxima `len` cu elementele din
    ; vectorul `arr` care se gasesc in intervalul [M, N].
    ; Declarati vectorul `res` in sectiunea `bss`.

    xor ebx, ebx
    xor edx, edx
    lea edi, [arr]
    pop esi
for2:
    cmp edx, esi
    je gata_c
    cmp [edi + 4*edx], eax
    jl mic
    cmp [edi + 4*edx], ecx
    jg mare
    push eax
    mov al, [edi + 4*edx]
    ; PRINTF32 `%d\n\x0`, eax
    mov [res + 4*ebx], al
    pop eax
    inc ebx
    inc edx
    jmp for2
    
mic:
    inc edx
    jmp for2

mare:
    inc edx
    jmp for2

gata_c:  
    ; TODO d: Afisati vectorul `res` de dimensiune `in_len` cu elementele
    ; pe aceeasi linie separate de un spatiu

    xor eax, eax
    xor ecx, ecx
    pop ebx
    xor edx, edx
    lea edx, [res]
afisare:
    PRINTF32 `%d \x0`, [edx]
    add edx, 4
    inc eax
    cmp eax, ebx
    je done
    jmp afisare
    
done:
    PRINTF32 `\n\x0`
    ; Return 0.
    xor eax, eax
    leave
    ret
