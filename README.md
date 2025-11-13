# Tema 1 – Liste dublu înlănt,uite, stive

### Ioana Dabelea, Alexandru Tudor, Răzvan S,erb, S,tefan Turcu,

### Alin Ichim, Andrei Voicu

### Data postării: 28.03.

## Deadline: 17.04.2025 ora 23:

Încă de la începuturile Internetului cu primele browsere text-based, precum Lynx, până la
Netscape Navigator s,i Internet Explorer, care au dominat anii ’90, s,i ulterior la Chrome, Firefox
s,i Edge, funct,ionalităt,ile de navigare pe web au evoluat continuu pentru a răspunde nevoilor
utilizatorilor.

Pe măsură ce mediul online s-a extins s,i s-a diversificat, comportamentul utilizatorilor s-a
schimbat semnificativ. Dacă la început navigarea era liniară s,i restrânsă la câteva pagini, astăzi
utilizatorii deschid simultan zeci de taburi, fiecare urmând un traseu propriu de explorare. În
acest context, istoricul de navigare nu mai este doar o listă de pagini accesate, ci un instrument
care poate facilita regăsirea rapidă a informat,iilor s,i organizarea cont,inutului online.

## 1 Descriere problemă

În această temă, vom explora o arhitectură de gestionare a istoricului unui browser web,
inspirată din sistemele utilizate de browserele moderne. Mai departe sunt descrise elementele
care vor ajuta la crearea unui sistem utilizat pentru a t,ine evident,a istoricului de navigare al
unui browser web care permite deschiderea mai multor taburi simultan, iar în cadrul unui tab
se poate naviga între mai multe pagini web.

O pagină web este un document accesibil pe internet, care poate cont,ine text, imagini,
videoclipuri s,i alte elemente interactive. În această temă, vom defini opaginăprintr-ostruc-
turăce include unID (număr întreg),un s,ir de caractere ce reprezintă un URL(maxim 50
de caractere) s,iun s,ir de caractere de dimensiune variabilă ce reprezintă descrierea paginii(va
cont,ine litere, cifre, blanc s,i semne de punctuat,ie s,i se va termina cu newline).

```
Structura unei pagini este:
```
### struct page {

```
int id;
char url[50];
char *description;
```
### };

```
ID
URL
Descriere
```

```
Observat,ie
```
```
Există opagină implicităcare va fi deschisă de fiecare dată când se creează un nou
tab. Aceasta are următoarele câmpuri:
```
- ID - 0
- URL - "https://acs.pub.ro/"
- descriere - “Computer Science”

```
Important
```
```
Toate paginile folosite în teste (mai put,in pagina implicită) vor fi citite din fis,ierul de
intrare. Vor exista maxim 50 de pagini s,i le putet,i salva în orice mod dorit,i
(spre exemplu listă sau vector de structuri).
```
Un tab (filă) este o sect,iune a browserului web care permite deschiderea s,i navigarea si-
multană între mai multe pagini web în aceeas,i fereastră. În această temă, vom defini untab
printr-ostructurăce cont,ine unID unic(număr întreg) pentru identificarea fiecărui tab,un
pointer către pagina curentă s,idouă stive folosite pentru istoricul tabului. Una din-
tre stive (BACKWARD) cont,inepaginilecare au fost deschise pentru a se ajunge la pagina
curentă, iar cealaltă stivă (FORWARD) cont,inepaginilecare au fost deschise anterior paginii
curente. Stivele vor fi folosite pentru a memora exclusiv istoricul tabului în care sunt definite.
O descriere mai detaliată este disponibilă în sect,iunea următoare.

```
Structura unui tab este:
```
### struct tab {

```
int id;
struct page *currentPage;
struct stack *backwardStack;
struct stack *forwardStack;
```
### };

