%include "printf32.asm"
extern printf

section .data

M dw 1000
N dw 700

arr1 dw 1000, 1000, 30, 40, 50, 60, 70, 80, 90, 100
arr2 dw 90, 100, 90, 50, 40, 30, 20, 10, 60, 100
len equ 10

section .bss
    res: resd len
; TODO c: Alocati memorie pentru vectorul `res` cu elemente de tip double word si dimensiunea egala cu `len`

section .text

global main

main:
    push ebp
    mov ebp, esp

; TODO a: Calculati si afisati produsul numerelor reprezentate pe 2 octeti (word) M si N.
    ; Sugestie: Pentru inmultire puteti folosi instructiunea `mul` care:

    xor edx, edx
    xor eax, eax
    xor ebx, ebx
    mov ax, word[M]
    mov bx, word[N]
    mul bx
    shl edx, 16
    or eax, edx
    PRINTF32 `%u\n\x0`, eax

    ;   - primeste primul operand in registrul AX
    ;   - primeste al doilea operand intr-un registru pe 16 biti / memorie de 16 biti
    ;   - intoarce rezultatul in DX:AX
    ;   - pe scurt, DX : AX = AX * r/m16.




; TODO b: Calculati si afisati produsul scalar al vectorilor arr1 si arr2
    ;   - P = arr1[0] * arr2[0] + arr1[1] * arr2[1] + ... arr1[i] * arr2[i] + ...
    ;   - este garantat ca P nu depaseste dimensiunea unui double word (4 octeti)
    push esi
    push edi
    mov esi, arr1
    mov edi, arr2
    mov ecx, len
    xor edx, edx  ; P

bucla1:
    push edx
    xor eax, eax
    mov ax, word[arr1 + 2 * (ecx - 1)]
    mov bx, word[arr2 + 2 * (ecx - 1)]
    mul bx
    shl edx, 16
    or eax, edx
    pop edx
    add edx, eax
    loop bucla1

    PRINTF32 `%u\n\x0`, edx


    pop edi
    pop esi

; TODO c: Completati vectorul `res` cu elemente de tip double word de dimensiune `len`  astfel incat
    ; fiecare element sa fie egal cu produsul elementelor corespunzatoare din vectorii `arr1` si `arr2`.
    ; - e.g: res[i] = arr1[i] * arr2[i]

    mov ecx, len
bucla2:
    xor eax, eax
    xor ebx, ebx
    xor edx, edx
    mov ax, word[arr1 + 2 * (ecx - 1)]
    mov bx, word[arr2 + 2 * (ecx - 1)]
    mul bx
    shl edx, 16
    or eax, edx
    mov dword[res + 4 * (ecx - 1)], eax
    loop bucla2

    ;PRINTF32 `%u\n\x0`, edx


    ; TODO d: Afisati vectorul `res` cu elemente de tip double word de dimensiune `len` calculat la punctul c)

    mov ecx, len
    xor edx, edx
bucla3:
    xor eax, eax
    ; mov eax, dword[res + 4 * (ecx - 1)]
    mov eax, dword[res + 4 * edx]
    PRINTF32 `%u \x0`, eax
    inc edx
    loop bucla3
    PRINTF32 `\n\x0`

    ; Return 0.
    xor eax, eax
    leave
    ret
