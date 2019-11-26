---
title: WEB SERVER IN C
created: '2019-11-20T09:51:19.284Z'
modified: '2019-11-26T09:52:44.271Z'
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

Per controllare i socket attivi del server
```bash
watch -c -t netstat -panetu
```

Per inseguire la stampa usare
```bash
tail -f nomefile #anche se ci sono processi che stampano
#usare il redirect delle stampe del server in un file di log
./server -p 1234 -T -v 1 > server.log
```

Livello di debug:
- 5 = CRITICAL
- 4 = ERROR
- 3 = WARNING
- 2 = NOTICE
- 1 = INFO

Livello di verbosità del programma:
1. Nothing (0)
1. **Default** (5, 4)
1. Verbose (5, 4, 3, 2)
1. All (5, 4, 3, 2, 1)

E' possibile che il livello venga modificato dal programma stesso in fase di sviluppo (branch dev).

---

## Licenza

MIT because yez
