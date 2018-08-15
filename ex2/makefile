CC= gcc
CFLAGS= -c -Wvla -Wall
CODEFILES= ex2.tar battleships.h battleships.c  battleships_game.c makefile


# All Target
all: ex2


# Object Files

battleships.o: battleships.c battleships.h
	$(CC) $(CFLAGS) battleships.c battleships.h

battleships_game.o: battleships_game.c battleships.h
	$(CC) $(CFLAGS) battleships_game.c battleships.h

battleships: battleships.o
	$(CC) $(CFLAGS) battleships.c battleships.h


# Exceutables
ex2: battleships.o battleships_game.o
	$(CC) battleships.o battleships_game.o -o ex2.exe



# tar
tar:
	tar -cf $(CODEFILES)


# Other Targets
clean:
	-rm -f *.o battleships_game battleships ex2.exe

# Things that aren't really build targets
.PHONY: clean
