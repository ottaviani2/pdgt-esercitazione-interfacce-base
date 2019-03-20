# Esercitazione 1: interfaccia del codice C

## Introduzione

Una volta compilato, il codice può essere visto come una “scatola nera” che esegue delle operazioni in maniera del tutto opaca all’utilizzatore ed anche al programmatore originale.
Il codice tuttavia non è *del tutto* opaco: tramite un sistema di **API**&nbsp;(Application Programming Interface) altri sviluppatori possono interagire con esso, mentre tramite un sistema di **ABI**&nbsp;(Application Binary Interface) altri blocchi di codice possono “comunicare” con il codice in questione.

In questa semplice esercitazione vedremo in pratica in cosa consistono API ed ABI dal punto di vista di uno sviluppatore, con l’esempio concreto di un semplice progetto in linguaggio&nbsp;C.

## Procedura

### 1. Diamo un’occhiata

Il codice è composto da:

* `divide.c`: file di codice, con una singola funzione `divide()` che, come suggerisce il nome, calcola il risultato della divisione tra due numeri interi,
* `divide.h`: come prevede il linguaggio C, le funzioni contenute in un file `.c` che devono essere “visibili esternamente” vanno dichiarate in un file `.h` associato. In questo caso dichiariamo la natura della funzione (tipi di dati, parametri, nome della funzione),
* `test.c`: semplice programma d’esempio che fa uso della funziona dichiarata ed implementata nei due file di cui sopra.

### 2. Compiliamo la funzione

I seguenti comandi fanno uso di GCC su sistema Unix, ma si può utilizzare `tcc` su Windows in alternativa.
Per compilare la funzione di divisione, lanciamo il seguente comando:

```bash
gcc -c divide.c -o divide.a
```

Il nostro codice “di libreria”, che non ha dipendenze esterne, verrà compilato nel file oggetto ```divide.a```. Non trattandosi di un file eseguibile, non sarà possibile eseguire il file.

Tuttavia è possibile andare ad esaminare il file compilato sfruttando ```objdump```. In particolare ```objdump -f divide.a``` ci darà informazioni di alto livello sul file, mentre ```objdump -t divide.a``` restituirà la _tabella dei simboli_ del file
Tale tabella dovrà contenere il riferimento all’unica funzione contenuta nel file compilato, ossia “divide”.
Il sistema di _name mangling_ di C è molto semplice, per cui generalmente il riferimento alla funzione comparirà con il nome originale nel codice sorgente. In altri linguaggi (come ad esempio C++) il sistema di _name mangling_ è più complesso (e dipende da altri fattori, come il compilatore utilizzato).

### 3. Utilizziamo la funzione

Per utilizzare il file di libreria, sarà necessario compilare il programma d’esempio.
Il comando:

```bash
gcc test.c -o test
```

restituirà un errore perché il compilatore (nella fase di _linking_ in particolare) non riuscirà a trovare il simbolo “divide”, che sappiamo essere incluso nel file oggetto `divide.a`.
Sarà sufficiente aggiungere il file oggetto con il simbolo richiesto come file di input:

```bash
gcc test.c divide.a -o test
```

A questo punto dovremmo ottenere un file eseguibile `test` che possiamo eseguire.

```bash
./test
```
