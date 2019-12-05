---
title: RELAZIONE_VIRTUALBOX
created: '2019-09-26T08:50:05.352Z'
modified: '2019-12-05T11:11:33.297Z'
---

# Virtualbox, M0n0wall e l'architettura client-server {#top}

---

## INTRODUZIONE [↑](#top)

#### Descrizione VirtualBox

![Virtualbox logo](https://www.virtualbox.org/graphics/vbox_logo2_gradient.png)

Virtualbox è un software che ci permette di emulare il funzionamento di altri sistemi operativi
al di sopra di un altro che sarà il nostro "pc ospite".

#### Descrizione M0n0wall

![M0n0wall logo](https://m0n0.ch/images/m0n0wall.gif)

M0n0wall è un sistema operativo open source ora abbandonato che ci permette di gestire
tutti gli aspetti avanzati di un router.

#### Obbiettivo

Riuscire a creare un laboratorio virtuale completo:
- router con firewall, NAT e DMZ
- server fruitore di servizi in locale e all'esterno verso il laboratorio fisico
- svariati client virtuali, tra i quali alcuni vulnerabili per svariati attacchi da provare

#### Informazioni aggiuntive


---

## Utilità [↑](#top)

### Download links

[Distribuzione debian](https://www.debian.org/distrib/netinst)

### Funzioni utili Virtualbox

Screenshot Virtualbox: **R-CTRL + E**  
Clonazione Virtualbox: **R-CTRL + T**

---

## Creazione VM Client [↑](#top)

#### Informazioni generali

- nome VM = clientcognome
- password per tutto = lasolita
- Debian (64bit)
- RAM 1 GB
- HDD 4 GB (4.0 GB root, 368 MB swap)
- Rete con NAT

### Installazione OS client [↑](#top)

1. Creazione macchina virtuale
    <!--![Screenshot VM server](https://raw.githubusercontent.com/Lince99/Systems_school/master/Notes/notes/screenshots/Screen_VM_server_config_0.png)
    > Creazione server-->
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
    1. Archivio Debian: buster - stable (testing, unstable, experimental sono le rolling release)
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
    1. Configurare orologio (RTC = real time clock a batteria, GPS via satellite manda l'ora e localizzazione, Orologio telecontrollato di Francoforte)
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

### Configurazione OS Client [↑](#top)

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
    ```bash
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

## Creazione VM Server [↑](#top)

1. Server debian
    1. spegnere la macchina da amministratore
        1. la GUI da la possibilità di spegnere la macchina da sudo, mentre da CLI serve per forza sudo
        1. shutdown -h now (oppure sudo shutdown -h now da utente uds)
    1. clonare la macchina virtuale *clientcognome*
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

## Creazione VM Router [↑](#top)

1. Creare nuova macchina per monowall
    1. configurazione macchina virtuale:
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
        1. Archiviazione
            1. CD: rimuovi disco dal lettore
    1. Scheda di rete 1
        1. Scheda con Bridge
            1. br0 (a scuola)
    1. Scheda di rete 2
        1. Rete interna
            1. LAN
    1. Scheda di rete 3
        1. Rete interna
            1. DMZ
    1. riconosce che esiste un HDD non visualizzando la voce 7 dal menu
    1. Non sono etichettate le porte LAN, WAN e DMZ
        1. 1 (Interfaces: assign network ports) (ci devono essere 3 interfacce: em0 em1 em2)
        1. osservare i MAC address nelle impostazioni di rete di VirtualBox se sono in ordine come su monowall
        1. richiesta di abilitare VLAN? n (è possibile avere monowall con 1 sola interfaccia e con VLAN attive per avere più reti)
        1. LAN interface: em1
        1. WAN interface: em0 (monowall si accontenta di 2 interfacce, ma useremo anche la DMZ)
        1. opzionali: em2
        1. ENTER
        1. confermare? y (punto delicato: a casa usa DHCP, in laboratorio viene aggiunto un server DHCP in più, creando caos nello stesso dominio di broadcast. Peroò due server DHCP possono distribuire una porzione di indirizzi)
        1. ENTER (per dare un'indirizzo IP alla WAN, monowall ha inviato una richiesta DHCP nella rete presente)
        1. Ora bisogna configurare gli host

---

### Grafica sul Client [↑](#top)

1. Avviare il clientcognome
    1. entrare con uds
    1. sudo bash
    1. serve gestore login grafico o desktop manager (mdm = mint desktop manager, lightdm = light desktop manager, kdm = kde desktop manager, nodm = avvia in automatico la sessione)
    1. serve un desktop enviroment (mate, lxqt, kde)
    1. serve il browser (firefox-esr è il nome del pacchetto creato per un litigio tra Mozilla e Debian per il logo (panda rosso), ora include patch sia da )
        1. apt install lightdm mate firefox-esr
        1. S
        1. apt install firefox-esr-l10n-it (lingua italiana)
    1. ora i pacchetti non servono più
        1. apt clean
    1. Linux quando parte c'è il kernel che passa il comando ad un gestore di sistema (init) che lancia una serie di script, ora esiste systemd, basato su un eseguibile parallelo
    1. E' possibile manovrare i singoli servizi da amministratori con:
        1. in /etc/init.d/... ci sono vari file eseguibili con configuratori (console-setup) e anche processi grafici
        1. /etc/init.d/lightdm status (gestito da systemd)
    1. /etc/init.d/lightdm restart (avvia l'interfaccia grafica)
        1. accedere come uds
        1. avviare firefox
        1. andare sulle impostazioni di rete del client di Virtualbox
            1. Collegare Rete interna e mettere LAN
        1. aprire terminale MATE
            1. ip addr
            1. sudo bash
            1. /etc/init.d/networking stop
            1. (PLEASE WAIT UNTIL OUR PROF RESOLVE THE PROBLEM...)
            1. lanciare a mano la richiesta DHCP
                1. dhclient enp0s3
                1. viene assegnato 192.168.1.100 (ciascuno è dentro la propria rete LAN distaccata da quella del laboratorio)

### Configurazione M0n0wall [↑](#top)

1. tornare su Firefox
    1. 192.168.1.1 sulla barra di ricerca per accedere alla pagina di gestione del router m0n0wall
        1. admin
    1. mono
    1. possibilità di configurazione del router via web attraverso il client o i computer presenti in LAN
    1. per questione di sicurezza è possibile modificare le impostazioni del router tramite una regola di controllo da parte del PC ospitante
        1. Firewall -> rules -> (e)
            1. disabilitare spunta Block.. (infondo)
        1. Firewall -> rules -> +
            1. Single host or alias
            1. Destination: WAN address
            1. inserire proprio IP
            1. porte from: 80 to: 80
            1. Description: Allow: ....
        1. Apply changes
    1. Andare sul browser dell'host e scrivere l'indirizzo della WAN da Status -> Interfaces
        1. Impostare proxy su auto su firefox
        1. accedere con admin mono
        1. System -> general setup
            1. hostaname: routercognome
            1. domain: cognome.intra
            1. lasciare spunta Allow DNS...
            1. user: admin
            1. password: lasolita
            1. time zone: Europe/Rome
            1. Save
            1. loggare con admin lasolita
        1. firmware: possiblità di aggiornare monowall via web
        1. System -> Advanced
            1. possibilità di attivare la modalità access point
        1. System -> User manager
            1. permette di creare un gruppo di utenti con delle regole di accesso, per creare voucher e altro
        1. Interfaces (assign)
            1. permette di ricalibrare le interfacce di rete, VLAN e WLAN
        1. Interfaces -> LAN
            1. permette di modificare il range di indirizzi
        1. Interfaces -> WAN
            1. DHCP -> hostname: routercognome
            1. Save
        1. Interfaces -> OPT1
            1. Enable
            1. DMZ (è possibile mettere in bridge monowall, ma DMZ deve essere indipendente dalla LAN)
            1. IP address: 192.168.101.1 / 24
            1. Save
            1. "Note: be sure to add firewall rules to permit traffic through the interface." (da configurare il firewall)
        1. Firewall -> Rules -> LAN
            1. (valido solo per BSD e non per iptables) Le regole sono valutate in ordine discendente (da sopra a sotto)
            1. Default: permette tutto
        1. Firewall -> Rules -> DMZ -> +
            1. Action: block
            1. protocol: any
            1. Source: DMZ subnet
            1. Destination: LAN subnet
            1. Description: Block: DMZ to LAN
            1. Save
        1. + sotto la (e)
            1. Pass
            1. Destination: any
            1. Description: Allow: DMZ to any
        1. Apply changes
            - I computer DMZ possono andare su tutta internet? NO: se il DMZ viene "conquistato" bisogna bloccare le connessioni con un firewall che non cercano direttamente un proxy specificato o un DNS personale.
        1. Status -> traffic graph
        1. Diagnostics -> Logs
        1. Diagnostics -> DHCP leases ()
        1. Diagnostics -> ARP table (MAC registrati)
        1. Diagnostics -> Backup/Restore (XML)
            1. Download configuration
        1. Diagnostics -> Factory Defaults (pulisce l'intera configurazione)

---

## Configurare la rete [↑](#top)

### Impostare l'ip del client

1. Rilanciare il router
1. Svegliare il client
    1. apt install anacron (opzionale)
    1. dal browser
        1. 192.168.1.1
        1. admin lasolita
        1. Services -> DHCP Server -> DMZ -> [x] Enable
        1. Range: 192.168.101.100 al 192.168.101.199
        1. Save

### Impostare DMZ nel router [↑](#top)

1. Configurare il server
    1. Rete -> Scheda 1 -> Rete interna DMZ
    1. Avviare il server
        1. uds lasolita
        1. testare la rete con ping 1.1.1.1
        1. FASE DI COLLAUDO:
            1. CONTROLLARE STACK ISO/OSI DAL LIVELLO 0
                1. scheda di rete fisica
                1. arp
                1. ping
                1. servizi
                1. dns e ip
                1. software
            1. essendoci delle regole di firewall bisogna collaudarlo (ordine delle righe sbagliate, DMZ, regole di blocco)
            1. sul router Diagnostics -> DHCP leases
            1. sul client pingare il server
                1. ping 192.168.101.100
            1. testare se server pinga il client
                1. ping 192.168.1.100
            1. test dei nomi di dominio nel client ([x] riuscita)
                1. ping www.e-fermi.it
            1. test dei nomi di dominio nel server
                1. ping www.e-fermi.it
        1. **/etc/resolv.conf**
            1. file ad attuazione immediata, serve per i programmi per trovare il DNS
            1. modifica manuale, ma il DHCP va a riscrivere tutto il file (usare solo in caso di disattivazione di DHCP)
            1. mostra dominio
            1. mostra quale server viene usato come dns (client .1.1, server .101.1), la regola di firewall vieta l'accesso alla DMZ verso la 192.168.1.x
    1. installare sul client e sul server
        1. sudo apt install ssh (metapacchetto, crea solo dipendenze come openssh client e server e altro)(dropbear alternativa ad ssh)
    1. verificare la possibilità di fare ssh da client a server e l'impossibilità di fare ssh dal server al client
        1. client
            1. ssh uds@192.168.101.100
            1. certificato SHA256: yes (usato per verificare l'autenticità del server)
        1. server
            1. ssh uds@192.168.1.100 (non deve funzionare)

### Applicare modifiche della rete [↑](#top)

1. Riavviare macchine virtuali
1. Il client deve identificare il server sempre con lo stesso indirizzo
    1. ip addr sul client: 192.168.1.100 e mostra il mac
    1. ip addr sul server: 192.168.101.100 e mostra il mac
    1. sulla configurazione del router:
        1. Diagnostics -> ARP table
        1. Services -> DHCP Server -> DMZ -> Reservations
        1. Possibilità di assegnare lo stesso ip ad una macchina specifica tramite indirizzo MAC
            1. MAC del server
            1. 192.168.101.250 (fuori dal range DHCP poichè al server necessita un indirizzo ip statico anche per i successivi riavvii)
            1. Ip statico del server
            1. "Deny unknown clients" Only respond to reserved clients listed below. LASCIARE DISATTIVATA (il firewall si occupa degli indirizzi esterni, DMZ per il range di indirizzi locali, no MAC, no IP)

---

## Aggiungere regole in M0n0wall [↑](#top)

1. aliases:
    1. Firewall -> Rules
        1. WAN ha solo il PC fisico
        1. Possibilità di aggiungere più regole di firewall allo stesso indirizzo IP, senza andare a modificare tutte le regole di firewall riguardanti quell'IP
        1. Firewall -> Aliases
            1. host-pcospitante
            1. 172.30.4.x
            1. Il computer da cui opero
          1. tornare in Firewall -> Rules
          1. modificare la regola WAN
              1. Source
              1. Type: Single host or alias
              1. host-pcospitante
          1. Tutti con regole uguali, ma con alias diversi. Questo permette di configurare diversamente i router ma con alias uguali. D'ora in poi le regole di firewall vanno fatte con alias standardizzati: WAN-descrizione LAN-descrizione HOST-descrizione-interfaccia
      1. creare un altro alias:
          1. lan-labsistemi
          1. Network
              1. 172.30.4.0/24 (a casa 192.168.1.1/24)
          1. La rete in cui appoggia la mia WAN
1. Studiare la migrazione degli indirizzi completa del laboratorio senza console server e router, temporizzare i riavvii con cambi di opzioni di monowall, client avrà indirizzo corretto al rinnovo richiesta DHCP
    1. socchiudere monowall
    1. server via ssh, quindi exit e socchiudere il server
    1. lasciare aperto solo il client
    1. usare ssh sul client e web
    1. attenzione: timing DHCP, ordine degli eventi, documentare tutto
    1. SNAPSHOT di tutte le macchine virtuali, salvare configurazione monowall nel client e in piattaforma (Istantanea 1, descrizione: pre-antartide)
    1. 192.168.x.0/24 LAN lab virtuale (192.168.11./24)
    1. 192.168.100+x.0/24 DMZ lab virtuale (192.168.111.0/24)

1. Impostare IP statico:
    1. nano /etc/network/interfaces
    1. dhcp to static
    1. address 192.168.x.2/24
    1. gateway 192.168.x.1
1. Pure nel server, ma con 192.168.100+x.2/24 e gateway .1
1. In monowall
    1. Interfaces
    1. Ip di gateway di LAN e DMZ
    1. Server DHCP
        1. LAN cambiare range in .x.100 e .x.199
        1. LAN cambiare range in .100+x.100 e .100+x.199

## Migrazione IP [↑](#top)

1. Nel SERVER da client in ssh
    1. ssh uds@192.168.101.250
    1. su -
    1. nano /etc/network/interfaces
        1. ... inet static
        1. address 192.168.100+x.250/24
           gateway 192.168.100+x.1
        1. ifup enp0s3
1. In M0n0wall
    1. Interfaces -> DMZ
        1. IP address = 192.168.111.1/24
    1. Services -> DHCP Server -> DMZ
        1. Range 192.168.111.100 to 192.168.111.199
        1. Reservations da 192.168.101.250 a 192.168.111.250
    1. Interfaces -> LAN (NON RIAVVIARE)
        1. IP 192.168.11.1/24
    1. Services -> DHCP Server -> LAN
        1. Enable
        1. Range 192.168.11.100 to 192.168.11.199
    1. Reboot system
1. Nel client
    1. ifup enp0s3
    1. testare il server
        1. ping 192.168.111.250
    1. testare la rete
        1. ping 1.1.1.1
    1. dal server pingare l'esterno
        1. ssh uds@192.168.111.250
        1. ping 1.1.1.1

- DHCP è debole:
    - boot da rete del lab: server fa anche da DHCP, si può osservare il server ufficiale, mandare un pacchetto UDP durante l'avvio che aggiunge le opzioni di avvio da rete del sistema operativo
    - nel caso di manutenzione di ip statici, questo stratagemma permette di ottenere sempre lo stesso indirizzo del DHCP

## Restrizioni aggiuntive sul firewall [↑](#top)

### Condizioni

- Sia il client che il server devono essere protetti da virus
(cercano di inibire chi li sconfigge, anti-antivirus)
- Firewall esterno devono proteggere sia LAN che DMZ
anche nel caso uno dei due o entrambi siano stati attaccati e vogliono diffondersi

- Da LAN a WAN: DNS riceve un nome e restituisce l'IP (elenco del telefono per la nonnina)
    - **IMPEDIRE IL CAMBIO DEL DNS**
    - chiamata telefono fisso tradizionale: il chiamante occupa il chiamato anche se il chiamato mette giù il telefono = truffa vecchio stile
    - Un client riceve il DNS dal router tramite la richiesta DHCP (dns livello applicazione, dhcp livello IP)
    - Client scrive il server DNS nel file /etc/resolve.conf, file continuamente riscritto dal router  
    Nel client cat /etc/resolv.conf
    - LAN deve permettere al servizio DNS di andare solo nel M0n0wall lato LAN, le altre richieste TCP/UDP per il DNS da tagliare
- Creare alias per host-server, host-router-lan, host-router-dmz

- LAN e WAN verso DMZ
    - DMZ esce solo con la porta 80 (ora solo porta 22 per SSH)
    - LAN può essere infettata
    - DMZ zona sicura dall'accesso sia da WAN che da LAN
    - DMZ deve dare accesso ad una lista di servizi, mentre il resto no (ora c'è Allow: DMZ to any)
    - permetti tutto dalla LAN alla DMZ disabilitata e da attivare in caso di manutenzione (descrizione: NORMALMENTE INATTIVA)

- DMZ verso LAN **PROIBITO**

- DMZ verso WAN
    - potrebbe ricevere attacchi anche da un ping fraudolento
    - Server ha bisogno di *rispondere* ad internet, non di *andare* verso internet
    - **VIETARE TRAFFICO IN BASE AL SERVIZIO**
        - minimo traffico ICMP
        - DNS verso il server giusto
        - NTP per l'orario (tempo in rete è importante, solo orologi fidati)
        - aggiornamenti, regola a scuola è differente da casa (apt-cache porta 3142 ip 172.30.1.199), a casa /etc/apt/sources ci sono gli indirizzi
        - /etc/apt/sources.list.d e il file pbiso.list aggiunge una fonte aggiuntiva oltre a sources, durante gli aggiornamenti controllerà anche questa repo
        - per windows esistono degli host per windows update

- Monowall -> Services -> Scheduler
    - Permette di limitare i servizi in certe fasce orarie

- Collaudare il DNS
Testare la rete anche con DNS diversi
```bash
host www.casettamia.it 8.8.8.8
```
- Al posto di bloccare le chiamate DNS illecite,
si può redirezionare con DNAT e rispondere con il server DNS ufficiale.

- NAT
    - indirizzi privati non possono andare su internet, poichè gli altri host non sanno come rispondere
    - IP sorgente dell'host privato viene sostituito con quello del router privato -> esce con IP pubblico -> traffico torna verso il router -> router ritorna il traffico all'ip privato dell'host

- DNAT
    - altero la destinazione
    - nel router si chiama port-forwarding, virtual-server, server-port, port-mapping, ...
    - DMZ con indirizzo pubblico, oppure se ha un indirizzo privato = ho solo l'ip pubblico del router
    - m0n0wall -> Firewall -> NAT -> Inbound
        - Regola di controllo del server da rete esterna (per teleassistenza, con la possibilità di accesso da solo alcuni IP statici (o aziendali o da server redirect))
        - from: SSH
        - NAT IP: host-server (accetta alias, ma attenzione)
        - Description: Server in SSH
        - Auto-add a firewall rule to permit traffic through this NAT rule (crea una regola permissiva da poi adattare nel firewall, solo in fase di creazione)
    - m0n0wall -> Firewall -> Rules
        - si vede l'aggiunta della regola di NAT
        - da modificare che permette di accedere al server solo dal pc ospitante (edit -> host-pcospitante)

- Installare il plugin Foxyproxy Standard sia nel pc ospitante che nel client
    - options (crea più profili proxy da switchare)
        - piu
            - diretto
            - #000000
            - Type: Direct (no proxy)
        - piu
            - scuola
            - #66cc66
            - 172.30.1.199
            - 3128
    - diretto -> patterns
        - se l'ip ha una forma usa un certo proxy, altrimenti usa l'altro
        - New White
            - Pattern: 192.168.*
    - permette di usare un proxy per gli ip locali, mentre
    - In firefox -> Preferenze -> nessun proxy

### Schema [↑](#top)

|  da/a      | LAN      |    WAN           |      DMZ   |
|:----------:|:--------:|:----------------:|:----------:|
| **LAN**    |  v       | v(dns)           |  v*2       |
| **WAN**    |  x       | v                | v*2(dnat)  |
| **DMZ**    |  x       | v(dns,ntp,http)  |  v         |

### Realizzazione [↑](#top)

#### Regole di NAT

| If | Proto | Ext. Port range | NAT IP | Int. port range | Descrizione |
|:--:|:-----:|:---------------:|:------:|:---------------:|-------------|
| WAN | TCP | 22 (SSH) | host-server | 22 (SSH) | Server in SSH |

#### Alias del firewall

| Nome | Indirizzo | Descrizione |
|------|-----------|-------------|
| host-pcospitante | 172.30.4.11 | Il computer da cui opero |
| host-router-dmz | 192.168.111.1 | Router M0n0wall DMZ |
| host-router-lan | 192.168.11.1 | Router M0n0wall LAN |
| host-server | 192.168.111.250 | Server in DMZ |
| lan-labsistemi | 172.30.4.0/24 | La rete in cui appoggia la mia WAN |

#### Regole firewall LAN

| Attivo | Proto | Source | Port | Destination | Port | Descr |
|:------:|:-----:|:------:|:----:|:-----------:|:----:|-------|
| X | TCP/UDP | LAN net | * | ! host-router-lan | 52 (DNS) | Block: LAN to LAN attack - DNS |
| V | TCP/UDP | LAN net | * | DMZ net | 80 (HTTP) | Pass: LAN to DMZ - HTTP |
| V | TCP/UDP | LAN net | * | DMZ net | 443 (HTTPS) | Pass: LAN to DMZ - HTTPS |
| V | TCP/UDP | LAN net | * | DMZ net | 22 (SSH) | Pass: LAN to DMZ - SSH |
| W |  |  |  |  |  | ! |
|  | R |  |  |  | ! |  |
|  |  | O |  | G |  |  |
|  |  |  | N |  |  |  |
| V | TCP/UDP | LAN net | any | DMZ net | 80 (HTTP) | Pass: LAN to DMZ - HTTP |
| V | TCP/UDP | LAN net | any | DMZ net | 443 (HTTPS) | Pass: LAN to DMZ - HTTPS |
| X | TCP/UDP | LAN net | any | DMZ net | * | Block: LAN to DMZ - any |
| X | TCP/UDP | any | any | ! host-router-lan | 53 (DNS) | Block: LAN to LAN attack - DNS |

#### Regole firewall WAN

| Attivo | Proto | Source | Port | Destination | Port | Descr |
|:------:|:-----:|:------:|:----:|:-----------:|:----:|-------|
| V | TCP | host-pcospitante | * | WAN address | 80 (HTTP) | Allow: accesso web al m0n0wall dal PC ospitante |
| V | TCP | host-pcospitante | * | host-server | 22 (SSH) | NAT Server in SSH |
| V | TCP/UDP | WAN address | * | DMZ net | 80 (HTTP) | Pass: WAN to DMZ - HTTP |
| V | TCP/UDP | WAN address | * | DMZ net | 443 (HTTPS) | Pass: WAN to DMZ - HTTPS |
| V | ICMP | * | * | WAN address | * | Pass: any to WAN - ICMP |  
| W |  |  |  |  |  | ! |
|  | R |  |  |  | ! |  |
|  |  | O |  | G |  |  |
|  |  |  | N |  |  |  |
| V | TCP | host-pcospitante | any | WAN address | 80 (HTTP) | Allow: accesso web al m0n0wall dal PC ospitante |
| V | TCP | any | any | host-server | 22 (SSH) | NAT Server in SSH |

#### Regole firewall DMZ

| Attivo | Proto | Source | Port | Destination | Port | Descr |
|:------:|:-----:|:------:|:----:|:-----------:|:----:|-------|
| X | * | DMZ net | * | LAN net | * | Block: DMZ to LAN any |
| V | ICMP | DMZ net | * | * | * | Pass: DMZ to any - ICMP |
| V | UDP | DMZ net | * | * | 53 (DNS) | Pass: DMZ to any - DNS |
| V | TCP | DMZ net | * | * | 123 | Pass: DMZ to apt-cacher - apt updates |
| W |  |  |  |  |  | ! |
|  | R |  |  |  | ! |  |
|  |  | O |  | G |  |  |
|  |  |  | N |  |  |  |
| X    | any | DMZ net | any | LAN net | any | Block: DMZ to LAN |


```
LAN to WAN: solo DNS in TCP/UDP

    TCP/UDP from LAN port NOT host-router-lan to WAN port 53 (Block: LAN to WAN - DNS)

LAN to DMZ: ammetti traffico HTTP e HTTPS solamente

    TCP/UDP from LAN port any to DMZ port 80 (Pass: LAN to DMZ - HTTP)
    TCP/UDP from LAN port any to DMZ port 443 (Pass: LAN to DMZ - HTTPS)

WAN to DMZ: ammetti traffico HTTP e HTTPS solamente

    TCP/UDP from WAN port any to DMZ port 80 (Pass: WAN to DMZ - HTTP)
    TCP/UDP from WAN port any to DMZ port 443 (Pass: WAN to DMZ - HTTPS)

WAN to LAN: blocca

DMZ to WAN: ammetti traffico ICMP, DNS, NTP (UDP 123), aggiornamenti (3142)

    protocol ICMP from DMZ port any to WAN port any (Pass: DMZ to WAN - ICMP)
    TCP/UDP from DMZ port any to WAN port 53 (Pass: DMZ to WAN - DNS)
    UDP from DMZ port any to WAN port 123 (Pass: DMZ to WAN - NTP)
    TCP/UDP from DMZ port any to WAN port 3142 (Pass: DMZ to WAN - Updates)

DMZ to client LAN port 2222

    (in LAN) TCP from DMZ port 2222 to LAN port 22 (Pass: DMZ to LAN client - SSH port 2222 (normally disabled) )
    (in DMZ) TCP from LAN client port 22 to DMZ port 2222 (Pass: DMZ to LAN client - SSH port 2222 (normally disabled) )

Dal server DMZ per connettersi al client usare il NAT tramite porta 2222 (scelta)
```

## Servizi per il server [↑](#top)

### Apache

- Indiscusso re del mercato del middleware, ora sono arrivati lighthttpd, nginix
- Servono a gestire i grandi flussi di dati e utenti con migliaia di richieste al secondo
- I contenuti dinamici forniti da vari server, mentre le parti statiche da altri server con tecnologie diverse (grande uso di cache)

#### Configurare la rete [↑](#top)

Sito web consultabile dall'esterno tramite l'IP del router, ora c'è M0n0wall in porta 80 **deve rimanere tale per la LAN**.  
Dall'esterno deve essere possibile vedere la pagina del server, senza togliere la gestione del M0n0wall dall'esterno tramite porta 8080.  


| da/a | apache | M0n0wall |
|:----:|:------:|:--------:|
| LAN  |   80   |   80     |
| WAN  | 80 restrict | 8080 restrict |

#### Installazione apache [↑](#top)

```bash
sudo apt install apache2
```

Modificare la pagina index

```bash
sudo nano /var/www/html/index.html
```

#### Configurazione apache con HTTPS [↑](#top)

```bash
#TODO
```

---

## Utilità [↑](#top)

### Possibili problemi

1. problemi di rete a casa
    1. cambiare gli IP
    1. riga di routing dettagliate da Cisco: "192.168.1.1/32 sono io" e "192.168.1.120/32 sono io", e **il router sceglierà le righe più dettagliate**
    1. riga di routing: "192.168.1.0/24 via LAN"
    1. router di casa riesce assegnare DHCP al m0n0wall
    1. riga di routing aggiunta: "192.168.1.0/24 via WAN"
    1. riga di routing aggiunta: "0.0.0.0/0 via 192.168.1.1" riga più generica, considerata per ultima dal router
    1. dal client arriva richiesta di andare verso .1.5, ma non arriva poichè monowall è sulla stessa rete di quella fisica
    1. verso la .1.7 il router Cisco decide in modalità round-robin, quindi è probabile che non arrivi il pacchetto
    1. verso la 1.7 il router Linux dedice in modalità cronologica, mandando sempre in LAN il pacchetto
    1. Anche la metrica viene usata per valutare delle indecisioni di routing (metrica minore viene usata)
    1. m0n0wall e client a casa non funzionano per il problema della rete
        1. CREAZIONE DELLA RETE: scegliere 192.168.x.0 x = con uno pseudorandom (188 = BC <-- oh c'mon)
        1. host www.facebook.com --> IPv6: face:b00c _oh c'mooooooon_

```
(WAN) <---> 1.120 (DMZ router1) <---> |rete diversa| (LAN router2) .2.1 <---> host
```

1. pacchetti da installare (per Debian/Ubuntu e derivate) che potrebbero mancare
    ```bash
    sudo apt search virtualbox-
    #fare apt install di quelli desiderati
    ```

1. riconfigurazione schede di rete
```bash
ifup nomeintefraccia
```
```bash
ifdown nomeinterfaccia
```

### Curiosità varie [↑](#top)

- possibilità di aumentare la banda aumentando il numero di interfacce

- Cellulari, sia Android che iOS, hanno il problema di cercare di velocizzare l'utilizzo dello stesso:
    1. cellulare al posto di inviare lo standard RFC 0.0.0.0
    1. configura i parametri della nuova rete con la vecchia configurazione della rete precedente
    1. appena si attacca, farà traffico con i vecchi IP
    1. INCONVENIENTE: cellulare nella vecchia rete era 192.168.1.5, nella rete in cui si connette cerca 192.168.1.5, DHCP se ne accorge dopo secondi, creando disservizio

- cron (cronos, tempo)
    1. Serve per eseguire dei comandi in orari prefissati
    1. Compito da fare alle 4 con pc spento:
        1. Linux: salta l'esecuzione del compito
        1. Windows: lo esegue appena acceso
    1. cron utilizzato per compiti di manutenzione
        1. compiti orari, giornalieri, settimanali, mensili, senza un'ora precisa

- anacron
    1. collabora con cron e gestisce la periodicità dei compiti da fare
    1. cron daily: cerca di lanciarlo alle 6, se non è accesa, lo avvia alla prima ora disponibile
    1. Se un pc non viene avviato per un po si crea una coda di programmi in cron.

- FHS
    1. [Filesystem Hierarchy _wikipedia_](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard)
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

- Usando il CD a casa richiede se si vuole scaricare dal CD o dalla rete, per rendere indipendente la macchina dall'uso del CD: _source_

- echo $TERM : stampa il nome del terminale
- CTRL+D : uscire dall'utente
- nano .bashrc:
```
case "$TERM" in
       xterm-color|linux|...
alias shutdown=/sbin/shutdown
```

### Funzionamento librerie [↑](#top)

- Eseguibile su winzoz: avanti forever e poi viene installato il programma con le liberie necessarie per ogni programma (Firefox e Thunderbird hanno le stesse librerie, vengono scaricate 2 volte e vengono trattate in modo differente)
- Programma in linux: i gestori delle distribuzioni modificano le librerie per il proprio sistema con risoluzione di problemi di compatibilità, rendendole univoche nel sistema. (per Debian ci sono i tester, obbiettivo: risparmiare trasmissione dati, i pacchettatori prendevano i vari software esistenti per analizzarne le librerie richieste, senza avere il bisogno di riscaricarle anche negli aggiornamenti) (ci possono essere varie versioni nello stesso sistema)
Android: il Play store colleziona software adatto al sistema insieme alle loro liberie
- DEBIAN usa .deb (creato da Ian Mardock, Deb "Deborah" Ian)
- **DPKG** gestore di file
    - vincoli di dipendenze (con limiti sulle versioni)
- **APT** altro gestore
    - utilizza dpkg
    - retrocompatibile con i comandi dpkg
- **deb**: i pacchetti includono sia il programma che i file configurazione standard per l'autoconfigurazione durante l'installazione
- **deborphan**: cerca le librerie orfane, non necessarie a nessun software
deb auto... : rimuove le librerie inutilizzate in automatico

### File utili [↑](#top)

file password:
```bash
cat /etc/shadow
```

file con la configurazione del profilo utente
```bash
sudo nano /etc/profile
# aggiungere :/usr/sbin dopo PATH
```

1. In caso di problemi con monowall, basta riavviarlo
1. Le macchine virtuali possono modificare le schede di rete anche durante le esecuzione delle stesse

---

## Esercizio Cisco [↑](#top)

#### SPERIMENTAZIONE VLAN CON ROUTER CISCO

```
192.168.3.0/24

R1 .101                                              R2 .102
        \                                          /
    1.100 access VLAN 100    .1              .2    VLAN 100
                          SW1 Ge1        Ge1   SW2
    1.200 access VLAN 200        VLAN100           VLAN 200
                                 VLAN200                  
        /                                          \
R3 .201                                              R3 .202
```

---

## TODO [↑](#top)

- [x] clonare client, configurare clone e rinominarlo SERVER
- [x] cron e anacron
- [x] come viene gestito DHCP in LAN e come fare la DMZ
- [x] fare i sistemisti in Antartide nel mese invernale, il client è al caldo, il server e monowall sono nel container al freddo.  
 Rinumerare rete IP di tutto con una procedura gestita solamente dal client.   
 Scaletta delle cose da fare, ssh al server, web al monowall e testare la rete.
- [ ] Fare regole firewall come indicato in **Restrizioni aggiuntive sul firewall**
- [ ] Installare servizi nel server
