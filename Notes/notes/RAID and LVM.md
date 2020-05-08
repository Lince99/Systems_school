---
title: RAID and LVM
created: '2020-03-12T09:29:18.898Z'
modified: '2020-05-08T08:58:08.280Z'
---

# RAID and LVM

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

## Passaggi per creare un RAID 1

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
    1. Portare grub su tutti i dischi e per vedere se tutti ce l'hanno `upgrade-from-grub-legacy`
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

##### VBoxManage per staccare un disco

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

### Trasformare un RAID 1 in un RAID 5

- Con due dischi da 1 TB in RAID1 ho solo il 50% della resa.
- Se ho bisogno di altro spazio e' possibile portarli a 2 TB aggiungendo un altro disco, portando al 66% di resa.

#### Scalabilita' del RAID con Linux

- Con Linux e' possibile tenere il server attivo senza interrompere il servizio
- Durante l'estensione dell'array, i dischi devono riorganizzarsi e genera una lentezza, quindi questa tipologia di lavoro va fatto in periodi di scarico del server

```
ext4 on block device
swap on block device

            root_partition  swap
                 |           |
/dev/sd_1        |           |
/dev/sd_2   partizione1   part2   partizione1   part2
                  |        |            |        |
/dev/sda         DISCO_FISICO          DISCO_FISICO
/dev/sdb  
```

Nel RAID1 con 2 dischi:
```
            root_partition  swap
                 |           |
           RAID_device1   RAID_device2
                 |\          |\__________________
                 | |         |                   |
                 | \------------------\          | 
/dev/sd_1        |           |        |          |
/dev/sd_2   partizione1   part2   partizione1   part2
                  |        |            |        |
/dev/sda         DISCO_FISICO          DISCO_FISICO
/dev/sdb  
```

- Nella fase di sincronizzazione del terzo disco il RAID non sara' ne 1 ne 5, pur mantenendo la dimensione del RAID1
    - Nel superblocco avra' una sua struttura speciale
    - Il RAID1 puo' essere visto come RAID5 con solo 2 dischi anche se non puo' funzionare
    - La root partition sta comunque usando meta' partizione, quindi bisogna informare la partizione che puo' essere estesa (raddoppiandola)
    - Una volta si usava l'xfs: file system della silicon graphics permetteva la deframmentazione, il journaling, e anche l'incremento della dimensione della partizione in linea
    - Anche la swap deve essere raddoppiata
- Da riga di comando il terzo disco deve essere allacciato alla macchina e con dmesg il disco deve essere riconosciuto
    - Deve essere subito partizionato
    - `sfdisk -d /dev/sda` esegue il dump dalla tabella di partizioni
    - Con sfdisk posso copaire la tabella di partizioni da un disco all'altro
    - `sfdisk -d /dev/sda | sfdisk /dev/sdc`

## Migrazione da RAID 1 a RAID 5

https://wiki.archlinux.org/index.php/Convert_a_single_drive_system_to_RAID  
https://serverfault.com/questions/32709/how-do-i-move-a-linux-software-raid-to-a-new-machine#32721

- La macchina deve rimanere funzionante
- Eseguire prima:

    ```bash
    #mostra i raid
    cat /proc/mdstat
    #mostra lo spazio disponibile
    df -h
    #mostra la swap
    free
    ```
- Eseguire durante la migrazione:

    ```bash
    su -
    dmesg -wH
    ```

1. Aggiungere un altro disco su VirtualBox
    1. disco da 4GB
    1. hot-pluggable
1. Andare nella macchina virtuale sempre accesa durante questi passaggi

    ```bash
    su -
    sfdisk -d /dev/sda #dump della tabella delle partizioni
    sfdisk -d /dev/sda | sfdisk /dev/sdb #copia la tabella delle partizioni
    ```

    1. Installare grub

    ```bash
    upgrade-from-grub-legacy
    cfdisk /dev/sdc #rendere il disco bootabile in caso di problemi
    ```


1. Assegnare il raid anche al nuovo disco

    ```bash
    mdadm /dev/md1 --add /dev/sdc1
    mdadm /dev/md2 --add /dev/sdc2
    ```

1. Passare da RAID 1 a RAID 5

    ```bash
    mdadm /dev/md2 --grow --raid-devices=3 --level=5
    cat /proc/partitions
    df
    ```

1. Ora bisogna ridimensionare la partizione di root

    ```bash
    resize2fs /dev/md1
    #prende la dimensione attuale del file system e la dimensione reale del dispositivo a blocchi
    df #root passa dal ~37% al ~19% di disco usato
    ```

1. Rimuovere la partizione di swap se non utilizzata

    ```bash
    cat /etc/fstab #copiare l'UUID
    swapoff -a #disattiva tutte le memorie di scambio mappate nell'fstab
    ```

    1. Riabilitare la swap ricreandola

        ```bash
        mkswap -U UUIDCOPIATODAPRIMA /dev/md2
        swapon -a
        ```
      
1. Controllare se e' tutto apposto

    ```bash
    ls -l /dev/disk/by-uuid/ #mostra tutti gli identificativi delle partizioni
    ```

---
---
---

## Dimensione e astrazione dei dischi (Logical Volume Management)

> Carpa giapponese: questo pesce adatta le sue caratteristiche in base all'ambiente in cui si trova, se sa di essere in un ambiente ridotto limita la dimensione del proprio corpo. Se l'ambiente si espande anche il pesce cresce fino ad un limite

### Creare una macchina virtuale da espandere

