#!/bin/bash
#Per uccidere il processo usare kill -9 PID

PORTA=9900
ESEGUIBILE="./readvbx"

while true
do
	echo Esecuzione read vbox $ESEGUIBILE nella porta $PORTA
	nc.traditional -l -p $PORTA -c "$ESEGUIBILE"
done
