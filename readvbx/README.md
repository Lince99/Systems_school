# READVBX

Leggere file .vbox (XML) per poi convertire i dati contenuti a scelta in xml, html, rtf, txt

## Come funziona

1. Legge da stdin o da argomento il file .vbox
1. Stampa in uscita i dati selezionati nei vari formati possibili
	1. Quantità di dati:
		- -0 livello minimo di dati da esportare
		- -1 livello intermedio (dati di rete, uuid)
		- -2 livello completo (ogni dato presente nel .vbox)
	1. Formato di output:
		- -html XHTML+CSS, output con maggior stile
		- -xml XML, output uguale se la quantità è 2
		- -rtf, output per esportare un documento
		- -txt, output di anteprima dei contenuti
