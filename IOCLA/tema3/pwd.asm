section .data
    back db "..", 0
    curr db ".", 0
    slash db "/", 0
    ; declare global vars here

section .text
    global pwd

;;	void pwd(char **directories, int n, char *output)
;	Adauga in parametrul output path-ul rezultat din
;	parcurgerea celor n foldere din directories
pwd:
    enter 0, 0

    push ebp
    mov ebp, esp

    mov esi, [ebp + 8]      ; Adresa vectorului de directoare (directories)
    mov ecx, [ebp + 12]     ; Numărul de directoare (n)
    mov edi, [ebp + 16]     ; Adresa variabilei output

    xor eax, eax            ; EAX = 0 (poziția curentă în vectorul de directoare)
    xor edx, edx            ; EDX = 0 (numărul de caractere în calea finală)

loop_start:
    cmp eax, ecx            ; Verificăm dacă am parcurs toate directoarele
    jge loop_end

    mov ebx, [esi + eax * 4] ; Adresa directorului curent
    cmp dword [ebx], 0      ; Verificăm dacă directorul curent este un șir vid
    je loop_next

    cmp dword [ebx], curr   ; Verificăm dacă directorul curent este "."
    je loop_next

    cmp dword [ebx], back   ; Verificăm dacă directorul curent este ".."
    je loop_back

    ; Adăugăm caracterul "/" la sfârșitul calei finale dacă nu există deja
    movzx edi, byte [edi + edx - 1]
	mov al, byte [slash]
	cmp byte [edi], al
    ; cmp edi, byte [slash]
    jne add_slash

add_slash:
    mov byte [edi + edx], slash
    inc edx

    ; Adăugăm directorul curent la calea finală
    add ebx, 1              ; Ignorăm lungimea șirului (primul byte)
add_dir:
    movzx ecx, byte [ebx]   ; Caracterul curent din director
    mov byte [edi + edx], cl
    inc edx
    inc ebx
    cmp ecx, 0
    jne add_dir

    jmp loop_next

loop_back:
    cmp edx, 1              ; Verificăm dacă există suficient spațiu în calea finală
    jl loop_next

    ; Eliminăm ultimul director din calea finală (dacă există)
    mov edx, edx - 1        ; Decrementăm numărul de caractere
    movzx ecx, byte [edi + edx]
check_slash:
    cmp ecx, byte [slash]
    jne loop_back

    ; Eliminăm caracterul "/"
    mov byte [edi + edx], 0
    jmp loop_next

loop_next:
    inc eax                 ; Trecem la următorul director
    jmp loop_start

loop_end:
    mov byte [edi + edx], 0 ; Adăugăm terminarea șirului la sfârșitul calei finale

    pop ebp
    leave
    ret
