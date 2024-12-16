CC = g++
FLAGS = -Wall -Wextra

all: Main.cc
	$(CC) $(FLAGS) -o Main Main.cc

clean:
	rm -f Main *.o output.txt

run: clean
	make all
	touch output.txt
	./Main input.txt