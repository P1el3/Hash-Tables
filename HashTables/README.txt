tema1 SD ==README==

~ mi-am defininit fisierele la inceput deoarece le am luat
in considerarea mai tarziu si mi-a fost lene sa editez functiile :)

~ liniile 8-22 contin declararile structurilor utilizate in realizarea temei

~ liniile 24-33 contin functia de initializare a listei

~ liniile 35-78 contin functia de adaugare a elementelor in lista
	aici tratez urmatoarele cazuri:
		-cazul in care lista este vida
		-cazul in care elementul exista deja in lista
		-cazul in care elementul exista si implicit fac cautarea unde trebuie adaugat

~ liniile 80-110 contin functia de stergere a unui element din lista
	aici tratez urmatoarele cazuri:
		-cazul in care lista este vida
		-cazul in care elementul este in lista, si il sterg
	(only este cazul in care lista are doar 1 element)
	(cum gandisem codul initial, crapa la rulare pe 1 singur element)
	(gaseste elementul si face lista vida)

~ liniile 112-125 contin functia de printare a listei
	=nu-s prea multe de spus=

~ liniile 127-145 contin functia de eliberare a memoriei alocate
	aici tratez urmatoarele cazuri:
		-cazul in care lista-i vida si nu fac nimic
		-cazul in care lista nu-i vida si sterg element cu element
			
~ liniile 147-163 contin functia de cautare a unui element in functie

~ liniile 164-169 contin declarea tabelei hash

~ liniile 171-182 contin o functie de inserare in tabela hash

~ liniile 184-207 contin functii care ma ajuta-n realizarea operatiilor pe tabela hash
		(sunt functii simple la care nu stiu ce sa explic)

~ liniile 209-213 contin declararea structurii care contine variabilele "key" si "value"

~ liniile 215-220 contin functia de dezalocarea a memoriei

~ liniile 221-225 contin functia care se ocupa cu afisarea output-ului in hash.out

~ liniile 226-231 contin functia care se ocupa cu compararea a 2 elemente

~ liniile 233-241 contin functia care se ocupa cu adaugarea elementelor key si value in hashtable

~ liniile 243-249 contin functia care se ocupa de stergerea unui element din tabela hash

~ liniile 251-262 contin functia care se ocupa cu printarea in fisierul de output(hash.out)

~ liniile 264-270 contin functia de print a bucket-ului care testeaza daca index este intre m si 0

~ liniile 272-278 contin functia care returneaza valoarea cheii

~ liniile 280-286 contin functia care se ocupa cu cautarea cheii in hashtable

~ liniile 288 variabila generala pe care o folosesc in functia urmatoarea si in main

~ liniile 289-299 functie care returneaza restul impartirii sumei caracterelor la nr maxim de bucket-uri

~functia main unde se apeleaza functiile mentionate mai sus.
