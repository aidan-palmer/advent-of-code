CC = g++
FLAGS = -g -Wall -Wextra -Wunused-variable -Wuninitialized

all: Main.cc
	$(CC) $(FLAGS) -o Main Main.cc

clean:
	rm -f Main

run: clean all
	./Main

dbg:
	gdb -q --args ./Main example.txt