In base alle esigenze faccio crescere la dimensione della macchina virtuale.

#### Obbiettivo

Normalmente la partizione di root ext4 era in sda1 e la swap nella sda2.


#### Macchina virtuale debian

- 1 GB
- Disco da 3 GB (apposta) (con 4 porte per aggiunte di altri dischi)
- Scheda di rete con bridge
- Installazione esperta
    - Selezione lingua
    - Rete automatica
    - nomehost: pescerosso
    - distro stable
    - componenti aggiuntivi
        - network-console (per installazione via ssh)
    - proseguire l'installazione in remoto
        - ssh installer@nomemacchina
    - Impostazione utenti e password
        - lasolita
        - Utente di Servizio
        - uds
        - lasolita
    - Orologio settato su Europa
    - Partizionamento del disco
        - partizione unica
        - Volume fisico per LVM (Logical Volume Management)
        - Configurare l'LVM
            - Mostra dettagli di configurazione
            - Creare gruppi di volumi
            - alleszusamme (VG o Volume Group usa solo sda1)
            - Creare volume logico
            - Nome: linuxroot
            - Dimensione: 2200MB
            - Creare volume logico
            - Nome: swap
            - Dimensione: 512MB
            - Creare volume logico
            - linuxhome
            - Dimensione: 500MB
            - Mostra dettagli di configurazione
            - lvmroot
            - lvmhome
            - swap
        - Con il sistema LVM linux gestisce le partizioni non direttamente collegate al disco fisico, permettendo ridimensionamenti conmm piu' liberta'

##### Comandi per vedere lo stato dell'LVM

```bash
mount
cd /dev/mapper
ls
df
free
cat /proc/swaps
```

Al posto di avere /dev/sda1/root si ha /dev/mapper/alleszusamme-linuxroot e GRUB non ha problemi a riconoscere l'LVM se mbr, in caso di EFI serve la partizione dedicata richiesta da sistemi U/EFI

#### Aggiunta di un altro disco sdb1 (LVM)

Il Volume Group deve espandersi prendendo anche il secondo disco fisico, ampliando di molto la home(LV) e la swap(LV)

Dimensione obbiettivo:
- linuxroot: 2.2GB
- swap: 1GB
- home: 3GB
- spazio libero rimanente serve in caso di necessita' future

E' possibile di ignorare dischi, aumentare il numero di dischi

Configurare uds e sudo

```bash
su -
apt install sudo joe
ip addr
adduser uds sudo
```

Mostrare le informazioni delle partizioni e dell'LVM

```bash
ssh uds@clientX
sudo -s
lvdisplay #mostra tutti i volumi logici
vgdisplay # mostra i volume group
```

Per ridimensionare le partizioni:

```bash
resize2fs --help
```

##### Impostare Virtualbox per aggiungere il disco

- Aggiungere un nuovo disco
    - PesceRossoB
    - 4 GB
- Avviare la macchina
- login
- controllare le partizioni

```bash
cat /proc/partitions
cd /dev/disk/by-uuid
ls -la
cd /dev/disk/by-label #etichette della lvm a livello di partizione
ls -la
```

> UUID e' un dato virtuale che esiste solo in una partizione formattata da un filesystem.

```bash
cd /dev/disk/by-id
ls -la
```

> ID e' a livello fisico e identifica le partizioni ma soprattutto il disk manager, marca e modello dei dischi.

Livelli:

1. Dispositivi a blocchi identificati con sda, sdb, ... (ID della partizione inserito nel disco durante la creazione)
1. Volume Group
1. Logical Volume mappati dal VG con dm-0, dm-1, ...
1. linuxhome, linuxroot, swap
1. formattazione delle partizioni (UUID e Label come lvmroot, lvmhome, ...)

##### Aggiunta del disco per LVM

Partizioni linux:
- 82 linux swap
- 85 ext
- fd Linux raid autodetect
- 8e Linux LVM

1. formattare il disco

```bash
sudo -s
wipefs /dev/sdb #attenzione! elimina i dati della partizione 
cfdisk /dev/sdb
```

1. partizione mbr
1. Type
    1. 8e

1. controllare che sia tutto apposto

```bash
cat /proc/partitions
vgdisplay #mostra VG UUID
dpkg -l lvm*
dpkg -L lvm2 | less #file che compongono il pacchetto: pv (physical volume), vg (virtual group), lv (logical volume),
```

1. Inizializzare il disco fisico

```bash
pvcreate /dev/sdb1
pvdisplay #manca il collegamento del disco al VG
vgextend VGNAME /dev/sdb1
pvdisplay #pra mache sdb1 fa parte del VG
vgsize #ora e' la somma della dimensione dei due dischi, manca il resize della LV
man lvresize 
man lvextend #quello che server
df #home da redimensionare
lvexend --size 3G alleszusamme/linuxhome #LV ridimensionato, ora manca la formattazione
lvdisplay
df -h #lvmhome in ext4 e' ancora come prima
resize2fs /dev/alleszusamme/linuxhome
df -h #linuxhome ridimensionata
vgdisplay #mostrano solo 5.5GB allocati, quindi bisogna ampliare anche linuxroot
lvextend --size 3G alleszusamme/linuxroot
df #quantita' di dati usati differenta 
resize2fs /dev/alleszusamme/linuxroot
vgdisplay #lo spazio rimanente serve per partizioni future
sync
```

Anche con LVM e' possibile gestire il RAID 1 software

#### Con LVM aggiungere terzo disco che sostituisce il secondo rotto

TODO
