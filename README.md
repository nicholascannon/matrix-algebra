# CITS3402 Project 1: Matrix Multiplication

Written by Nicholas Cannon (22241579)

## Folders

- `bin/` -> contains compiled executable.
- `data/` -> Sample matrix data and sample output logs.
- `docs/` -> Contains report and excel document used to generate graphs.
- `include/` -> Application header files.
- `obj/` -> compiled object files (run make clean to remove).
- `scripts/` -> Simple bash scripts to test application performance.
- `src/` -> Source code for the application.

## Make commands

- `make` -> compiles and builds executable into bin folder
- `make run` -> runs executable in bin folder
- `make clean` -> cleans project (removes object files)

## Running the application

Simple example of running the appliaction with the make file:

    make run ARGS="--sm 4 -t 4 -l -f data/matrices/int1.in"

## Command line args

- `--sm -f mat1.in` -> scalar multiplication
- `--tr -f mat1.in` -> trace
- `--ad -f mat1.in mat2.in` -> matrix addition
- `--ts -f mat1.in` -> matrix transposition
- `--mm -f mat1.in mat2.in` -> matrix multiplication
- `-t %d` -> number of threads to use
- `-l` -> Writes to logfile. Logfiles can be found in `data/logs/`
- `-O` -> print operation time to stdout
- `-L` -> print load time to stdout
- `ti` -> time CSR loading with given matrix

## NOTE

May need to change the `CC` value in makefile. I'm running on osx and had to use gcc-9 as gcc is just a symlink to clang on osx =(
