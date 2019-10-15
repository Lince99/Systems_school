---
tags: [nc, TPSIT]
title: NETCAT
created: '2019-10-08T10:32:06.437Z'
modified: '2019-10-15T09:23:00.356Z'
---

# NETCAT

## server con nc.traditional

Nell'instaurare la connessione è certo, ma nella chiusura dipende dal programma, se termina il programma termina anche nc.
Il client nota la chiusura del canale.
Invece, se il client stabilisce la connessione, ma non invia dati e poi muore, allora nc rimane un processo pendente con il processo di nc zombie.
Se muore elegantemente, allora nc termina normalmente uccidendo il proprio processo.

# terminazioni

```bash
cowsay
```

**CTRL + C** termina cowsay

**CTRL + D** invia EOF, terminando il flusso di dati in stdin di cowsay

```bash
nc.traditional -l -p9800 -c cowsay
```

su un altro terminale:
```bash
nc localhost 9800
```
su questo si potrà scrivere i dati da inviare al server

sul terzo terminale:
```bash
netstat -panetu
```
output:
```
Proto CodaRic CodaInv Indirizzo locale        Indirizzo remoto       Stato       User       Inode       PID/Program name
tcp        0      0 127.0.0.1:9800          127.0.0.1:49464         ESTABLISHED 1941689748 33082        3144/sh

tcp        0      0 127.0.0.1:49464         127.0.0.1:9800          ESTABLISHED 1941689748 33208       3178/nc
```

- 0.0.0.0:22 server ssh
- 0.0.0.0:80 server http


Dopo aver fatto CTRL+D sul client, riceve la risposta dal server.
Poi il client termina l'esecuzione di nc appena riceve la stampa di cowsay e nc.traditional sul server termina, terminando cowsay.
In questo caso è il server a terminare la connessione.

### Accettazione più chiamate consecutive e contemporanee

- Creazione variabili di sistema

```bash
#!/bin/bash
#interpreta i successivi comandi con l'interprete corrent (chiamato SHABANG per bash), SOLO LA PRIMA RIGA con #! allora usa quell'interpete
PORTA=9970
ESEGUIBILE="./eseguibile"
```

- Creazione demone netcat che esegue richieste consecutive

```bash
while true
do
    echo eseguo $ESEGUIBILE in ascolto sulla porta $PORTA
    nc.traditional -l -p $PORTA -c "$ESEGUIBILE"
done
```

poi renderlo eseguibile con
```bash
chmod +x nomefile.sh
```

esempio: (ATTENZIONE VA ALL'INFINITO!)
```bash
while true; do echo "invocazione"; nc.traditional -l -p 9970 -c "cowthink -f vader" ; done
```

```bash
nc 172.30.4.129 9970
```

richiede CTRL + Z o CTRL + C per terminarlo

---

## Variabili d'ambiente

Serve per appendere altro testo

```bash
${nomevariabile}testoattaccato
```

## Piping

```bash
date | cowsay
```

stdout di _date_ --> stdin di _cowsay_ --> stdout

In netcat traditional serve -c, che va a prendere l'stdout oltre a dare l'stdin al programma.

cat --> stdin --> **nc client** - - net - -> **nc server** --> stdin --> programma --> stdout --> **nc server** - - net - -> **nc client** --> stdout 
