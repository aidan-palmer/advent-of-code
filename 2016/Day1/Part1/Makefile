CC = g++
FLAGS = -g -Wall -Wextra -Wunused-variable -Wuninitialized

all: Main.cc
	$(CC) $(FLAGS) -o Main Main.cc

clean:
	rm -f Main *.o

run: clean all
	./Main input.txt

test: clean all
	./Main example.txt

dbg:
	gdb -q --args ./Main example.txt