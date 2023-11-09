extern printf
section .data

arr dd  1331, 1441, 1551, 1661, 1771, 1881, 1991, 2002, 2022, 1337
len equ 10
int_fmt db '%d ', 0
int_fmt_newline db '%d', 10, 0
NEWLINE db 10, 0

TEN     dd 10

section .bss
ans resd len

section .text
global main

; TODO a: Implementati functia `void print_array(int *arr, int n) care afiseaza
;   elementele numere intregi ale vectorului `arr` de dimensiune n.
;   Toate elementele vor fi afisate pe aceeasi linie separate de un spatiu.
;   La finalul afisarii se va insera NEWLINE. Vezi sectiunea .data
;   functia `printf` poate modifica registrele EAX, ECX si EDX.

print_array:
    push ebp
    mov ebp, esp



    leave
    ret


;TODO b: Implementati functia `int sum_digits(n)` care intoarce suma cifrelor numarului
;   intreg fara semn `n`.
;   e.g:
;       -sum_digits(123456) = 1+2+3+4+5+6 = 21
;       -sum_digits(100) = 1+0+0 = 1
sum_digits:
    push ebp
    mov ebp, esp



    leave
    ret

; TODO c: Implementati functia `void sum_digits_arr(int *arr, int len, int *out_arr)
; care actualizeaza fiecare element din vectorul `out_arr` cu suma cifrelor elementului
; corespunzator din vectorul `arr` de dimensiunea `len`.
; out_arr[i] = sum_digits(arr[i])
; ATENTIE la registrii pe care functia `sum_digits` ii modifica.
sum_digits_arr:
    push ebp
    mov ebp, esp


    leave
    ret

;TODO d: Implementati functia `int reverse(int a)` care intoarce rasturnatul
; unui numar intreg fara semn. Rasturnatul este numarul obtinut din citirea
; numarului initial de dreapta la stanga.
; e.g:
;       - reverse(123456) = 654321
;       - reverse(300000) = 3
;       - reverse(10002)  = 20001
reverse:
    push ebp
    mov ebp, esp



    leave
    ret

main:
    push ebp
    mov ebp, esp

    ;TODO a: Afisati folosind functia `print_array` vectorul `arr` de dimensiune `len`.



    ;TODO b: Apelati functia `sum_digits` pentru numerele intregi `123456` si `202020`. Afisati rezultatul
    ;folosind functia `printf`. Fiecare rezultat fiind afisat pe o linie noua.




    ; TODO c: Apelati functia `sum_digits_arr` pentru a calcula suma cifrelor numerelor din vectorul `arr` de dimensiune `len`.
    ; Salvati rezultatul in vectorul `ans` alocat in sectiunea `.bss`
    ; Afisati apoi vectorul `ans` folosind functia `print_array` implementata la TODO a.



    ; TODO d: Apelati functia `reverse` pentru a calcula rasturnatul numerelor intregi fara semn `123456` si `100`. Afisati
    ; apoi fiecare rezultat pe o linie noua.



    xor eax, eax
    leave
    ret
