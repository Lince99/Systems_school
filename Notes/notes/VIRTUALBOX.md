---
title: VIRTUALBOX
created: '2019-09-26T08:50:05.352Z'
modified: '2019-10-02T09:43:30.341Z'
---

# VIRTUALBOX

## CLIENT

### Configurazione:

clientcognome lasolita
Debian (64bit)
RAM 1MB
HDD 4 GB
NAT
https://www.debian.org/distrib/netinst

**Screenshot: CTRL DX + E**

**Clonazione: CTRL DX + T**

1. Creazione macchina virtuale
1. abilitare Network con NAT
1. expert install
1. Choose language
  1. Italiano
  1. Italia - it_IT.UTF-8
  1. it_IT e it_IT@euro
  1. UTF8
1. Configurazione tastiera
  1. Italiana
1. Caricare i componenti del programma
  1. nessun software
1. Rilevare l'hardware di rete
1. Configurare la rete
  1. DHCP
    1. Si
    1. 3
    1. hostname = cognome.intra
1. Scelta distribuzione
  1. http
  1. Italy
  1. ftp.it.debian.org
  1. Archivio Debian: buster - stable
    (testing, unstable, experimental sono le rolling release)
1. Scaricare componenti del programma installazione
  1. Modalità esperta permette di installare i programmi dall'immagine ISO
1. Password e utenti
  1. nomi e password erano nello stesso file, ora sono separati
  1. "shadow passowrd" abilitato (Sì)
  1. accesso a root abilitato (Sì)
    utente root deve essere in possesso di una sola persona (GDPR)
  1. password: lasolita
  1. Creazione utente normale:
    1. Utente Di Servizio
    1. uds
    1. lasolita
