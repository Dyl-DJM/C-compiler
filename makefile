# Makefile TP Flex/Bison

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-Wall
EXEC=src/tpcc

all: $(EXEC)
	cp $(EXEC) bin
	cp lex.yy.* obj
	cp tpcc.tab.* obj
	make clean


$(EXEC): lex.yy.o tpcc.tab.o tree.o obj/anonymous

	$(CC) -o $@ $^ $(LDFLAGS)


obj/anonymous : src/make_anonymous.c
	$(CC) -c src/make_anonymous.c -o obj/anonymous $(CFLAGS)


lex.yy.c: $(EXEC).l
	flex $(EXEC).l


tree.o : src/tree.c
	$(CC) -o tree.o -c src/tree.c $(CFLAGS)

%.o: %.c
	make tpcc.tab.c
	$(CC) -o $@ -c $< $(CFLAGS)

tpcc.tab.c: $(EXEC).y
	bison -d $(EXEC).y
	



clean_directories:
	make clean
	rm -f *.o obj/lex.yy.c obj/lex.yy.o obj/tpcc.tab.* bin/tpcc $(EXEC)

clean:
	rm -f *.o lex.yy.c tpcc.tab.* $(EXEC)
	rm -f a.out _anonymous.asm


exec:
	nasm -f elf64 -o anonymous.o _anonymous.asm
	nasm -f elf64 -o utils.o utils.asm
	gcc -o a.out anonymous.o -nostartfiles -no-pie

