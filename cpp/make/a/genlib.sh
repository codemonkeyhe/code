#!/bin/sh
g++ src/a.cpp -I./h/  -c -o a.o
ar crs liba.a a.o
mv liba.a ./lib/

