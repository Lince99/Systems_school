---
tags: [Import-0f7e]
title: READVBX
created: '2019-10-01T10:05:06.945Z'
modified: '2019-10-01T10:37:03.644Z'
---

# READVBX

Leggere file .vbox (XML) per poi convertire i dati contenuti a scelta in xml, html, rtf, txt

## Come funziona

1. Legge da stdin o da argomento il file .vbox
1. Stampa in uscita i dati selezionati nei vari formati possibili
	1. Quantità di dati:
		- -0
        livello minimo di dati da esportare
		- -1
        livello intermedio (dati di rete, uuid)
		- -2
        livello completo (ogni dato presente nel .vbox)
	1. Formato di output:
		- -html XHTML+CSS
        output con maggior stile
		- -xml
        XML output uguale se la quantità è 2
		- -rtf
        output per esportare un documento
		- -txt
        output di anteprima dei contenuti
  1. I/O
    - -i
        file di input da leggere, se non presente

## Esempi

**IMPORTANTE! non specificare il formato nel file di output poichè è inserito dal programma in base al formato scelto via parametro**

```
./readvbx -0 -xml -i nomefile.vbox -o nomefile
```

oppure
```
./readvbx -0 -xml < nomefile.vbox > nomefile
```

oppure
```
./readvbx -0 -xml > nomeout
#da scrivere tutto in stdin 
```

## Quantità di dati

1. 0: NO ExtraData, CPU specs, void Adapters, HDD uuid
1. 1: NO ExtraData, HDD uuid
1. 2: Everything

## TODO

[] Creare libreria di lettura albero XML
[] Creare liberia di output
[] Unire e fare la prima release

## Disclaimer

L'autore e i contributori di questo progetto non si assumono alcuna responsabilità nella perdita di dati nei file .vbox originali. E' vivamente consigliato fare una copia di backup prima di manipolarli.
