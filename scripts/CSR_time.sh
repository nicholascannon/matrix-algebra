#!/bin/bash
# times CSR loading 20 times
for i in {1..20}; do
    bin/mysolution.exe --ti -L -f data/matrices/$1
done
