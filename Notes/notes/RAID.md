---
title: RAID
created: '2020-03-12T09:29:18.898Z'
modified: '2020-04-03T07:52:02.319Z'
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

## TODO creare RAID 1

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


### Istruzioni creazione Raid 1 in Virtualbox

1. Creare nuova macchina virtuale
    1. debian_raid
    1. RAM: 2048 MB
    1. HDD: 4 GB
    1. Impostazioni della macchina
        1. System
            1. Aggiungere un processore in piu
        1. Storage
            1. Inserire la iso nel lettore dischi del controller IDE
            1. Controller SATA
                1. Incrementare Port Count a 4
                1. Aggiungere un altro disco debian_raid2 da 4 GB
        1. Network
            1. Cambiare in Bridged Adapter

1. Inserire la iso di debian 10 e avviare la macchina virtuale
1. Install (no GUI)
    1. Lingua: italiano
    1. Nome host: propriocognomeraid (bassoraid)
    1. Nome del dominio: lasciarlo vuoto
    1. Password di root: lasolita
    1. Nome completo utente: Utente di Servizio
    1. Username: uds
    1. Password: lasolita
    1. Partizionamento Manuale
        1. Per ogni disco SCSIx
            1. partizione primaria
                1. 4.0 GB
                1. volume fisico per il RAID
            1. partizione logica
                1. 292.6 MB
                1. volume fisico per il RAID
        1. Configurare il RAID software per il root
            1. Configurare un device multidisk (MD)
            1. RAID 1
            1. 2 dischi attivi
            1. 0 device "spare"
            1. Terminare
        1. Configurare il RAID software per lo swap
            1. Configurare un device multidisk (MD)
            1. RAID 1
            1. 2 dischi attivi
            1. 0 device "spare"
            1. Terminare
        1. Selezionare la partizione 1 creata via raid software
            1. Usare come: File system ext4 con journaling
            1. Punto di mount: /
        1. Selezionare la partizione 2 per la swap
            1. Usare come: swap
      1. Selezionare mirror italiano
          1. ftp.it.debian.org
      1. Lasciare i pacchetti di default (non aggiungere GUI o altri servizi)
      1. Installare GRUB: si
          1. Installarlo nel primo disco
1. Entrare come uds
    1. `su -`
    1. `apt update && apt install sudo nano elinks -y`
    1. Installare grub anche sull'altro disco `grub-install /dev/sda && grub-install /dev/sdb`
1. Questo sistema va ancora in modalita' legacy, mentre ora si usa la modalita' UEFI 
1. Tipologie di superblocchi:
    1. Inizio
    1. Fine: permette l'utilizzo di avvio da BIOS UEFI
        1. UEFI non prevede mbr o altro codice, ma una partizione da 100 MB etichettata da gpt che contiene degli eseguibili come un normale file system, e da qui viene caricato il giusto loader (grub o windows boot loader), avendo 2 dishi servono 2 partizioni UEFI in parallelo
        1. Serve partizione fat per il raid
    1. Quando il kernel vede partizioni di tipo RAID va a leggere all'inizio del disco o alla fine, se non trova nulla allora sono partizioni generiche


#### Disconnessione di un disco in live

##### Informazioni varie sui dischi

Mostra tutte le partizioni presenti

```bash
cat /proc/partitions
```

Se si possiede nagios nel server RAID

```bash
/usr/lib/nagios/plugins/check_raid
```

Mostra le informazioni e lo stato del disco

```bash
cciss_vol_status -V /dev/sda
```


Nel caso di raid software il seguente comando mostra le informazioni

```bash
cat /proc/mdstat
```

SE NON VENGONO FUORI DATI:

```bash
mount
```

Dove si vede /dev/sda1, se ha la radice ( / ) allora non e' stata configurato il RAID

```bash
cfdisk /dev/sda
cfdisk /dev/sdb
```

##### MDADM e VBoxManage

Virtualbox possiede il comando `VBoxManage`:
- Permette di gestire le macchine virtuali da riga di comando
- `VBoxManage --help`
- l'opzione `modifyvm` permette di aggiungere dischi a caldo
- `storageattach` permette di staccare i dischi

Per simulare una rottura del primo disco:
1. Servono delle operazioni all'interno della VM come `dmesg`
1. Con `cat /proc/mdstat` devono venire fuori delle UUU_UUUUUU
1. In live riattaccare il disco e vedere i log
1. Il Raid software
1. `mdadm -Q /dev/md0` mostra lo stato di un raid
1. `mdadm -E /dev/sda | less` mostra le informazioni del disco
    1. Guardando l'Array UUID di varie partizioni si possono notare se fanno parte dello stesso raid
1. Il raid hardware i controlli di sincronizzazione sono automatici, mentre il raid software richiede dei comandi di sincronizzazione

> Obbiettivo cercare di riallineare le partizioni staccando prima il primo disco e poi il secondo con il primo attaccato.

###### VBoxManage per staccare un disco

https://www.virtualbox.org/manual/ch08.html ( Voce _8.17. VBoxManage storageattach_ )  
https://nakkaya.com/2012/08/30/create-manage-virtualBox-vms-from-the-command-line/

1. Si ottengono le informazioni della macchina virtuale

```bash
VBoxManage showvminfo debian_raid
```

1. La macchina deve essere in esecuzione e si esegue il seguente comando da root:

```bash
su -
dmesg -wH
```

1. E si stacca il primo hard disk
    1. Su virtualbox i dischi devono avere l'opzione **Hot-pluggable** attivata

    1. Comando da eseguire nella macchina ospitante:
    ```bash
    VBoxManage storageattach "debian_raid" --storagectl "SATA" --port 1 --medium none
    ```

    1. Deve venire fuori il seguente messaggio in dmesg:
    
    > md/raid1:md0: Operation continuing on 1 devices
