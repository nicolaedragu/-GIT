%include "../include/io.mac"

section .data
	; declare global vars here
	vocale db "aeiou"
	format_string db "%s", 0
	; fformat_string db "%s", 0

section .text
	global reverse_vowels
	extern printf

;;	void reverse_vowels(char *string)
;	Cauta toate vocalele din string-ul `string` si afiseaza-le
;	in ordine inversa. Consoanele raman nemodificate.
;	Modificare se va face in-place
reverse_vowels:
	push ebp
	xor ebp, ebp
	add ebp, esp
	
	add esp, 8
	pop esp
	sub esp, 12
	
	jmp done
	
	; xor edi, edi
	; push dword [ebp + 8]
	; pop edi
	
	
	; push format_string
	; push edi
	; call printf
	; add ebp, 8
	

done:
	; sub ebp, 8

	; popa
	ret