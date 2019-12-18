---
title: CGI
created: '2019-12-17T08:45:45.685Z'
modified: '2019-12-18T10:39:09.655Z'
---

# CGI

### Ottenere parametri in GET

```bash
QUERY_STRING='?chiave=valore&chiave2=valore2'
```

Consiglio: usare _strtok()_ per prendere i dati

[tutorial cgi](http://www.yolinux.com/TUTORIALS/BashShellCgi.html)

[](https://www.icosaedro.it/apache/cgi-bash.html)

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
```


