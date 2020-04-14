CC=g++
CFLAGS=-Wall -O -Wno-deprecated -g
LDFLAGS=
EXEC=exec

all: $(EXEC)

test: test.o Instance.o Solution.o vector_methods.o
	$(CC) -o $@ $^ $(LDFLAGS)

exec: main.o Instance.o Solution.o generation.o selection.o reproduction.o mutation.o vector_methods.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.cpp Instance.cpp Solution.cpp generation.cpp selection.cpp reproduction.cpp mutation.cpp vector_methods.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Instance.o: Instance.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Solution.o: Solution.cpp vector_methods.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

vector_methods.o: vector_methods.cpp Solution.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

selection.o: selection.cpp Solution.cpp Instance.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

reproduction.o: reproduction.cpp Solution.cpp Instance.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

mutation.o: mutation.cpp Solution.cpp Instance.cpp vector_methods.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

generation.o: generation.cpp Solution.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

test.o: test.cpp Instance.cpp Solution.cpp vector_methods.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)

# j'ai rajouté un argumenter au valgrind histoire de pouvoir faire make valgrind ARG="..."
valgrind: $(ARG)
	valgrind ./$(ARG) -f -tool=memcheck -leak-check=full track-origin=yes
