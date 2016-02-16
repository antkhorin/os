default: hello_world

all: default

hello_world.o: hello_world.c
	gcc -c hello_world.c -o hello_world.o
hello_world: hello_world.o
	gcc hello_world.o -o hello_world

clean:
	rm -f hello_world.o
	rm -f hello_world
