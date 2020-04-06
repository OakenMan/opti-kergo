CC=g++
CFLAGS=-Wall -O -Wno-deprecated
LDFLAGS=
EXEC=exec

all: $(EXEC)

exec: main.o Instance.o Solution.o
	$(CC) -o $@ $^ $(LDFLAGS)

Instance.o: Instance.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Solution.o : Solution.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.cpp Instance.hpp Solution.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)

valgrind:
	gcc -g -o main main.cpp
	valgrind ./main -f -leak-check=full
