#!/bin/bash

#Basso Nicola 5^AI
#24/10/2019
#Esercizio 2

#Client invia stringa al server
#Client stampa stringa di risposta dal server

IP="localhost"
PORTA="8980"

echo -en "Inserisci la stringa da mandare al server $IP:$PORTA\n"
nc $IP $PORTA
