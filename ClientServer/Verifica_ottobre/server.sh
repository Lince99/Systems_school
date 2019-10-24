#!/bin/bash

#Basso Nicola 5^AI
#24/10/2019
#Esercizio 2

#Server ascolta in porta 8980 per n client
#Riceve richesta dal client contenente una stringa
#Server esegue programma in C che stampa "Stringa ricevuta" e legge da stdin la stringa del client
#Server invia al client su stdout "RICEVUTO: messaggiodelclient"
#Client stampa il messaggio ricevuto dal server

PORTA="8980"
PROGRAMMA="./getstr"

while true
do
	echo -en "\tEsecuzione del server con PID $$\n"
	nc.traditional -l -p $PORTA -c $PROGRAMMA
done
