CFLAGS := -Wall -g -O0  
SRC=buf.c heap.c huge.c mmap.c null.c stack.c

DEPENDHELPERS=helpers.o

BINARIES=$(SRC:%.c=%)

%.o : %c
	gcc -c $+

$(BINARIES): % : %.o $(DEPENDHELPERS)
	gcc  -o $@ $+

all : $(BINARIES)

clean:
	rm -f *.o $(BINARIES)
