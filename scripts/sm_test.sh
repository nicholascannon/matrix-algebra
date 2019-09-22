#!/bin/bash
# SM test
for i in {1..20}; do
    bin/mysolution.exe --sm 4 -O -f data/matrices/$1
done
