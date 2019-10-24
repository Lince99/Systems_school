#!/bin/bash

#Basso Nicola 5^AI
#24/10/2019
#Esercizio 1

#Script con netcat che visualizza la versione del proxy usato dalla scuola per navigare verso l'esterno
#come www.e-fermi.it, e invia una richiesta HTTP
#Porta del proxy trovata tramite netstat -panetu

PORTA="3128"

echo -en "GET / HTTP/1.1\nUser-Agent:Mozilla/5.0\n\n" | nc www.e-fermi.it $PORTA | grep Server
