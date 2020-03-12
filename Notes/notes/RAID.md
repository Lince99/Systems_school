---
title: RAID
---

# RAID

Raid non e' backup, sono due aspetti differenti:
- Backup: mantenere i dati, pc spento e dati ci sono
- Raid: continuita' di servizio, serve a mantenere il servizio attivo insieme da altre funzioni

Sistemi performanti e durevoli devono avere i controlli di temperatura, sistema di dischi per il quale se un disco fallisce

**RAID: Redundant Array of Independent Disks**

[Wikipedia RAID](https://it.wikipedia.org/wiki/RAID)

Costa di piu' tenere il server fermo tot ore o un disco nuovo in piu' (contanto anche la manodopera)?

## Numerazione

### RAID 0

Non cura la sicurezza dei dati, serve per avere massime capacita' e prestazioni ma accetta 0 dischi falliti.
Se un disco fallisce si perdono i dati.

#### Esempio

- 5 dischi
- dischi su ogni controller differente
- tempo di accesso di un singolo disco diviso in 5 dischi contemporaneamente

#### Utilizzo tipico

Workstation

### RAID 1

Chiamato anche mirroring, scrive i dati parrallelamente su entrambi i dischi.
Differisce dal backup poiche' quest'ultimo prende un solo istante e li mette da parte.
Un virus se attacca un sistema con RAID 1, i dati vengono cancellati da entrambi i dischi in tempo reale.
Comprando i dischi, il prezzo e' il doppio rispetto allo spazio utilizzabile.
200 di dischi, ottengo solo 100 di disco.

Aumenta la resistenza ai guasti, ma e' meno prestante di avere un disco singolo, poiche' scrive due volte la stessa cosa.

#### Esempio

- Aumento di prestazioni in lettura, poiche' si puo' leggere due meta' del file da due dischi su controller diversi

#### Esempio ed esercizio tipico

Creazione macchina virtuale con RAID 1


### RAID 2 e 3

Non molto implementati

### RAID 4

Se si possiede minimo 3 dischi, si ha un sistema che resiste al guasto di un disco.
Utilizza lo XOR per mettere meta' contenuti nel disco A, altra meta' nel disco B e lo XOR dei dati nel C.
Se uno dei dischi si rompe, l'operazione di XOR permette di mantenere vivi i dati scambiando le colonne dell'operazione.

|A|B|XOR|
|---|---|---|
|0|0|0|
|1|0|1|
|0|1|1|
|1|1|0|

#### Esempio

- Da la possibilita' di inserire un disco a caldo.
- Il disco delle parita' viene riscritto ogni volta che viene cambiato il disco.
- Scrittura rallentata nel calcolo della parita'.
- Il disco di parita' e' il cono di bottiglia e anche il piu' utilizzato, quindi soggetto a rotture

### RAID 5

La parita' rimane nell'ultimo disco, poi nei successivi dati, la parita' viene shiftata nel disco precedente.
Cosi' il consumo e' uniforme tra tutti i dischi, ottenendo un vantaggio di scrittura.

#### Esempio

- Nel caso di utilizzo di 3 dischi, la resa e' del 66%.
- Con 4 dischi diventa 75%.

Spazio_totale = Spazio_del_disco * (n-1)
Spazio_percentuale = (n-1)/n

Piu' sono i dischi, piu' lo spazio in percentuale tendera' al 100%.
Pero' la possibilita' che i dischi si guastino porta a trovare un compromesso.

### RAID 10

Combinano RAID 1 e RAID 0

## Striping

Prendo piu' dischi e spargo i dati nei vari dischi = fornisce un unico disco con la somma della
Perdo l'affidabilita' poiche' basta solo un disco fallimentare per perdere parte dei dati


## RAID hardware e RAID software

### RAID hardware

Scheda fisica configurabile che gestisce i dischi, la quale fara' vedere al sistema operativo solo un disco.
Utile per gli OS che non supportano i sistemi RAID.
Rende pero' difficile il recupero dei dati nel caso la scheda si rompa.

### RAID software

L'OS vede all'inizio tutti i dischi come dischi normali, poi li vede come RAID.
Conviene il RAID software in base alle situazioni, poiche' richiede computazione alla macchina ospitante.

## TODO

- Creare pc virtuale con 2 dischi in raid 1
- disco da 4 GB
- Dopo creazione virtualbox
- Creare subito altro disco
- Impostare il controller a minimo 4 porte disco
- Debian prevede installazione di software raid
- Partizionamento uguale tipo 0xfd (volume fisico raid)
- Creazione raid software in linux si chiamano /dev/md_0 ...1
- Root da 4GB swap da 300 MB
- RAID 1 per partizioni sda2 e sdb2
    - md0 = sda2 sdb2
    - md1 = sda1 sdb1
    - cancellare md0
    - creare md2 = sda2 sdb2
    - md = multiple disk
- Cercare il Controllo RAID
    - /proc/mdstat
- Settimana prossima disconnessione disco in live per tenere il sistema in live
