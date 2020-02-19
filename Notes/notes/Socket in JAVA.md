---
title: Socket in JAVA
created: '2020-01-14T09:37:59.601Z'
modified: '2020-02-19T09:54:46.904Z'
---

# Socket in JAVA

Libro pagine 150-160

http://www.jsums.edu/nmeghanathan/files/2015/05/CSC437-Fall2013-Java-Socket-Programming-Manual.pdf?x61976

## Server Java

Librerie richieste:

```java
import java.io.*;
import java.net.*;
```

Creazione del socket

```java
private ServerSocket serverSocket;

```

Accetta 1 client

```java
Socket server = serverSocket.accept();
```

Separazione del flusso dei dati in entrata e in uscita.
- Tutto deve essere gestito da uno stream
- Dal singolo client servono due oggetti: uno lettura e uno scrittura

```java
public void comunicazione() {
    try {
        ricevuta = inDalClient.readLine();
        outVersoClient.writeBytes(dati);
        socketClient.close();
    } catch(Exception e) {
        e.printStackTrace();
        System.exit(2); 
    }
}
```

Per ricevere la stringa dal client si usa readLine() che rimane in attesa della connessione e dell'invio dei dati dal client.
Per inviare una stringa al client si usa writeBytes()

#### IPv6 

Java può utilizzare l'IPv6, e un socket normale è già in ascolto sia in v4 e v6

```bash
ip addr
```
inet6 ..... scope link --> IPv6 locale
Questo indirizzo viene fornito da avahi o bonjour che è un IPv4 fittizzio nel caso non ci sia un server DHCP

## Catturare CTRL+C

```java
//gestice CTRL+C
Runtime.getRuntime().addShutdownHook(
  new Thread() {
    @Override
    public void run() {
      System.out.println("\nCTRL+C rilevato ...");
    }
  }
);
```

### Obbiettivi

Non usare indirizzo IP ma usare nome host

[ ] fare client
[ ] fare server
[x] connessioni via IPv4, IPv6, nome hosts
[ ] Web server che stampa nell'html (HTTP 1.1) chi è connesso
[ ] Client e Server (multithread) per invio XML in UDP

---

# Client server chat

- scambio di ID
- lista di utenti correnti connessi
    - ttl all'interno del tag id
    ```xml
    <msg id="nome" timeout="60">
        Hello World!
    </msg>

    ```
