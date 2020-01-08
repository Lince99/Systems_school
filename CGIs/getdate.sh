#!/bin/bash

echo 'Content-type: text/html'
echo ''
echo '<!DOCTYPE html>'
echo ''
echo ''
echo '<html><title>Data</title>'
echo '<body>'
echo '<h1>Today is: '
date
echo '</h1>'
echo '<h3>Variabili d''ambiente:</h3>'
env
echo '</body>'
echo '</html>'
