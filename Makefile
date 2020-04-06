CC=g++
CFLAGS=-Wall -O
LDFLAGS=
EXEC=exec

all: $(EXEC)

exec: main.o
	$(CC) -o $@ $^ $(LDFLAGS)

Instance.o: Instance.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Solution.o : Solution.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c 
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)
