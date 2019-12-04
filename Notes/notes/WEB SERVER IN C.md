---
title: WEB SERVER IN C
created: '2019-11-20T09:51:19.284Z'
modified: '2019-12-04T10:39:44.230Z'
---

# WEB SERVER IN C

## Obbiettivo

Riuscire a creare un server che fornisca a più client una pagina web html o php e che riceva dati json o altri formati

### Conoscenze sui seguenti costrutti richieste

- standard I/O
- fork
- thread
- socket
- signal

## Compilazione

Per la official release usare
```bash
grep -v 
```

```bash
make
```

### Esempi reali

Apache se non trova il file richiesto dal client, andrà a creare una pagina autogenerata che mostra i file nella cartella corrente.

> Security by Information Hiding
> Nascondere i file dagli attacchi 

URL = parte host e struttura del file
URI = 

### Controlli

Per controllare i socket attivi del server
```bash
watch -c -t netstat -panetu
#oppure
watch "netstat -panetu | grep Nomeprogramma"
```

Per controllare i processi figli del server
```bash
watch -n 1 "ps -def | grep Nomeprogramma"
```

Per inseguire la stampa usare
```bash
tail -f nomefile #anche se ci sono processi che stampano
#usare il redirect delle stampe del server in un file di log
./server -p 1234 -T -v 1 > server.log
```

Per testare come client
```bash
telnet 172.30.4.11 8000
```

### DEBUG

Livello di debug:
- 5 = <span style="color:yellow; background-color: purple">**! CRITICAL !**</span>
- 4 = <span style="color:red; background-color: black">ERROR</span>
- 3 = <span style="color:orange; background-color: black">WARNING</span>
- 2 = <span style="color:green; background-color: black">NOTICE</span>
- 1 = <span style="color:white; background-color: black">INFO</span>

Livello di verbosità del programma:
1. Nothing (0)
1. **Default** (5, 4)
1. Verbose (5, 4, 3, 2)
1. All (5, 4, 3, 2, 1)

E' possibile che il livello venga modificato dal programma stesso in fase di sviluppo (branch dev).

---

## Licenza

MIT because yez
