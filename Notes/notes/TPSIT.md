---
tags: [Networking, Routing]
title: TPSIT
created: '2019-09-24T08:59:47.457Z'
modified: '2019-10-01T10:13:39.811Z'
---

# TPSIT

24/09/19

## SOCKET e Client-Server

Programmazione a basso livello
nc: netcat

Dati richiesti dal client-server:
- IP
- PORT
- TCP / UDP

DOMINIO e IP non è una corrispondenza biunivoca.
Più domini sullo stesso IP con Virtual Host (Apache).

Per bloccare un sito non bisogna bloccare l'IP (perchè ci sono altri domini sullo stesso), ma basta bloccare il DOMINIO.

HTTPS non leggibile, bloccabile solo nella richiesta del client al DNS per risolvere il nome del sito con l'IP.

DNS primario e secondario: IP e porta 53 UDP, il secondario viene provato a richiesta scaduta del primo.

CLIENT --> richiesta DNS --> DNS --> indirizzo IP --> CLIENT

DHCP:
- IP privato (con associazione MAC)
- Subnet mask
- Gateway

DNS interno:
- Lista di associazione Dominio con IP

Firewall:
- Intercetta le porte
- Blocca richiesta DNS esterna (porta 53) che non sia fatta dal DNS interno.

Router:
- Traffico entrante:
  - Fa da firewall perchè il NAT blocca gli IP che non sono delle richieste dal locale.
- Traffico uscente:
  - Non fa da firewall perchè il NAT ha ricevuto la richiesta dal client in LAN.
- NAT: Network Address Translation
- PAT: Port Address Translation (integrato nel NAT)


### Tabella di NAT

```
|---------------------------------|
| IP esterno | Porta | IP interno |
| IP1        | 7000  |         .7 | <-- richiesta
| IP2        | 5435  |         .8 |
| IP3        | 3144  |       .100 |
| IP1        | 7000  |         .7 | <-- risposta
| IP5        | 2000  |         .3 | <-- port forwarding
|---------------------------------|
```

Client --> Router --> WAN --> Server
      IP Dynamic Port     IP Port

Client <-- Router <-- WAN <-- Server
   IP Dynamic Port     IP Dynamic Port

Porta generata dai client in locale per fare la richiesta verso l'esterno per accordarsi con i server

### Port forwarding

Modifica la tabella NAT del router
