#!/bin/bash

gcc -o level.o -c level.c -O2
gcc -o sfun.o -c sfun.c -O2
gcc -o main.o -c main.c -O2
gcc -o snake main.o sfun.o level.o -O2

