C_FLAGS = -mcmodel=large -fno-builtin -m64 -I ../../include/

all: main.o print.o head.o

%.o: %.c
	gcc -c $*.c $(C_FLAGS)

head.o: head.s
	as --64 head.s -o head.o


clear:
	rm *.o

