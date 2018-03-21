# Esercitazione 2: interfaccia tra processi

## Introduzione

Ogni processo in esecuzione sul proprio sistema operativo ha accesso ad un sistema di input e output tramite il quale può comunicare con il mondo (e gli altri processi in esecuzione).
In Unix ogni canale di comunicazioe è identificato da un “file descriptor”, un riferimento numerico al canale.
I vari canali disponibili vanno dai file (blocchi di dati memorizzati sulla macchina), ai flussi testuali (la riga di comando ad esempio), alle *socket* (delle strutture che permettono di comunicare con altri processi eventualmente in esecuzione su altre macchine remote).

Generalmente ogni processo in esecuzione in ambiente Unix ha 3&nbsp;canali di comunicazione aperti di default:

* Standard input (STDIN): flusso in ingresso, generalmente l'input fornito dall'utente da riga di comando,
* Standard output (STDOUT): flusso in uscita, generalmente i risultati che vengono scritti dal processo a video sulla riga di comando,
* Standard error (STDERR): flusso in uscita ausiliario, sempre visualizzato sulla riga di comando di default (assieme allo standard output), che serve per comunicare la presenza di errori.

Il meccanismo per cui, da riga di comando, è possibile concatenare più processi (collegando lo standard output dell'uno allo standard input del prossimo), si chiama **piping** (e si avvale generalmente del carattere `|` da riga di comando).

## Procedura

### Echo e Cat

Il programma più semplice per dimostrare il funzionamento dei canali standard di comunicazione è `echo`.
Ad esempio:

```bash
echo "Ciao mondo"
```

Non farà altro che stampare su standard output la stringa fornita (“Ciao mondo” in questo caso).

Mentre `echo` si basa sui parametri passati, il programma `cat` stampa i contenuti di un file:

```bash
cat divina_commedia.txt
```

stamperà i contenuti dell'intera Divina Commedia su standard output (ci potrebbe volere un po').

### Word count

Alcuni tool Unix prendono in input dei contenuti e li trasformano o effettuano delle operazioni in base ad essi. Ad esempio, `wc` conta il numero di righe, parole e caratteri presenti all'interno di un testo.

```bash
echo "Ciao mondo" | wc
```

ritornerà il numero di righe (1), il numero di parole (2) ed il numero di caratteri (11).
Possiamo applicare lo stesso processo anche alla Divina Commedia:

```bash
cat divina_commedia.txt | wc
```

### Altri strumenti

Si consiglia di fare qualche prova con altri strumenti Unix elencati qui sotto.
È generalmente sempre possibile lanciare lo strumento con il parametro `-help` oppure scrivere `man <nome del comando>` per ottenere una breve guida.

* `ls`: permette di ottenere una lista dei file, eventualmente ordinata (ad esempio, `ls -S` ordina dal file più grande al più piccolo) ed eventualmente su più righe (`ls -l` visualizza una lista suddivisa per righe).
* `sort`: riordina l'input in base all'ordine alfabetico delle righe di cui è composto.
* `more`: visualizza in più pagine l'input (utile per elenchi o file lunghi, ad esempio `cat divina_commedia.txt | more` permette di leggere la Divina Commedia suddivisa in paginate).
* `head`: visualizza le prime righe dell'input, in particolare `head -n 1` visualizza soltanto la prima riga.
* `tail`: stessa cosa, ma a partire dalla fine dell'input.
* `tac`: (il contrario di `cat` 😒) stampa l'input al contrario, dall'ultima riga alla prima.
* `curl`: scarica una risorsa online (tramite richiesta HTTP) e la stampa in output.

### Grep

Menzione speciale per `grep`, uno strumento un po' più sofisticato, che permette di fare *pattern matching* di una stringa all'interno dell'input.
Ad esempio:

```bash
curl http://www.example.org | grep -i "example"
```

stamperà tutte le righe in cui è presente la stringa “example” all'interno della pagina `example.org`.
Il parametro `-i` effettua un *pattern matching* che non distingue tra maiuscole e minuscole.

## Consegna

Di seguito sono indicate alcune domande alle quali rispondere specificando una sequenza di comandi Unix in piping che risolvono il problema.
Consegnare l'esercitazione semplicemente modificando questo file ed inserendo il comando corretto nel testo.

### 1. Fine della Commedia

Come si ottiene l'utima riga della Divina Commedia?

```bash
Inserire qui il comando che produce la risposta
```

### 2. A proposito di stelle

Le stelle occupano un significato simbolico all'intero della Divina Commedia. Quante volte vengono menzionate all'interno del testo?

```bash
Inserire qui il comando che produce la risposta
```

### 3. Lista dei file

Trovare il file più piccolo presente in questa cartella.

```bash
Inserire qui il comando che produce la risposta
```

### 4. Lista delle domande

Considerato che il sorgente di questo file è disponibile all'indirizzo:
`URL`
trovare il comando che generi la lista delle domande per la consegna.

```bash
Inserire qui il comando che produce la risposta
```
