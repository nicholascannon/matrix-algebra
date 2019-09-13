# CITS3402 Project 1: Matrix Multiplication

Written by Nicholas Cannon (22241579)

## Make commands

- `make` -> compiles and builds executable
- `make run` -> runs executable in ./bin
- `make clean` -> cleans project (removes object files)

## Command line args

- `--sm -f mat1.in` -> scalar multiplication
- `--tr -f mat1.in` -> trace
- `--ad -f mat1.in mat2.in` -> matrix addition
- `--ts -f mat1.in` -> matrix transposition
- `--mm -f mat1.in mat2.in` -> matrix multiplication
- `-t %d` -> number of threads to use
- `-l` -> log to file

## NOTE

May need to change the `CC` value in makefile. I'm running on osx and had to use gcc-9 as gcc is just a symlink to clang on osx =(
