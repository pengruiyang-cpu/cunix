C_FLAGS = -mcmodel=large -fno-builtin -m64 -I ../../include/ -Wall -Werror -O3

all: main.o panic.o head.o

%.o: %.c
	gcc -c $*.c $(C_FLAGS)

head.o: head.S
	gcc -E head.S -I ../../include/ > head.s
	as --64 head.s -o head.o 


clear:
	rm *.o head.s

