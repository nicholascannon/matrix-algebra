#!/bin/bash
# AD test
for i in {1..20}; do
    bin/mysolution.exe --ad -O -f data/matrices/$1 data/matrices/$1
done
