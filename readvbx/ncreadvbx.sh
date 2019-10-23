#!/bin/bash

#SERVER in ascolto per vbox
nc.traditional -l -p9800 -c ./readvbx

#CLIENT
nc localhost 9800 < clientbasso.vbox
