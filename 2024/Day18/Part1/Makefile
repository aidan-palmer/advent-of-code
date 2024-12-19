CC = g++
FLAGS = -g -Wall -Wextra

all: Main.cc
	$(CC) $(FLAGS) -o Main Main.cc

clean:
	rm -f Main *.o

run: clean
	make all
	./Main input.txt