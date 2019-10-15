#!/bin/bash
#Per uccidere il processo usare kill -9 PID

PORTA=9970
IP=localhost
FILE="clientbasso.vbox"

echo Esecuzione client, attesa ricezione dati da server $IP $PORTA con file $FILE
nc $IP $PORTA < $FILE
#cat $FILE | nc $IP $PORTA
