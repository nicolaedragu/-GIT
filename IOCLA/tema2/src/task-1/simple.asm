%include "../include/io.mac"

section .text
    global simple
    extern printf

simple:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     ecx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; plain
    mov     edi, [ebp + 16] ; enc_string
    mov     edx, [ebp + 20] ; step

    ;; DO NOT MODIFY
   
    ;; Your code starts here
    
; Prima litera din cuvant, eax-ul este indexul
    mov eax, dword [ebp + 12]
incrementare_char:
; Initializare prima litera din cuvant intr-o valoare ce va fi modificata
    mov bl, byte [eax]
; Daca s-a ajuns la sfarsitul sirului, se termina programul
; Singura cale de a ajunge la sfarsitul problemei
    cmp bl, 0
    je out
prag:
; Daca pragul este mai mare decat 26
; Se fac scaderi repetate pana se ajunge la o valoare mai mica decat 26
    cmp edx, 26
    jle prag_done
    sub edx, 26
    jmp prag
    
prag_done:
; Se transforma litera in functie de prag
    add bl, dl
    
prag_reusit:
    cmp bl, 'Z'
    jle litera
; Daca a trecut de 'Z', se repeta alfabetul
    sub bl, 26
    jmp prag_reusit
    
litera:
    mov byte [edi], bl
    inc edi
sari:
    inc eax
    cmp eax, ecx
    jle incrementare_char
    
out:
    ;; Your code ends here
    
    ;; DO NOT MODIFY

    popa
    leave
    ret
    
    ;; DO NOT MODIFY
