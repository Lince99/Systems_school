---
title: Socket in JAVA
created: '2020-01-14T09:37:59.601Z'
modified: '2020-01-22T10:29:33.079Z'
---

# Socket in JAVA

Libro pagine 

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

### Obbiettivi

Non usare indirizzo IP ma usare nome host

[ ] fare client
[ ] fare server
[ ] connessioni via IPv4, IPv6, nome hosts
[ ] Web server che stampa nell'html (HTTP 1.1) chi è connesso
