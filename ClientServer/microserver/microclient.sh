#!/bin/bash

echo -en "GET / HTTP/1.1\nUser-Agent: Mozilla/5.0\n\n" | nc localhost 2080