1. Configurare orologio 
    (RTC = real time clock a batteria, GPS via satellite manda l'ora e localizzazione, Orologio telecontrollato di Francoforte)
  1. NTP = Si
    1. Consigliato (italiano)
    1. Europe/Rome (UTC Greenwich +1 inverno, +2 estate, CEST (central europe standard time))
1. Rilevare dischi (auto)
1. Partizionamento dei dischi
  - permette di usare il terminale grazie al multiplexing - 6 terminali + altre grafiche (CTRL+ALT+F1 F2 F3... F9(su pc lab))
  - ALT+F1 su VM
  1. Manuale
    1. HDD nuovo da partizionare
      - gpt e mbr
      1. Partizioni primarie
        1. esteso
          1. partizioni logiche
      - 2TB e avvio OS EFI con partizionamento gpt (senza limiti sul partizionamento)
      - tabella del partizionamento presente all'inizio del disco (gpt copiata anche a senso inverso alla fine del disco)
      1. SCSI (0,0,0) (sda) - 10,7 GB
        1. msdos
          1. SPAZIO LIBERO
          1. Creare nuova paritzione
            1. 4.0 GB
            1. Primaria (mbr)
            1. Inizio
                - btrfs per i dischi flash per sistemi ibridi, FAT va a leggere i dati nella prima parte chiavetta usurandola
            1. Usare come ext4 (estesa con journaling)
            1. Punti di mount: / (cartella di root)
              - mount: attacca il disco nel tree delle directory
              - root, home, swap
            1. attivare nelle opzioni di mount:
            1. discard: rimuovere un file: dereferenziazione per poi essere sovrascritto da altri file, informa il disco della cancellazione, durante i periodi di inattività cancella i settori marchiati "discard"
              - dispositivi flash: scrivere e riscrivere: cancellazione costa risorse su zone già scritte
            1. noatime: lettura dei file: scrive le date (accesso, creazione, modifica, ...) sul file letto, quindi scrive e rallenta = alcuni servizi necessitano la gestione di atime (orario di accesso).
            1. etichetta: linuxroot
            1. Flag avviabile: utilizzato da DOS
            1. Impostazione della partizione completata
        1. SPAZIO LIBERO
          1. Primaria
          1. Fine
          1. Area di swap: (memoria virtuale in winzoz), se la RAM è occupata va ad utilizzare il disco nella partizione dedicata
        1. Terminare le modifiche
          1. Yep
      1. Sistema di base
        1. scelta del kernel: linux-image-amd64 (ultimo kernel stabile)
        1. generico (mappatura del disco all'avvio, driver autoconfigurati)
      1. Gestore dei pacchetti
        1. No (solo software libero)
        1. Si Software contrib (software libero con parti non libere) (installazione di Adobe Flash Player (libreria), (Font proprietari Microsoft)
        1. No repository sorgenti APT
        1. Continua
      1. Selezione installazione software:
        1. Deselezionare tutto
        1. Abilitare pacchetti VirtualBox
        1. Nessun auto update
        1. No partecipare alle statistiche
        1. Deseleziona tutto
      1. Installare Boot loader GRUB (GRUB è un OS per avviare gli altri OS)
        1. Installare boot loader GRUB nel master boot record (prima parte del disco che serve ad avviare l'OS)
          - BIOS legacy: letto primo settore del disco e viene mandato in esecuzione
          - BIOS EFI: legge il disco per trovare partizioni EFI, carica un file EFI in memoria
      1. Si
      1. /dev/sda
      1. Forzare l'installazione di GRUB su dispositivo rimovibile EFI? No
        - EFI: partizionamento da 100 MB nella prima parte del disco formattato in gpt
  1. Terminare l'installazione
    1. Orologio di sistema da impostare su UTC? Si
      - Winzoz: locale
      - Linux: UTC
      1. Continua
  - (RIMUOVERE IL CD DAL LETTORE VIRTUALE SE USATA UNA ISO)

1. Debian GNU/Linux
  1. TAB COMPLETITION: doppio tab per completare le parole sul terminale
  1. Segnalazione dell'integrazione del puntatore del mouse
  1. clientcognome login: uds
  1. password: lasolita
  1. UTENTE NORMALE
    1. pwd : print working directory
    1. df -h : visualizza lo stato dell'hard disk
    1. sudo : super user do often
    1. su - : super user
    1. password di root: lasolita
  1. UTENTE ROOT
    1. apt update
    1. apt upgrade
    1. (in caso di problemi: nano /etc/apt/sources.list)
```
deb http://deb.debian.org/debian buster main
deb-src http://deb.debian.org/debian buster main

deb http://deb.debian.org/debian-security/ buster/updates main
deb-src http://deb.debian.org/debian-security/ buster/updates main

deb http://deb.debian.org/debian buster-updates main
deb-src http://deb.debian.org/debian buster-updates main
```
  1. apt install less joe tcpdump mtr-tiny cowsay (opzionali: bash-completion, dnsutils, netcat)
      - pacchetti aggiuntivi: librerie mancanti per i programmi selezionati --> DIPENDENZE INCLUSIVE
      - contesa dei software: propone la scelta, configurandone la scelta scartata --> DIPENDENZE ESCLUSIVE
      1. S
      1. cowsay : non funziona perchè i giochi non esistono per root 
      1. apt install sudo
      - SUDO permette di usufruire di azioni da amministratore da parte dell'utente normale senza sapere la password di root ma usando la propria (Wireshark richiede accesso hardware alla scheda di rete)
      - crea gruppo sudo
      1. id : mostra i gruppi a cui appartiene l'utente corrent
      1. id uds : mostra i gruppi a cui appartiene all'utente
      1. adduser uds sudo : iscrive un utente al gruppo
      1. id uds : ricontrollo se è su sudo 
      1. exit
      1. id
      1. exit
      1. relogin con uds lasolita
      1. id : ora uds è sudo
      1. sudo -s
        1. password
      1. apt clean : configurazione di sistema non viene rimossa, nel caso di una reinstallazione la configurazione rimuove i file superflui
      1. apt purge nomeprogramma : rimuove programma, config di sistema MA non configurazione utente
    1. CREARE IL SERVER
      1. spegnere la macchina da amministratore
        1. la GUI da la possibilità di spegnere la macchina da sudo, mentre da CLI serve per forza sudo
        1. shutdown -h now (oppure sudo shutdown -h now da utente uds)
      1. clonare la macchina virtuale
        1. CTRL + O o Pecora Dolly nel menu a tendina
        1. servercognome
        1. ABILITARE "Inizializza nuovamente l'indirizzo MAC di tutte le schede di rete", (serve per sperimentare lo stesso sistema su sistemi differenti ma con MAC uguale)
        1. Scegliere "Clone completo", copia tutti i file come disco separato.
        1. nome sbagliato: modificare /etc/hostname: (i processi prendono l'hostname all'avvio, quindi lo mantengono durante l'esecuzione anche se nel durante viene modificato)
          1. login uds
          1. joe /etc/hostname
          1. mettere servercognome invece di clientcognome
          1. CTRL+K e poi X
          1. modificare file /etc/hosts
          1. 127.0.0.1 = localhost (127.0.1.1 = sempre indirizzi di loopback (max 16 milioni))
          1. ping 127.0.x.x
          1. shutdown -h now

1. Creare nuova macchina per monowall
  1. routercognome
  1. BSD
  1. FreeBSD (32-bit)
  1. RAM = 128 MB
  1. HDD = 64 MB
  1. Seleziona disco di avvio:
    1. /home/itis/InternetFiles/m0n0wall-generic-pc-1.8.1.iso
    1. avvia e poi subito F12
  1. Menu di monowall (può funzionare solo con floppy (config ) e CD (OS))
    1. 7 - Install on HDD
    1. ad0
    1. y
    1. al riavvio spegnere subito
    1. togliere CD da virtualbox


## Robe utili:

1. FHS
  1. https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard
  1. dove sono i file nel filesystem linux
  1. sotto /etc/apt/sources.list o cartella sources.list.d/...
    1. in Debian si trovano delle configurazioni modulari = installare un software ha eseguibili, configurazioni e .deb per la configurazione iniziale
    1. aggiunge alla configurazione precedente
    1. ESEMPIO: scaricare Firefox, plugin installabili in maniera centralizzata, passando la configurazione nella sottocartella del file di configurazione di Firefox.
    1. FILE SOURCES.LIST contiene le configurazioni di dove trovare gli aggiornamenti Debian
    1. Commentare riga contenente gli aggiornamenti via CD
    1. apt update: scarica l'elenco del software per il controllo delle versioni
    1. apt upgrade: scarica il software aggiornato, momento delicato poichè deve seguire una scaletta di dipendenze
    1. aggiornamento della versione di Debian: tutte le dipendenze rischiano di rompere l'upgrade (dependency hell)
      1. dist-upgrade: esegue l'upgrade senza dare peso alle dipendenze, però portando ad interruzioni di servizio

1. Usando il CD a casa richiede se si vuole scaricare dal CD o dalla rete, per rendere indipendente la macchina dall'uso del CD:
  1. source

1. echo $TERM : stampa il nome del terminale
1. CTRL+D : uscire dall'utente
1. nano .bashrc:
```
case "$TERM" in
  xterm-color|linux|...

alias shutdown=/sbin/shutdown
```

  1. LIBRERIE
    - Eseguibile su winzoz: avanti forever e poi viene installato il programma con le liberie necessarie per ogni programma (Firefox e Thunderbird hanno le stesse librerie, vengono scaricate 2 volte e vengono trattate in modo differente)
    - Programma in linux: i gestori delle distribuzioni modificano le librerie per il proprio sistema con risoluzione di problemi di compatibilità, rendendole univoche nel sistema. (per Debian ci sono i tester, obbiettivo: risparmiare trasmissione dati, i pacchettatori prendevano i vari software esistenti per analizzarne le librerie richieste, senza avere il bisogno di riscaricarle anche negli aggiornamenti) (ci possono essere varie versioni nello stesso sistema)
    Android: il Play store colleziona software adatto al sistema insieme alle loro liberie
      - DEBIAN usa .deb (creato da Ian Mardock, Deb "Deborah" Ian)
      - DPKG gestore di file
        - vincoli di dipendenze (con limiti sulle versioni)
      - APT
        - utilizza dpkg
        - retrocompatibile con i comandi dpkg
      - deb: i pacchetti includono sia il programma che i file configurazione standard per l'autoconfigurazione durante l'installazione
      - deborphan: cerca le librerie orfane, non necessarie a nessun software
      deb auto... : rimuove le librerie inutilizzate in automatico

```
cat /etc/shadow
```

```
sudo nano /etc/profile
# aggiungere :/usr/sbin dopo PATH
```


#### TODO:
- clonare client, configurare clone e rinominarlo SERVER
- cron e anacron
