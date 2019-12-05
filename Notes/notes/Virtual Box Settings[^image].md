---
title: 'Virtual Box Settings[^image]'
created: '2019-12-05T10:15:24.707Z'
modified: '2019-12-05T10:15:28.758Z'
---

# Virtual Box Settings[^image]
[^image]: [Upload Image](https://it.imgbb.com/)

## Indice
1. [Alias](#alias)
2. [Nat](#nat)
3. [LAN](#lan)
4. [WAN](#wan)
5. [DMZ](#dmz)
6. [Altro](#altro)

## Alias

| Name | Address | Description |
| --- | --- | --- |
| apt-cacher[^apt] | 172.30.1.199 | Server update apt-cacher |
| host-client | 192.168.2.100 | Client in LAN
| host-pcospitante | 172.30.4.2 | Il Computer da cui opero |
| host-router | 172.30.4.110 | Router m0n0wall |
| host-router-dmz |192.168.102.1 | Router m0n0wall DMZ |
| host-router-lan | 192.168.2.1 | Router m0n0wall LAN |
| host-server | 192.168.102.250 | Server in DMZ |
| lan-labsistemi | 172.30.4.0/24 | La Rete in cui appoggia la mia WAN |
[↑](#indice)
[^apt]: apt-cacher.fermi.intra:3142
---
# Firewall
|  | LAN | WAN | DMZ |
| :---: | :---: | :---: | :---: |
| LAN | V | V | V |
| WAN | X | V | V |
| DMZ | X | X | V |

## NAT
Prima regola utilizzata per permettere al PC hospitante di connettersi in SSH
Seconda regola utilizzata per permettere l'SSH dal server al Client via porta 22 o 5022

| If | Proto | Ext. port range | NAT IP | Int. port range | Description |
| --- | --- | --- | --- | --- | --- |
| WAN | TCP | 22 (SSH) | host-server | 22 (SSH) | Server in SSH |
| WAN | TCP | 80 (HTTP) | host-server | 80 (HTTP) | Rendirizzamento al server "apache" |
| DMZ | TCP | 22 (SSH) | host-client | 5022 | Block only port 22 (SSH) on DMZ net |
| DMZ | TCP | 5022 | host-client | 22 (SSH) | DMZ to LAN in SSH via port 22 or 5022 |
| WAN | TCP | 8080 | host-router | 80 (HTTP) | Rendirizzamento al router m0n0wall dalla porta 8080 |
[↑](#indice)

---

# LAN
IP Address: 192.168.`2`.1/24[^lan]
[^lan]: Il `2` si riferisce all'indirizzo del mio PC nel laboratorio

## Firewall Rules
| Proto | Source | Port | Destination | Port | Description |
| --- | --- | --- | --- | --- | --- |
| TCP/UDP | LAN net | * | ! host-router-lan | 53 (DNS) | Block richieste DNS che non sono al router |
| * | LAN net | * | * | * | Default LAN -> any |

## DHCP Server
Range: 192.168.2.100 to 192.168.2.199

[↑](#indice)
# WAN
IP Address: 172.30.4.110

- Username: admin
- Password: lasolita
## Firewall Rules
| Proto | Source | Port | Destination | Port | Description |
| --- | --- | --- | --- | --- | --- |
| TCP | host-pcospitante | * | WAN address | 80 (HTTP) | Allow: accesso web al m0n0wall dal PC ospitante |
| TCP | host-pcospitante | * | host-server | 22(SSH) | NAT Server in SSH |
| ICMP | * | * | WAN address | * | Allow ping to WAN |
[↑](#indice)

# DMZ
IP Address: 192.168.`102`.1/24[^dmz]
[^dmz]: Il`102` si riferisce all'indirizzo del mio PC nel laboratorio sommato a `100`

## Firewall Rules
| Proto | Source | Port | Destination | Port | Description |
| --- | --- | --- | --- | --- | --- |
| TCP | DMZ net | * | host-client | 22(SSH) | Allow DMZ to LAN in SSH (Normally disable) |
| * | DMZ net | * | LAN net | * | Block DMZ to LAN |
| ICMP | DMZ net | * | * | * | Allow ping to any |
| UDP | DMZ net | * | * | 53(DNS) | Allow DNS to any |
| UDP | DMZ net | * | * | 123(NTP | Allow NTP to any |
| TCP | DMZ net | * | apt-cacher | 3142 | Allow only update from server apt-cacher |
| * | DMZ net | * | * | * | Allow: DMZ to any (Normally disable) |

## DHCP Server
Range: 192.168.102.100 to 192.168.102.199

#### Reservations
| MAC address | IP address | Description |
| --- | --- | --- |
| 08:00:27:78:8e:2b | 192.168.102.250 | IP statico del Server |
[↑](#indice)

## Altro
### Installazione comando "host"
		apt-get install dnsutils -y
Questo comando installerà i seguenti pacchetti:

- dig
- nslookup
- host

### Installazione "apache"
Inizialmente bisogna aggiornare l'apt chacher

		sudo apt-get update

Successivamente installiamo il pacchetto apache

		sudo apt-get install apache2

Ora rimane solamente da avviare il servizio

		sudo service apache2 start

Il file index.html sarà generato nella cartella /html
Per operare in quella cartella digitare

		cd /var/www/html

Per personalizzare la propria pagina inizialmente rinominiamo il file index.html in index.html_
Ora creiamo il nuovo file index.html con il seguente comando

		sudo touch index.html

Ora procediamo ad editare il file

		sudo nano index.html

Una volta terminata la modifica procediamo con la verifica
In un browser del client digitiamo il seguente IP

		192.168.102.250

Se la procedura è stata eseguita con successo dovrebbe visualizzarsi il contenuto del file index.html appena creato.

[↑](#indice)
