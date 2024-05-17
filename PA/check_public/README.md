1. Servere

    Folosesc Divide et Impera, de la 0 stanga si dreapta curentul maxim, avand
o functie pentru a calcula maximul. Mai am o functie care, pentru fiecare 
putere a serverului, aplica formula corespunzatoare calcularii puterii
individuale a fiecarui server dupa ce alimentam cu un curent "curent".
    Acest curent este calculat in functia "divide", unde calculez de 3 ori
puterea individuala si in functie de valorile acestea, ma mut cu 
intervalul in stanga respectiv dreapta.
    Algoritmul are complexitatea O(n * log n)

2. Colorare
    
    Observ ca numarul posibil de culori este fix, in functie de zona anterioara,
ajung la formula:
    - V V = posibilitatile anterioare * 2
    - H V = posibilitatile anterioare * 1
    - H H = posibilitatile anterioare * 3
    - V H = posibilitatile anterioare * 2
    Pentru inceput initilaizam numarul de posibilitati in functie de prima zona.
Daca este orizontala, avem 6 posibilitati. Daca este verticala, avem 3 posibilitati.
Retin zona anterioara si citesc perechile. Inmultesc corespunzator, apoi pentru zona
curenta ridic la putere logaritmica rezultatul sa pot inmulti repetat cu cate zone 
imi mai raman.
    Algoritmul are complexitatea O(n + numar * log n)

3. Compresie

    Ma plimb cu doi indici in ambii vectori. Am doua valori care stocheaza suma
pentru fiecare vector, care aduna elementele vectorului respectiv cat timp
cele doua sume sunt diferite. Cand ajung la o valoare egala, creste lungimea
sirului comun celor doua, cat si cei doi indici, astfel, cand intram intr-o noua
iteratie in bucla mare, se recalculeaza sumele cu noile valori.
    Algoritmul are complexitatea O(n + m)

4. Criptat

    Pentru aceasta problema, am ales sa stochez cuvintele intr-o structura,
putand astfel sa ma folosesc de aceasta mai tarziu. Principiul rezolvarii este: 
    - Pentru fiecare litera distincta, sortez cuvintele in asa fel incat cele
cu un raport de numar de litere dominante (cea aleasa anterior) pe numarul de
litere ale cuvantului sa aiba prioritate.
    - Creez parola. Adaug cuvintele in ordinea sortata cat timp numarul de litere
dominante este mereu peste lungimea parolei. Intai verific daca as fi adaugat
cuvantul curent iteratiei, daca conditia nu va fi adevarata, apoi adaug la parola
    - Fac asta pentru fiecare litera dominanta si mereu verific daca lungimea
parolei create este mai lunga decat parola pentru litera anterioara, astfel
retinand parola de lungime maxima
    Am functii pentru calcului acestui raport, pentru sortare (compare) si
pentru a afla numarul de aparitii ale literei dominante in cuvant.
    Algoritmul are complexitatea O(m * n * log n), cu 
    m = lungimea maxima a unui cuvant

5. Oferta

    Am rezolvat doar cazul pentru k = 1, deci pretul minim pentru cele n produse.
Intr-un vector dp[n] stochez costul celor [i] elemente, i = 0..n-1. Prima valoare
va fi costul primei valori iar pentru a doua valoare se va aplica reducere
de 50%, cea pentru doua produse. Testez gruparile:
    - Daca cumpar produsul i impreuna cu produsul i - 1 voi avea reducere
50% pe cel mai ieftin
    - Daca cumpar produsul i impreuna cu produsele i - 1 si i - 2, voi
avea cel mai ieftin produs gratis
    - Daca nu grupez si cumpar separat.
Fac minimul din aceste 3 cazuri si il adaug in vectorul dp si returnez corespunzator.
    Algoritmul are complexitatea O(n)