```
ID
Pagina curent ̆a
Stiva BACKWARD
Stiva FORWARD
```
```
O reprezentare a tabului init,ial este următoarea:
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
int id = 0;
char url[50] = "https://acs.pub.ro/";
char *description = "Computer Science";
```
```
pagina curent ̆a
Stiva FORWARD
```
Un browser (navigator web) este o aplicat,ie care ne permite să accesăm s,i să navigăm
pe internet. Browserul interpretează codul paginilor web s,i le afis,ează într-un mod vizual
interactiv. Cu alte cuvinte, un browser permite deschiderea s,i utilizarea simultană a mai multor
pagini web prin intermediul taburilor (în browser se pot deschide taburi, iar în taburi
se pot accesa pagini). În această temă, vom defini untabprintr-ostructurăce cont,ineun
pointer către tabul curent(deschis în browser) s,io listă dublu înlănt,uită circulară cu
santinelăpentru gestionarea tuturor taburilor.


```
Structura unui browser este:
```
### struct browser {

```
struct tab *current;
struct tabsList list;
```
### };

```
Tabul curent
List ̆a de taburi
```
```
O reprezentare completă a unui browser este:
```
```
Vectorul de pagini
```
```
int id = 7;
char url[50] = "www.gatech.edu";
char *description = "Georgia";
```
```
int id = 25;
char url[50] = "acs.curs.pub.ro";
char *description = "ACS - UPB";
```
```
int id = 31;
char url[50] = "www.utoronto.ca";
char *description = "Toronto" ;
```
```
int id = 0;
struct page *current;
struct stack *backwardStack;
struct stack *forwardStack;
```
```
int id = 1;
struct page *current;
struct stack *backwardStack;
struct stack *forwardStack;
```
```
int id = 2;
struct page *current;
struct stack *backwardStack;
struct stack *forwardStack;
```
```
santinel ̆a tab curent
```
```
În ilustrat,ia de mai sus este prezentat un browser care cont,ine 3 taburi:
```
- Tabul cu ID 0, în care este accesată pagina cu ID 7, cu descrierea "Georgia".
- Tabul cu ID 1, în care este accesată pagina cu ID 31, cu descrierea "Toronto".
- Tabul cu ID 2, în care este accesată pagina cu ID 7, cu descrierea "Georgia".

Observat,ie

Init,ial, în browser va fi deschis doar un singur tab (cu ID 0), în care este accesată pagina
implicită.

Important

Pentru simplitate,doar în ilustrat,iile următoarevom folosi doar ID-urile taburilor s,i
paginilor. În locul acestora vor fi, de fapt, adresele structurilor ce reprezintă elementele
descrise.

NU trebuie să folosit,i ID-ul pe post de elemente s,i trebuie să lucrat,i cu
structurile specificate!


Astfel, putem ilustra structura browserului din exemplul anterior utilizând următoarea listă
circulară cu santinelă:

```
0 1 2
```
```
santinel ̆a tab curent
```
Un alt exemplu, pentru un browser care cont,ine 7 taburi, cu tabul cu ID 3 deschis (setat ca
tab curent), este:

```
santinel ̆a 0 1 2 3 4 5 6
```
```
TAB curent
```
De asemenea, componentele tabului init,ial (s,i a unui nou tab creat în browser) sunt reprezen-
tate astfel:

#### 0

```
Tabul cu id 0
Stiva BACKWARD
```
#### 0

```
pagina curent ̆a
Stiva FORWARD
```
Pentru a înt,elege mai bine cum se poate prelucra acest browser, vă propunem următorul
exemplu:

1. Pornim de la cont,inutul init,ial al browserului.

```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```

2. În browser se deschide un nou tab, cu ID 1, în care va fi accesată automat pagina 0.

```
0 1
```
santinel ̆a tab curent

