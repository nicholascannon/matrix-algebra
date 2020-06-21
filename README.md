# Matrix Algebra Application

Simple command line application that performs basic matrix algebra operations on sparse matrices. The project reads the sparse matrices in two formats, [coordinate list (COO)](https://en.wikipedia.org/wiki/Sparse_matrix#Coordinate_list_(COO)) & [compressed sparse row (CSR)](https://en.wikipedia.org/wiki/Sparse_matrix#Compressed_sparse_row_(CSR,_CRS_or_Yale_format)), depending on the operation being performed. Efficient multi-threading achieved with the [OpenMP](https://www.openmp.org/) library.

**Written by Nicholas Cannon**

## Command line args (project assumes arguments are correct)

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

## Running the application

Simple example of running the appliaction with the make file:

    make run ARGS="--sm 4 -t 4 -l -f data/matrices/int1.in"

The above example multiplies the matrix stored in `data/matrices/int1.in` by the scalar 4, uses 4 threads and logs the output to file.

## Make commands

- `make` -> compiles and builds executable into bin folder
- `make run` -> runs executable in bin folder
- `make clean` -> cleans project (removes object files)

## Folders

- `bin/` -> contains compiled executable.
- `data/` -> Sample matrix data and sample output logs.
- `docs/` -> **Contains report and excel document used to generate graphs.**
- `include/` -> Application header files.
- `obj/` -> compiled object files (run make clean to remove).
- `scripts/` -> Simple bash scripts to test application performance.
- `src/` -> Source code for the application.
