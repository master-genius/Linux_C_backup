#!/bin/bash

gcc -o level.o -c level.c
gcc -o sfun.o -c sfun.c
gcc -o main.o -c main.c
gcc -o snake main.o sfun.o level.o -O2

