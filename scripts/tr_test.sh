#!/bin/bash
# TR test
for i in {1..20}; do
    bin/mysolution.exe --tr -O -f data/matrices/$1
done
