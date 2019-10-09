# READVBX

Leggere file .vbox (XML) per poi convertire i dati contenuti a scelta
in xml, html, rtf, txt

## Come funziona

1. Legge da stdin o da argomento il file .vbox
    -i nomefile.vbox : legge dal file indicato
    (NECESSARIA ESTENSIONE VBOX, configurabile)
1. Stampa in uscita i dati selezionati nei vari formati possibili
	1. Quantità di dati:
	    - -1 livello minimo di dati da esportare
	    - -2 livello intermedio (dati di rete, uuid)
	    - -3 livello completo (ogni dato presente nel .vbox)
	    - nel caso di nessun livello selezionato, viene fornito il massimo dei dati
	1. Formato di output:
	    - -html XHTML+CSS : output con maggior stile
	    - -xml XML : output uguale se la quantità è 2
	    - -rtf : output per esportare un documento
	    - -txt : output di anteprima dei contenuti
	    - -o : output con nome scelto a priori con estensione (deve essere valida)
	    - nel caso di nessun formato selezionato, stampa in stdout

## Compilare il programma

E' presente un makefile per il progetto

Usare
```bash
make help
```
per vedere tutte le opzioni disponibili

Usare semplicemente __make__ per una compilazione semplice del programma

## Esempi

Legge dal file .vbox l'albero xml per estrarre una stampa html

```bash
readvbx -i client.vbox -o client.html
```

Legge dal file .vbox l'albero xml per estrarre un file omonimo html

```bash
readvbx -i client.vbox -html
```

Legge dal file .vbox solamente i dati minimi per esportarli in txt

```bash
readvbx -i client.vbox -0 -o client_info.txt
```

Comando minimo possibile, richiede file in stdin e produce il risultato in stdout

```bash
readvbx
```

Comando minimo con redirect

```bash
readvbx < client.vbox 2> result.txt
```

## Errori

-1: errore fatale nell'esecuzione del comando

0: tutto ok

1: errore nella lettura dei comandi o da stdin

2: errore nella lettura o apertura dei file

3: nessun contenuto, valori mancanti
