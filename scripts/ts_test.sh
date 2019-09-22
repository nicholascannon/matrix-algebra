#!/bin/bash
# TS test
for i in {1..20}; do
    bin/mysolution.exe --ts -O -f data/matrices/$1
done
