CC=g++
CFLAGS=-Wall -O -Wno-deprecated -g
LDFLAGS=
EXEC=exec

all: $(EXEC)

find_parameters: find_parameters.o Instance.o Solution.o generation.o selection.o reproduction.o mutation.o vector_methods.o stats.o settings.o
	$(CC) -o $@ $^ $(LDFLAGS)

exec: main.o Instance.o Solution.o generation.o selection.o reproduction.o mutation.o vector_methods.o stats.o settings.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.cpp Instance.cpp Solution.cpp generation.cpp selection.cpp reproduction.cpp mutation.cpp vector_methods.cpp stats.cpp settings.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Instance.o: Instance.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Solution.o: Solution.cpp vector_methods.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

vector_methods.o: vector_methods.cpp Solution.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

selection.o: selection.cpp Solution.cpp Instance.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

reproduction.o: reproduction.cpp Solution.cpp Instance.cpp settings.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

mutation.o: mutation.cpp Solution.cpp Instance.cpp vector_methods.cpp settings.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

generation.o: generation.cpp Solution.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

find_parameters.o: find_parameters.cpp Instance.cpp Solution.cpp generation.cpp selection.cpp reproduction.cpp mutation.cpp vector_methods.cpp stats.cpp settings.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

stats.o: stats.cpp Solution.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

settings.o: settings.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)

# make valgrind ARG="./exec"
valgrind: $(ARG)
	valgrind ./$(ARG) -f -tool=memcheck -leak-check=full track-origin=yes