```
1
```
```
Tabul cu id 1
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
3. În tabul curent se deschide o nouă pagină, cu ID 1.

```
0 1
```
santinel ̆a tab curent

```
0
```
```
Stiva BACKWARD
```
```
1
```
```
Tabul cu id 1
```
```
1
```
```
pagina curent ̆a
Stiva FORWARD
```
4. În tabul curent se deschide, din nou, o nouă pagină, cu ID 2.

```
0 1
```
santinel ̆a tab curent

```
1
0
```
```
Stiva BACKWARD
```
```
1
```
```
Tabul cu id 1
```
```
2
```
```
pagina curent ̆a
Stiva FORWARD
```
5. Se accesează pagina anterioară folosind butonul BACKWARD.

```
0 1
```
santinel ̆a tab curent

```
0
```
```
Stiva BACKWARD
```
```
1
```
```
Tabul cu id 1
```
```
1
```
```
pagina curent ̆a^2
Stiva FORWARD
```
6. Se accesează pagina următoare folosind butonul FORWARD.

```
0 1
```
santinel ̆a tab curent

```
1
0
```
```
Stiva BACKWARD
```
```
1
```
```
Tabul cu id 1
```
```
2
```
```
pagina curent ̆a
Stiva FORWARD
```

## 2 Prezentare operat,ii posibile

Va trebui să implementat,i mai multe funct,ionalităt,i prin care va fi gestionat istoricul
fiecărui tab. În continuare vom prezenta toate act,iunile posibile, specificând pentru fiecare
ce particularităt,i prezintă.

### 2.1 NEW_TAB

- Se creează un nou tab în lista de taburi.
- Init,ial, în browser va fi deschis doar un singur tab (cu ID 0, în care este accesată pagina
    implicită).
- Se va seta pagina implicită pentru un tab nou creat, iar acesta va fi setat ca tab curent
    al browserului.
- Tabul nou creat va fi adăugat la sfârs,itul listei s,i va primi automat un ID calculat prin
    incrementarea ID-ului ultimului tab adăugat în lista de taburi.

### 2.2 CLOSE

- Se închide tabul curent prin eliminarea sa din lista de taburi.
- În browser se va seta ca tab curent tabul aflat în stânga celui s,ters.
- Nu se va putea s,terge niciodată tabul cu ID 0 (tabul init,ial). Dacă se încearcă acest lucru,
    se va afis,a mesajul de eroare.

### 2.3 OPEN <ID>

- Tabul curent al browserului devine tabul cu ID-ul specificat.
- Dacă nu există un tab cu acest ID, se va afis,a mesajul de eroare.

### 2.4 NEXT

- Se deschide în browser tabul care urmează în listă după tabul curent. Astfel, noul tab
    care se deschide va fi notat ca tab curent al browserului.

### 2.5 PREV

- Se deschide în browser tabul care se află în listă înaintea tabului curent. Astfel, noul tab
    care se deschide va fi notat ca tab curent al browserului.

### 2.6 PAGE <ID>

- În tabul curent se deschide pagina cu ID-ul specificat. Dacă nu există o pagină cu acest
    ID, se va afis,a mesajul de eroare.
- Pagina curentă, care va fi înlocuită de noua pagină, va fi pusă în stiva Backward.
- Cont,inutul stivei Forward va fi s,ters.


```
Observat,ie
```
```
Explicat,ie suplimentară
Presupunem că în tabul curent este deschisă pagina 0 s,i urmează să fie accesate, pe rând,
paginile 1 s,i 2. Când se deschide pagina 1, aceasta va fi setată ca pagină curentă, iar
pagina 0 va fi adăugată în stiva Backward (stiva Forward va fi golită). Când se accesează
pagina 2, pagina 1 va fi s,i ea adăugată în stiva Backward (stiva Forward va fi golită).
```
### 2.7 BACKWARD

- În tabul curent, se va accesa ultima pagină adăugată în stiva Backward. Dacă stiva este
    goală, se va afis,a mesajul de eroare.
- Pagina curentă, care va fi înlocuită de pagina extrasă din stiva Backward, va fi pusă în
    stiva Forward.
Observat,ie

```
Explicat,ie suplimentară
Presupunem că în tabul curent este deschisă pagina 2. În stiva Backward se află paginile
1 s,i 0. Când se execută comanda Backward, pagina 1 va fi scoasă din stivă s,i va fi setată
ca pagină curentă, iar pagina 2 va fi adăugată în stiva Forward.
```
### 2.8 FORWARD

- În tabul curent, se va accesa ultima pagină adăugată în stiva Forward. Dacă stiva este
    goală, se va afis,a mesajul de eroare.
- Pagina curentă, care va fi înlocuită de pagina extrasă din stiva Forward, va fi pusă în
    stiva Backward.
Observat,ie

```
Explicat,ie suplimentară
Presupunem că în tabul curent este deschisă pagina 2. În stiva Forward se află paginile
3 s,i 4. Când se execută comanda Forward, pagina 3 va fi scoasă din stivă s,i va fi setată
ca pagină curentă, iar pagina 2 va fi adăugată în stiva Backward.
```
### 2.9 PRINT

- Se afis,eazăcircular, o singură dată, pe aceeas,i linie (separate de un spat,iu), ID-urile
    tuturor taburilor deschise în browser, începând de la tabul curent, spre dreapta.
- Se afis,ează, pe o linie nouă, descrierea paginii curente a tabului curent.

### 2.10 PRINT_HISTORY <ID>

- Se afis,ează, pe linii separate, URL-urile paginilor accesate în tab-ul cu ID-ul specificat.
    Dacă acest tab nu există, se va afis,a mesajul de eroare.
- Ordinea de afis,are a URL-urilor începe cu paginile aflate în stiva Forward (de la prima
    adăugată), continuă cu pagina curentă s,i se termină cu paginile aflate în stiva Backward
    (de la ultima adăugată).


```
Important
```
```
Mesajul de eroare este "403 Forbidden".
```
```
Acesta va fi afis,at pentru cazurile except,ionale specificate la operat,iileCLOSE,
OPEN <ID>, PAGE <ID>, BACKWARD s,i FORWARD.
```
## 3 Bonus

#### BONUS

```
Se va acorda un bonus pentru implementările care nu au deloc probleme, erori
la rularea testelor cu Valgrind.
```
## 4 Fis,iere de intrare

```
Datele se citesc din fis,ierultema1.ins,i rezultatele se vor scrie în fis,ierultema1.out.
```
Fis,ierele de intrare vor cont,ine, pe prima linie, numărul de pagini care pot fi folosite în test.
Urmează apoi câte 3 linii pentru fiecare pagină - prima linie cont,ine ID-ul, a doua linie cont,ine
URL-ul, iar a treia linie cont,ine descrierea. Pagina init,ială (default) nu va fi citită - se
asigură că toate paginile din fis,ierul de intrare au ID diferit de 0.

Pe următoarea linie se află N, numărul de operat,ii care vor fi executate, urmat de N linii ce
cont,in operat,iile descrise anterior.

## 5 Testarea temei

Temele trebuie să fie încărcate atât pechecker-ul automatcât s,i peMoodle, la sect,iunea
corespunzătoare.NUse acceptă teme trimise pe e-mail sau altfel decât prin intermediulMoo-
dle.

O rezolvare constă într-o arhivă de tipzipcare conţine toate fişierele sursă alături de un
Makefile, ce va fi folosit pentru compilare, şi un fişierREADME, în care se vor preciza de-
taliile implementării.

Makefile-ul trebuie să aibă obligatoriu regulile pentrubuildşiclean. Regulabuildtre-
buie să aibă ca efect compilarea surselor şi crearea binaruluitema1.

Va fi pus la dispozit,ie un checker prin care vet,i putea testa corectitudinea implementării.
De asemenea, acest checker va verifica existent,a fis,ierului README, nu s,i cont,inutul, acesta
urmând să fie verificat ulterior, manual.


## 6 Exemple

```
Exemplu NEW_TAB
```
```
tema1.in
```
(1) 3
(2) 1
(3) https://www.stanford.edu/
(4) A Mission Defined by Possibility
(5) 2
(6) https://www.ox.ac.uk/
(7) University of Oxford
(8) 3
(9) https://www.harvard.edu/
(10) Harvard University
(11) 4
(12) NEW_TAB
(13) NEW_TAB
(14) NEW_TAB
(15) PRINT

```
tema1.out
```
```
(1) 3 0 1 2
(2) Computer Science
```
```
Explicat,ie
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
Init,ial
```
```
0 1
```
```
santinel ̆a tab curent
```
```
1
```
```
Tabul cu id 1
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(12) NEW_TAB
```

```
0 1 2
```
```
santinel ̆a tab curent
```
```
2
```
```
Tabul cu id 2
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(13) NEW_TAB
```
```
0 1 2 3
```
```
santinel ̆a tab curent
```
```
3
Tabul cu id 3
Stiva BACKWARD
```
```
0
pagina curent ̆a
Stiva FORWARD
```
#### (14) NEW_TAB

(15) Comanda PRINT afis,ează ID-urile tuturor taburilor începând de la tabul curent s,i va
merge spre dreapta până parcurge toate taburile (linia 1 din output). De asemenea, se va afis,a
s,i descrierea paginii curente (pagina cu ID 0) din tabul curent (tabul cu ID 3).

```
Exemplu CLOSE
```
```
tema1.in
```
(1) 3
(2) 1
(3) https://www.stanford.edu/
(4) A Mission Defined by Possibility
(5) 2
(6) https://www.ox.ac.uk/
(7) University of Oxford
(8) 3
(9) https://www.harvard.edu/
(10) Harvard University
(11) 5
(12) NEW_TAB
(13) NEW_TAB
(14) CLOSE
(15) CLOSE
(16) CLOSE

```
tema1.out
```
```
(1) 403 Forbidden
```

```
Explicat,ie
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
Init,ial
```
```
0 1
```
```
santinel ̆a tab curent
```
```
1
```
```
Tabul cu id 1
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(12) NEW_TAB
```
```
0 1 2
```
santinel ̆a tab curent

```
2
```
```
Tabul cu id 2
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(13) NEW_TAB
```
```
0 1
```
```
santinel ̆a tab curent
```
```
1
```
```
Tabul cu id 1
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(14) CLOSE
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(15) CLOSE
```
```
(16) Comanda CLOSE nu poate fi executată pe tabul cu ID 0.
```

```
Exemplu OPEN
```
```
tema1.in
```
(1) 3
(2) 1
(3) https://www.stanford.edu/
(4) A Mission Defined by Possibility
(5) 2
(6) https://www.ox.ac.uk/
(7) University of Oxford
(8) 3
(9) https://www.harvard.edu/
(10) Harvard University
(11) 5
(12) OPEN 6
(13) NEW_TAB
(14) NEW_TAB
(15) OPEN 1
(16) PRINT

```
tema1.out
```
```
(1) 403 Forbidden
(1) 1 2 0
(2) Computer Science
```
```
Explicat,ie
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
Init,ial
```
(12) Se încearcă deschiderea tabului cu ID 6, doar că în browser există doar tabul init,ial cu
ID 0, deci se va afis,a mesajul de eroare.

```
0 1
```
```
santinel ̆a tab curent
```
```
1
```
```
Tabul cu id 1
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(13) NEW_TAB
```

```
0 1 2
```
```
santinel ̆a tab curent
```
```
2
```
```
Tabul cu id 2
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(14) NEW_TAB
```
```
0 1 2
```
```
santinel ̆a tab curent
```
```
1
```
```
Tabul cu id 1
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(15) OPEN 1
```
(16) În urma comenzii PRINT se vor afis,a ID-urile taburilor începând de la tabul 1 s,i va
afis,a descrierea paginii care este accesată în tabul curent (în acest caz, pagina implicită).

```
Exemplu NEXT s,i PREV
```
```
tema1.in
```
(1) 3
(2) 1
(3) https://www.stanford.edu/
(4) A Mission Defined by Possibility
(5) 2
(6) https://www.ox.ac.uk/
(7) University of Oxford
(8) 3
(9) https://www.harvard.edu/
(10) Harvard University
(11) 10
(12) NEW_TAB
(13) NEW_TAB
(14) NEW_TAB
(15) OPEN 2
(16) PRINT
(17) PREV
(18) PREV
(19) PREV
(20) NEXT
(21) PRINT

```
tema1.out
```
```
(1) 2 3 0 1
(2) Computer Science
(3) 0 1 2 3
(4) Computer Science
```

```
Explicat,ie
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
Init,ial
```
```
0 1
```
```
santinel ̆a tab curent
```
```
1
```
```
Tabul cu id 1
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(12) NEW_TAB
```
```
0 1 2
```
```
santinel ̆a tab curent
```
```
2
```
```
Tabul cu id 2
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(13) NEW_TAB
```
```
0 1 2 3
```
```
santinel ̆a tab curent
```
```
3
```
```
Tabul cu id 3
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
#### (14) NEW_TAB

