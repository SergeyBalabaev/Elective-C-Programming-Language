DFLAGS=-Wall -g -Werror -DDEBUG
RFLAGS=-Wall -Werror -O3

all: clean
	gcc -c $(RFLAGS) *.c
	gcc *.o $(RFLAGS) -o main
debug: clean
	gcc -c $(DFLAGS) *.c
	gcc *.o $(DFLAGS) -o main
lib: clean
	gcc -c main.c -o main.o
	gcc -shared -fpic -o *.so *lib.c
	gcc *.o *.so -Wl,-rpath,. -o main
clean:
	rm -f *.o
clean_all:
	rm -f *.o
	rm -f *so
