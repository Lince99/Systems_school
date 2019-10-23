#!/bin/bash

nc -l 2080 < paginastriminzita.htmlhttp > serverout.txt && cat serverout.txt && rm serverout.txt
