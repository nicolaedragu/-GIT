%include "printf32.asm"
extern printf

section .data
M dd -20
N dd 90

arr dd -30, -20, -10, 40, 50, 60, 70, 80, 90, 100
len equ 10

section .bss

; TODO b: Declarati variabla de tip `double word` cu numele `in_len`
in_len: resd 1
; TODO c: Declarati vectorul de intregi (`double word`) `res` cu maximum `len` elemente
res:    resd len


section .text
global main

main:
    push ebp
    mov ebp, esp

    ; TODO a: Determinați cum este plasat numarul arr[0] relativ la intervalul [M, N], unde M < N. Afisati:
    ; -1, daca numarul arr[0] se afla la stanga intervalului (arr[0] < M)
    ; 0, daca numarul arr[0] se gaseste in intervalul [M, N] (M <= arr[0] <= N)
    ; 1, daca numarul arr[0] se gaseste la dreapta intervalului (arr[0] > N)


    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    mov eax, [arr]
   ; PRINTF32 `%d\n\x0`, eax
    mov ebx, [M]
    mov ecx, [N]
  ;  PRINTF32 `%d %d\n\x0`, ebx, ecx
    cmp eax, ebx
    jl sub
    jmp c2


sub:
    mov eax, -1
    jmp exit

c2:
    cmp eax, ecx
    jg peste
    jmp intre

peste:
    mov eax, 1
    jmp exit

intre:
    mov eax, 0
    jmp exit

exit:
    PRINTF32 `%d\n\x0`, eax 

    ; TODO b: Calculati si afisati numarul elementelor din vectorul `arr` care se gasesc
    ; in intervalul [M, N]. Retineti aceasta valoare in variabila `in_len` din sectiunea `.bss`.

    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    
    mov ebx, [M]
    mov ecx, [N]
    lea eax, [arr]

comp:
    cmp [eax], ebx
    jl cont
    cmp [eax], ecx
    jle incr
    cmp [eax], ecx
    jg  ext

incr:
    inc edx
    add eax, 4
    jmp comp

cont:
    add eax, 4
    jmp comp    

ext:
    mov [in_len], edx

    PRINTF32 `%d\n\x0`, [in_len]

    ; TODO c: Completati vectorul `res` de dimensiune maxima `len` cu elementele din
    ; vectorul `arr` care se gasesc in intervalul [M, N].
    ; Declarati vectorul `res` in sectiunea `bss`.

    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    xor edi, edi
    xor esi, esi

    lea edx, [res]
    lea eax, [arr]
    mov ebx, [M]
    mov ecx, [N]


lop:
    cmp [eax], ebx
    jl cnt
    cmp [eax], ecx
    jg extt
    ;PRINTF32 `%d\n\x0`, [eax]
    mov edi, [eax]
    ;PRINTF32 `%d\n\x0`, edi
    mov [edx], edi
    add edx, 4
    add eax, 4
    inc esi
    jmp lop

cnt:
    add eax, 4
    jmp lop


extt:
    mov ecx, esi
    PRINTF32 `%d\n\x0`, [edx]


    ; TODO d: Afisati vectorul `res` de dimensiune `in_len` cu elementele
    ; pe aceeasi linie separate de un spatiu

    lea edx, [res]
prt:
    PRINTF32 `%d \x0`, [edx]
    add edx, 4

    loop prt
    PRINTF32 `\n\x0`


    ; Return 0.
    xor eax, eax
    leave
    ret
