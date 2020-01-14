---
title: Socket in JAVA
created: '2020-01-14T09:37:59.601Z'
modified: '2020-01-14T10:10:03.316Z'
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

### Obbiettivi

Non usare indirizzo IP ma usare nome host

[ ] fare client
[ ] fare server
[ ] connessioni via IPv4, IPv6, nome hosts