```
0 1 2 3
```
```
santinel ̆a tab curent
```
```
2
```
```
Tabul cu id 2
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
#### (15) OPEN 2

(16) Se afis,ează ID-urile taburilor începând ID-ul 2. urmate de descrierea paginii curente a
tabului cu ID 2.


```
0 1 2 3
```
```
santinel ̆a tab curent
```
```
1
Tabul cu id 1
Stiva BACKWARD
```
```
0
pagina curent ̆a
Stiva FORWARD
```
#### (17) PREV

```
0 1 2 3
```
```
santinel ̆a tab curent
```
```
0
Tabul cu id 0
Stiva BACKWARD
```
```
0
pagina curent ̆a
Stiva FORWARD
```
#### (18) PREV

```
0 1 2 3
```
```
santinel ̆a tab curent
```
```
3
```
```
Tabul cu id 3
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
#### (19) PREV

```
0 1 2 3
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
#### (20) NEXT

(21) Se afis,ează ID-urile taburilor începând ID-ul 0, urmate de descrierea paginii curente a
tabului cu ID 0.


```
Exemplu PAGE
```
```
tema1.in
```
(1) 3
(2) 1
(3) https://www.stanford.edu/
(4) A Mission Defined by Possibility
(5) 2
(6) https://www.ox.ac.uk/
(7) University of Oxford
(8) 3
(9) https://www.harvard.edu/
(10) Harvard University
(11) 3
(12) PAGE 3
(13) PAGE 2
(14) PRINT_HISTORY 0

```
tema1.out
```
```
(1) https://www.ox.ac.uk/
(2) https://www.harvard.edu/
(3) https://acs.pub.ro/
```
```
Explicat,ie
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
Init,ial
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Stiva BACKWARD
```
```
0
```
```
Tabul cu id 0
```
```
3
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(12) PAGE 3
```
```
0
```
```
santinel ̆a tab curent
```
```
3
0
```
```
Stiva BACKWARD
```
```
0
```
```
Tabul cu id 0
```
```
2
```
```
pagina curent ̆a
Stiva FORWARD
```
#### (13) PAGE 2


(14) Se va afis,a URL-ul tuturor paginilor: prima dată vor fi afis,ate cele din stiva Forward
(goală în acest caz), apoi URL-ul paginii curente (ID 2), urmat de URL-ul paginilor cu ID 3 s,i
0 din stiva Backward.

```
Exemplu BACKWARD s,i FORWARD
```
```
tema1.in
```
(1) 3
(2) 1
(3) https://www.stanford.edu/
(4) A Mission Defined by Possibility
(5) 2
(6) https://www.ox.ac.uk/
(7) University of Oxford
(8) 3
(9) https://www.harvard.edu/
(10) Harvard University
(11) 10
(12) PAGE 1
(13) PAGE 2
(14) PAGE 3
(15) PAGE 3
(16) BACKWARD
(17) BACKWARD
(18) BACKWARD
(19) PRINT_HISTORY 0
(20) FORWARD
(21) PRINT

```
tema1.out
```
```
(1) https://www.harvard.edu/
(2) https://www.harvard.edu/
(3) https://www.ox.ac.uk/
(4) https://www.stanford.edu/
(5) https://acs.pub.ro/
(6) 0
(7) University of Oxford
```
```
Explicat,ie
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Tabul cu id 0
Stiva BACKWARD
```
```
0
```
```
pagina curent ̆a
Stiva FORWARD
```
```
Init,ial
```
```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Stiva BACKWARD
```
```
0
```
```
Tabul cu id 0
```
```
1
```
```
pagina curent ̆a
Stiva FORWARD
```
```
(12) PAGE 1
```

```
0
```
santinel ̆a tab curent

```
1
0
```
```
Stiva BACKWARD
```
```
0
```
```
Tabul cu id 0
```
```
2
```
```
pagina curent ̆a
Stiva FORWARD
```
#### (13) PAGE 2

```
0
```
santinel ̆a tab curent

```
2
1
0
```
```
Stiva BACKWARD
```
#### 0

```
Tabul cu id 0
```
#### 3

```
pagina curent ̆a
Stiva FORWARD
```
#### (14) PAGE 3

```
0
```
santinel ̆a tab curent

```
3
2
1
0
```
```
Stiva BACKWARD
```
#### 0

```
Tabul cu id 0
```
#### 3

```
pagina curent ̆a
Stiva FORWARD
```
#### (15) PAGE 3

```
0
```
santinel ̆a tab curent

```
2
1
0
```
```
Stiva BACKWARD
```
#### 0

```
Tabul cu id 0
```
#### 3

```
pagina curent ̆a
```
```
3
```
```
Stiva FORWARD
```
#### (16) BACKWARD


```
0
```
```
santinel ̆a tab curent
```
```
1
0
```
```
Stiva BACKWARD
```
#### 0

```
Tabul cu id 0
```
#### 2

```
pagina curent ̆a
```
```
3
3
```
```
Stiva FORWARD
```
#### (17) BACKWARD

```
0
```
```
santinel ̆a tab curent
```
```
0
```
```
Stiva BACKWARD
```
#### 0

```
Tabul cu id 0
```
#### 1

```
pagina curent ̆a
```
```
2
3
3
```
```
Stiva FORWARD
```
#### (18) BACKWARD

(19) Se va afis,a URL-ul tuturor paginilor: prima dată vor fi afis,ate cele din stiva Forward
(ID 3, ID 3 s,i ID 2), apoi URL-ul paginii curente (ID 1), urmat de URL-ul paginilor din stiva
Backward (ID 0)

```
0
```
```
santinel ̆a tab curent
```
```
1
0
```
```
Stiva BACKWARD
```
#### 0

```
Tabul cu id 0
```
#### 2

```
pagina curent ̆a
```
```
3
3
```
```
Stiva FORWARD
```
#### (20) FORWARD

(21) Se vor afis,a ID-urile taburilor existente (doar un singur tab în acest caz) s,i descrierea
paginii curente (ID 2).


## 7 Punctaj

O temă perfectă valorează 100 de puncte. 95 de puncte se vor acorda pentru teste s,i 5
puncte pentru README. Vor exista atât teste simple, care verifică o operat,ie specifică, dar s,i
teste complexe, în care există majoritatea operat,iilor.
În urma corectării manuale, punctajul acordat de checker-ul automat poate fi scăzut cu
maxim 15 puncte pentru coding style. De asemenea, cont,inutul fis,ierului README va fi
verificat manual, iar punctajul obt,inut pentru README poate fi diminuat.
Punctajul pe teste este următorul:

```
Cerint,a Punctaj
ComenziNEW_TAB 10 puncte
ComenziCLOSE / OPEN <ID> 20 puncte, 10 puncte (CLOSE), 10 puncte (OPEN)
ComenziNEXT / PREV 20 puncte (10 puncte fiecare comandă)
ComenziPAGE <ID> 10 puncte
ComenziBACKWARD / FORWARD 20 puncte (10 puncte fiecare comandă)
ComandaPRINT 5 puncte
ComenziPRINT_HISTORY <ID> 10 puncte
README 5 puncte
BONUS (testat cu valgrind) 20 puncte
TOTAL 120 puncte
```
```
Atent,ie!
```
- Orice rezolvare care nu conţine structurile de date specificateNUeste punctată.
    - browserulva fi implementat printr-o structură care va cont,ine o listă dublu
       înlănt,uită circulară cu santinelă s,i adresa celulei care indică tabul curent;
    - tabulva fi implementat ca o structură ce cont,ine un număr întreg, adresa
       paginii curente accesată în tab s,i două stive;
    - paginava fi implementată ca o structură ce cont,ine un număr întreg, un s,ir
       de maxim 50 de caractere s,i un s,ir de caractere de dimensiune variabilă;
    - Pentru orice altă solut,ie se vor anula punctajele obt,inute pe checker-
       ul automat s,i nu se vor primi puncte pentru README sau codying
       style.
- Descrierea unei pagini se va termina întotdeauna cu un caracter newline.
- Pentru descrierea paginii trebuie să alocat,i exact atâta memorie cât este
    necesară.
- Toate paginile folosite în teste (mai put,in pagina implicită) vor fi citite din fis,ierul
    de intrare. Vor exista maxim 50 de pagini s,i le putet,i salva în orice mod dorit,i
    (listă, vector de structuri, etc.).
- Folosirea variabilelor statice s,i/sau globale este interzisă!
- Temele vor fi punctate doar pentru testele care sunt trecute pe checker-ul automat.
- Nu lăsaţi warning-urile nerezolvate, deoarece veţi fi depunctaţi.
- Tema este individuală! Toate soluţiile trimise vor fi verificate, folosind o
    unealtă pentru detectarea plagiatului.


