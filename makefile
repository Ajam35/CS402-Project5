.SUFFIXES: .c .o
CC = gcc
CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

p5a: p5amain.o BSTfuncs.o 
	gcc p5amain.o BSTfuncs.o  -o p5a

p5amain.o: p5amain.c BSTfuncs.c struct5a.h

p5b: p5bmain.o funcs5b.o
	gcc p5bmain.o funcs5b.o  -o p5b

p5bmain.o: p5bmain.c funcs5b.o struct5b.h
funcs5b.o: funcs5b.c externs5b.h


clean:
	rm -f core p5a *.o
