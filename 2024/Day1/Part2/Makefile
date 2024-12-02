CC = g++
FLAGS = -Wall -Wextra

all: Main.cc
	$(CC) $(FLAGS) -o Main Main.cc

clean:
	rm -f Main *.o

run: clean
	make all
	./Main input.txt

push:
	git add .
	git commit -m "update"
	git push origin