IDIR =/
CC= g++-7
CFLAGS=-I$(IDIR) -g3 -ggdb

ODIR=./

_DEPS = compiler.h inputbuf.h lexer.h grammar.h parser.h program.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = compiler.o inputbuf.o lexer.o parser.o program.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cc $(DEPS)
	$(CC)  -c -o $@ $<  $(CFLAGS)
a.out: $(OBJ)
	$(CC) -o  $@ $^  $(CFLAGS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
