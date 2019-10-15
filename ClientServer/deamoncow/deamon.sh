#!/bin/bash

PORTA=9970
ESEGUIBILE="cowsay -f meow"

while true
do
	echo Esecuzione catto $ESEGUIBILE nella porta $PORTA
	nc.traditional -l -p $PORTA -c "$ESEGUIBILE"
done
