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
; PRINTF32 `\n\x0`
pwd:
	enter 0, 0

	mov eax, [esp + 8]
	mov edx, [esp + 12]
	mov ecx, [esp + 16]

	xor edi, edi
parcurgere_siruri:
	mov esi, [eax + edi * 4]
	push edx
	mov dl, byte [esi]
	cmp dl, '.'
	jne director

identificare_comanda:
	mov dl, byte [esi + 1]
	cmp dl, 0
	je continuare_parcurgere
	cmp dl, '.'
	jne director
	mov dl, byte [esi + 2]
	cmp dl, 0
	jne director

anterior:
	push edi
	xor edi, edi
	gasire_sfarsit_1:
    	cmp byte [ecx + edi], 0
    	jz iesire_sfarsit_1

    	add edi, 1
    	jmp gasire_sfarsit_1
	iesire_sfarsit_1:

	gasire_slash:
		cmp byte [ecx + edi], '/'
		jz iesire_slash

		sub edi, 1
		jmp gasire_slash
	iesire_slash:
	mov dl, 0
	mov byte [ecx + edi], dl

	pop edi
	jmp continuare_parcurgere

director:
	push edi
	xor edi, edi
	gasire_sfarsit_2:
    	cmp byte [ecx + edi], 0
    	jz adauga_slash_2

    	add edi, 1
    	jmp gasire_sfarsit_2

    adauga_slash_2:
        mov dl, '/'
		mov byte [ecx + edi], dl

		add edi, 1
		push ebx
		xor ebx, ebx
        copiaza_sir:
            mov dl, byte [esi + ebx]
            mov byte [ecx + edi], dl
			add ebx, 1
			add edi, 1
            cmp dl, 0         
            jnz copiaza_sir
	pop ebx
	pop edi

continuare_parcurgere:
	pop edx
	add edi, 1
	cmp edi, edx
	jl parcurgere_siruri

iesire:
	gasire_sfarsit_3:
    	cmp byte [ecx + edi], 0
    	jz adauga_slash_3

    	add edi, 1
    	jmp gasire_sfarsit_3

    adauga_slash_3:
        mov dl, '/'
		mov byte [ecx + edi], dl

	leave
	ret