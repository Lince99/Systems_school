---
tags: [Networking]
title: Configurazione_dispositivi
created: '2019-09-24T10:11:06.431Z'
modified: '2019-09-24T10:26:38.838Z'
---

# Configurazione Dispositivi

24/09/19

## Creazione VPN

### Dominio
casa.iz3twl.it

Winzoz: 
Pannello di controllo --> VPN
- Provider
- Nome
- Indirizzo (dominio o IP)
- Tipologia (PPTP bacato, IPSec ancora sicuro)
- Chiave condivisa se presente (password)
- Informazioni d'accesso
- Nome utente da collegare
- Password utente da collegare

Modificare il registro:
HKEY_LOCAL_MACHINE --> SYSTEM --> CurrentControlSet --> Services --> PolicyAgent --> DWORD 32bit --> AssumeUDPEncapsulationContextOnSendRule --> 2

*(per protocollo IPsec modificato versione Ubiquity btw -.-)*

__VPN VA SU KERNEL__
- crea una scheda di rete virtuale con il suo indirizzo IP
- autoswitching tra rete VPN e rete normale
