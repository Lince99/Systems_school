---
title: PROCESSI IN C
created: '2019-11-20T09:54:52.709Z'
modified: '2019-11-20T10:44:11.595Z'
---

# PROCESSI IN C

## Comandi utili

```bash
man ps #per vedere le info del comando
```

```bash
ps -aux | less
```

```bash
ps -def | grep nomeuser #mostra processi e relativi pid e ppid dell'utente passato al grep
```

PID: id del processo
PPID: id del padre

```bash
pstree -p | less
```

```bash
top #Z per dare colori
```

Questi programmi attingono i dati dalla cartella _/proc_ che contiene dei file virtuali (gestiti dal kernel linux)

```bash
cat /proc/cpuinfo #mostra le informazioni del processore 
```

Sono presenti molte cartelle numerate = **PROCESSI**

```bash
cd /proc/80
cat sched #mostra le informazioni dello schedulatore sul processo
```

#### GREP

Grep filtra i risultati sia con parole singole che con espressioni regolari
- .* ci sono da 1 a n caratteri
- ^ inizia per caratteri dopo
- $ finisce per caratteri prima

---

## Programma di esempio stampe

### Consegna:

Fare un programma che generi 10 processi e il padre aspetti che tutti e 10 i figli terminino.  
Ogni processo sarà numerato e attende 50ms per stampare delle informazioni, e altri 500ms termina con il codice terminazione 100+numero_figlio.

### Flusso del programma

1. Al posto di 10 processi è possibile variarne il numero tramite primo parametro

### Esecuzione

## Programma di esempio lavorazione su file

### Consegna:

Si vuole realizzare un programma in linguaggio C in grado di:
Generare due processi padre/figlio in cui:
- Il processo padre scrive la sequenza di caratteri [A-Z][a-z] in un file di testo (aperto prima di eseguire la fork) e successivamente chiude e rimuove il file creato
- Il processo figlio attende 5 secondi e stampa il contenuto del file precedentemente gestito dal processo padre

### Flusso del programma

### Esecuzione

---

## TODO

[ ] Fare i due esercizi
[ ] Scrivere degli esempi automatici
[ ] Mettere un'indice su questo readme

