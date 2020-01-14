---
deleted: true
title: CGI
created: '2019-12-17T08:45:45.685Z'
modified: '2020-01-14T09:29:42.894Z'
---

# CGI

### Ottenere parametri in GET

```bash
QUERY_STRING='?chiave=valore&chiave2=valore2'
```

Consiglio: usare _strtok()_ per prendere i dati

[tutorial cgi](http://www.yolinux.com/TUTORIALS/BashShellCgi.html)

[tutorial bash cgi](https://www.icosaedro.it/apache/cgi-bash.html)

### Abilitare CGI

```bash
sudo a2enmod cgi
```

### Configuro Apache 2 per CGI

```bash
cd /etc/apache2/sites-available
sudo nano 000-default.conf
# decommentare l'Include di cgi-bin
sudo service apache2 restart
```

### Mettere lo script CGI in /usr/lib/cgi-bin

```bash
cd
mkdir web_dev
cd web_dev
nano getdata.sh #aggiungere stampa html e altri script bash (echo a gogo)
sudo ln -s /home/uds/web_dev/getdata.cgi /usr/lib/cgi-bin/getdata.cgi
sudo chmod +x /usr/lib/cgi-bin/getdata.cgi
sudo chown uds:uds /usr/lib/cgi-bin/getdata.cgi
```

In caso di errore 500

https://unix.stackexchange.com/questions/123866/500internal-server-error-from-cgi-program

## CGI per prendere variabili GET

```bash
nano getenv.sh
```

[esempio codice c99 cgi](https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c#2085385)

```c
#include <stdio.h>

int main(int argc, char **argv, char** env) {
    while (*env)
        printf("%s\n", *env++);
    return 0;
}
```

```bash
sftp uds@192.168.111.250
cd /usr/lib/cgi-bin
lpwd #mostra dove sei nel client
pwd #mostra dove sei nel server
put getvar #eseguibile
```

## TODO

[ ] Leggere sia GET che POST da un form HTML in cgi scritto in C con apposite librerie


