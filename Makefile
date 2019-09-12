# See link below for template of this makefile
# https://stackoverflow.com/questions/53136024/makefile-to-compile-all-c-files-without-needing-to-specify-them/53138757
IDIR=./include
ODIR=./obj
LDIR=./lib
SDIR=./src
BDIR=./bin

CC=gcc-9 # NOTE this may need to be changed depending on the system!
CFLAGS=-Wall -Werror -pedantic -I$(IDIR)

LIBS=-fopenmp
SRCS=$(wildcard $(SDIR)/*.c)
OBJS=$(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRCS))
EXE=$(BDIR)/mysolution

.PHONY: run all clean

all: $(EXE)

$(EXE): $(OBJS) | $(BDIR)
	$(CC) $(LIBS) $^ -o $@  

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BDIR) $(ODIR):
	md $@

run: $(EXE)
	$<

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
