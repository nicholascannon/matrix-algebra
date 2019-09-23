#!/bin/bash
# MM test
for i in {1..20}; do
    bin/mysolution.exe --mm -O -f data/matrices/$1 data/matrices/$1
done
