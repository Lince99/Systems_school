---
title: SOCKETS
created: '2019-11-05T08:29:31.370Z'
modified: '2019-11-20T09:50:23.253Z'
---

# SOCKETS

## Socket

### Strutture

**INADDR_ANY** numero che corrisponde all'IP 0.0.0.0, possiede più significati: 
- indirizzo socket = qualsiasi IP
- router = nessun DNS, dato non inserito

Tutti = 255.255.255.255, a volte 0.0.0.0, nella transizione IPv6 il problema si risolverà.


### TCP



```bash
nc localhost porta
```


### UDP

Esempi: DNS Domain Name System, NTP Network Time Protocol, TFTP, ...  
Risposta entro la trama usualmente, domanda 77 byte per dns, risposta 150 byte.

```bash
nc localhost porta -U
```

Fare client/server NTP, TFTP

---

## Signal

Per catturare un segnale basta usare la funzione asincrona signal.h

```C
#include <signal.h>

```


