#!/bin/bash
# times COO loading 20 times
for i in {1..20}; do
    bin/mysolution.exe --sm 4 -L -f data/matrices/$1
done
