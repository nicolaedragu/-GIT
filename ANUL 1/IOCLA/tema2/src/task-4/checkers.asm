
section .data

section .text
	global checkers
    extern printf

checkers:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table

    ;; DO NOT MODIFY
    ;; FREESTYLE STARTS HERE

    ; ecx + 8 * eax + ebx = Pozitia piesei in tabel
    
    ; creare index linie
    xor edx, edx
    mov edx, 8
    mul edx
    ; initializare index pentru linia pe care se va deplasa dama
    ; linia de deasupra sau de dedesubt
    ; pentru edi = 8, dama se poate muta deasupra
    mov edi, 8
    
    ; verificare daca dama se afla pe ultima linie
    cmp eax, 8 * 7
    je ultima_linie
    
scriere:
    ; creare index
    xor edx, edx
    mov edx, ecx
    add edx, eax
    add edx, ebx
    ; adunare index pentru linia pe care se va deplasa dama
    add edx, edi
    ; daca dama se afla in stanga tablei,
    ; fapt ce implica deplasarea ei in dreapta
    cmp ebx, 0
    je  peste
    mov byte [edx - 1], 1
peste:
    ; daca dama se afla in dreapta tablei,
    ; fapt ce implica deplasarea ei in stanga
    cmp ebx, 7
    je scris_destul
    mov byte [edx + 1], 1
scris_destul:
; daca tocmai s-a efectuat traseul damei ce se afla pe ultima linie
    cmp edi, -8
    je out
; pana acum s-a determinat si marcat posibilitatea damei de a inainta
; daca dama se afla pe prima linie, ea nu se poate duce in jos
    cmp eax, 8 * 0 
    je out
    
ultima_linie:
; se va scrie doar pe linia de dedesubt
    mov edi, -8
    jmp scriere
    
out:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY