CC=g++
CFLAGS=-Wall -O -Wno-deprecated -g
LDFLAGS=
EXEC=exec

all: $(EXEC)

exec: main.o Instance.o Solution.o vector_methods.o
	$(CC) -o $@ $^ $(LDFLAGS)

Instance.o: Instance.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Solution.o : Solution.cpp vector_methods.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

vector_methods.o : vector_methods.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.cpp Instance.cpp Solution.cpp vector_methods.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)

# j'ai rajouté un argumenter au valgrind histoire de pouvoir faire make valgrind ARG="..."
valgrind: $(ARG)
	valgrind ./$(ARG) -f -tool=memcheck -leak-check=full track-origin=yes

repro: reproduction.cpp Solution.cpp Instance.cpp vector_methods.cpp
	$(CC) -o $@ $^ $(CFLAGS)

muta: mutation.cpp Solution.cpp Instance.cpp vector_methods.cpp
	$(CC) -o $@ $^ $(CFLAGS)
