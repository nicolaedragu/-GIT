section .data
	; declare global vars here

section .text
	global reverse_vowels

;;	void reverse_vowels(char *string)
;	Cauta toate vocalele din string-ul `string` si afiseaza-le
;	in ordine inversa. Consoanele raman nemodificate.
;	Modificare se va face in-place
reverse_vowels:
	; Initializez stack frame-ul
	push ebp
	push esp
	pop ebp
	; Obtin de pe stiva sirul, singurul argument al functiei
	push dword [ebp + 8]
	; Il stochez in EDI
	pop edi
	; Pregatesc variabila EDX, 
	; pe care o voi folosi cu scopul de a trece prin fiecare litera a sirului
	xor edx, edx
	jmp gasire_vocale

; Bucla pentru obtinerea valorii in codul ASCII al fiecarei litere din sir
ascii:
	; Aceasta se obtine in registrul ECX, 
	; dar trebuie utilizat registrul pe 8 biti - CL
	cmp byte [edi + edx], cl
	; S-a calculat valoarea literei
	je back
	; In caz contrar, se creste CL - ul pana vom da de valoarea literei
	inc cl
	jmp ascii
	
; Bucla ce itereaza prin fiecare litera a sirului
gasire_vocale:
	;  Pregatirea valorii ce stocheaza codul ASCII al literei
	xor ecx, ecx
	; Daca s-a ajuns la delimitatorul de sir '/0', se termina bucla
	cmp byte [edi + edx], 0
	je final
	; Se afla valoarea literei in ASCII
	jmp ascii
back:
	; Verificam daca e vocala
	cmp byte [edi + edx], 'a'
	je vocala
	cmp byte [edi + edx], 'e'
	je vocala
	cmp byte [edi + edx], 'i'
	je vocala
	cmp byte [edi + edx], 'o'
	je vocala
	cmp byte [edi + edx], 'u'
	je vocala

; Daca se ajunge la aceasta parte din cod, inseamna ca 
; litera pe care o verificam este o consoana
consoana:
	; Se verifica urmatoarea litera din sir
	jmp urmatorul

; E vocala, deci impingem codul ASCII al vocalei pe stiva, 
; urmand a fi recuperat aceasta valoare in cadrul urmatoarei bucle ce
; inlocuieste vocalele 
vocala:
	push ecx
	
; Crestem contorul pentru a ajunge la urmatoarea litera din sir
urmatorul:
	inc edx 		
	jmp gasire_vocale
	
; EDX va fi in final egal cu lungimea sirului
; Se reseteaza contorul de sir
final: 
	xor edx, edx
	jmp inlocuire

; Si se incepe o noua bucla, ce, asemeni primei bucle, 
; ia fiecare litera de la inceputul sirului pana la delimitatorul de sir
inlocuire:
	; Daca s-a ajuns la delimitatorul de sir '/0', se termina programul
	cmp byte [edi + edx], 0
	je done 
	; Se verifica daca este litera
	cmp byte [edi + edx], 'a'
	je schimbare_vocala
	cmp byte [edi + edx], 'e'
	je schimbare_vocala
	cmp byte [edi + edx], 'i'
	je schimbare_vocala
	cmp byte [edi + edx], 'o'
	je schimbare_vocala
	cmp byte [edi + edx], 'u'
	je schimbare_vocala
	
; Observam ca nu este litera, deci se trece la urmatoarea litera din sir
nu_e_vocala:
	jmp urmatorul_inlocuire
	
; Este litera
schimbare_vocala:
	; Trebuie sa schimbam vocala de pe pozitita curenta 
	; Vocala cu care trebuie schimbata este extrasa de pe stiva,
	; prin codul ASCII al ei
	pop ecx
	; In registrul ESI stochez pozitia curenta a literei din sirul meu
	xor esi, esi
	add esi, edi
	add esi, edx
	; Compar cu noua vocala, cu care trebuie inlocuita
	cmp byte [esi], cl
	jne incrementare_decrementare
	; Daca este deja egala cu noua vocala, se trece la
	; urmatoarea litera din sir
	jmp urmatorul_inlocuire
	
; Se incrementeaza sau decrementeaza vocala curenta, 
; cat timp valoarea in ASCII a vocalei curente este diferita de 
; vocala cu care trebuie inlocuita
incrementare_decrementare:
	cmp byte [esi], cl
	; Daca este mai mica valoarea
	jl mai_mic
	cmp byte [esi], cl
	; Daca este mai mare valoarea
	jg mai_mare
	
	; S-a executat cu succes interschimbarea vocalei curente cu 
	; vocala corespunzatoare 
	jmp urmatorul_inlocuire

; Se decrementeaza vocala curenta
mai_mare:
	dec byte [esi]
	jmp incrementare_decrementare
; Se incrementeaza vocala curenta
mai_mic:
	inc byte [esi]
	jmp incrementare_decrementare

; Se trece la urmatoarea litera din sir
urmatorul_inlocuire:
	inc edx
	jmp inlocuire

done:
	; Restaurarea stivei
	pop ebp
	ret