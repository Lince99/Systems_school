---
title: Docker
created: '2020-02-22T07:46:55.811Z'
modified: '2020-02-22T08:31:49.336Z'
---

# Docker

Servizio che permette di creare dei contenitori in cui si possono installare software a piacimento

Tutti i servizi rimangono solamente all'interno del contenitore, non sono disponibili sulla macchina utilizzata

```bash
sudo apt update
sudo apt upgrade
sudo apt install docker.io
```


## Docker preconfigurati

docker hub
- Server apache, cacti, minecraft, qualsiasi servizio


## Configurazione

Scarica un docker
```bash
docker pull debian:latest
```

```bash
docker images
docker container ls --all
```
mostra le immagini installate


### Rete

I container servono per far andare più istanze della stessa applicazione, però per la comunicazione bisogna specificare la porta diversa. (sovrapposizione diretta, senza bridge)

Docker crea un'interfaccia di rete 172.17.0.1 che si collega a tutti i container

```bash
ip route
```

Utilizza la macchina docker come default gateway


## Avvio

```bash
docker run -it --name debian debian:latest
```

Entra nel docker (sottomacchina) e ottiene le risorse dalla macchina ospite, con la possibilità di limitarne la quantità.

Per avviare un servizio sotto una porta diversa usare il comando che esegue un DNAT:

```bash
docker run -dit --name nomedocker -p 8080:80 servizio
iptables-save #mostra le regole generate da docker
```

Rispetto alla virtualizzazione classica, i docker non hanno tutto il peso dell'emulazione dell'hardware, infatti vede direttamente le risorse della macchina ospitante

```bash
cat /proc/info
```


### Servizi

Di default non sono preinsallati servizi, infatti nel docker debian il comando non restituisce nulla

```bash
ss -panetu
```

```bash
apt install elinks joe mtr-tiny
elinks http://registro.e-fermi.it #rete->IP e crea un NAT
mtr registro.e-fermi.it #mostra il primo salto come locale
```


### Utilizzi

- Isolamento del contesto per motivi di sicurezza
- Possibilità di provare servizi senza compromettere la macchina ospite

```bash
docker attach #rientro nel docker direttamente
#oppure con ssh
```

#### Test vari


```bash
echo "miofile" > pippo.txt
cat pippo.txt
apt install ssh
scp pippo.txt ip-ospite:
```


### Spegnimento

Applicare le modifiche al docker, creandone una copia di backup (snapshot)

```bash
docker commit debian debian:v1
docker images
```

```bash
docker run -it --name debian1 debian:v1
```

Terminazione del docker

```bash
docker container ls --all
#eliminare le modifiche fatte
docker rm debian:v1
```

### Eliminazione

```bash
docker system prune
docker system prune -a #anche le immagini
```


## Risorse utili

https://github.com/DockStation/dockstation

## Esempio

```bash
sudo apt install docker.io
docker pull debian:latest
docker run -it --name debian debian:latest
apt update
apt install nano apache2 net-tools
nano /var/www/html/index.html
exit
docker commit debian debian:apache_ready
docker images
docker run -it debian:apache_ready
docker pull httpd
docker start httpd
```

### Tomcat e apache in docker

```bash
docker pull debian:latest
docker run -it --name webserver_apache debian
```

All'interno del docker:

```bash
apt update
apt install net-tools nano apache2 php -y
exit
```

Si salvano i cambiamenti in una nuova immagine per fare un nuovo container

```bash
docker ps -a
docker container ls --all
docker commit webserver_apache webserver:apache_ready
docker images
```

Installazione di tomcat

```bash
docker run -it --name apache_tomcat webserver:apache_ready
apt install tomcat9 default-jdk ant git -y
apt install tomcat9-examples tomcat9-admin tomcat9-docs -y
exit
docker commit apache_tomcat webserver:apache_tomcat
```

Esecuzione del server tomcat in una porta personalizzata

https://hub.docker.com/_/tomcat/

```bash
# docker stop test_tomcat #in caso di problemi
docker run -it --rm --name test_tomcat -p 8888:8080 webserver:apache_tomcat #todo test better
```
