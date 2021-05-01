C_FLAGS = -mcmodel=large -m64 -fno-builtin -nostdlib -I ../../include/ -Wall -Werror -O3

all: bitmap.c bitman.c bitmap.o bitman.o 

%.o: %.c
	gcc -c $*.c $(C_FLAGS)


clear:
	rm *.o

