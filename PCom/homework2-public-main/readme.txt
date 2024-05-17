    Dragu Nicolae 324CC
    
        Am lucrat in c++.
        In fisierul utils.hpp am declarat headerele folositoare si macroul DIE,
alaturi de structurile de date folosite in rezolvarea problemei si am definit
lungimea maxima a buffer-ului.
        In subscriber.cpp incep sa implementez clientul TCP care se conecteaza la
server si primeste mesajele de la acesta. Programul primeste 3 argumente de la
linia de comanda: Id ul clientului, adresa IP a serverului si portul pe care
acesta asculta. Se creeaza un socket TCP si se conecteaza la server, folosind
adresa IP si portul date ca argumente.
        Clientul poate trimite 3 comenzi: 
        - subscribe: trimite serverului un mesaj de tip subscribe, care contine
topicul la care se aboneaza
        - unsubscribe: trimite serverului un mesaj de tip unsubscribe, care
contine topicul de la care se dezaboneaza
        - exit: trimite serverului un mesaj de tip exit, care semnaleaza
inchiderea conexiunii
        In server.cpp initial am cateva functii inainte de main. Functia
send_messages trimite mesaje catre toti clientii abonati la un anumit
topic. Parcurg lista de clienti si vad daca este conectat. Daca este conectat si
este abonat la topicul respectiv, ii trimit mesajul.
Functia este make_readable transforma un mesaj UDP intr-un format citibil.
In functie de tipul de date primit, il formateaza corespunzator conform tabelului
din enunt, urmand ca la final sa adauge acest mesaj la TCP impreuna cu adresa IP
si portul clientului corespunzator.
Am functii de cautare a anumitilor clienti in functie de ID sau socket.
Functia close_connections inchide toate conexiunile deschise. pentru
fiecare client conectat, se inchide socketul lui. Se inchide si socketurile
UDP si TCP ale serverului. 
        In main pregatesc serverul pentru a primi mesaje de la clienti. Se
creeaza un socket TCP si unul UDP. Se seteaza optiunile pentru a putea folosi
aceste socketuri. Se adauga socketii la multimea de descriptori si se asteapta
conexiuni de la clienti. Se proceseaza socketurile in functie de tipul lor.
Daca este un socket TCP, se verifica daca clientul este deja inregistrat.
Daca nu este inregistrat, este adaugat la vectorul de clienti. Daca este
inregistrat, se verifica daca nu cumva s-a deconectat anterior.
Daca este un socket UDP, se primeste mesajul si se apeleaza functia make_readable
pentru a-l transforma intr-un format citibil. Se trimit mesajele catre abonati.
Daca se primeste o comanda de la un abonat, se efectueaza aceea comanda.
Acest main este structurat in mari functii separate, pentru a fi mai lizibil
codul. Sunt functii pentru a procesa fiecare tip de socket sau cerinta de la
un client.
        Peste tot in proiect am folosit macroul DIE pentru a realiza un control
al erorilor si a afisa un mesaj corespunzator in cazul in care acestea apar.