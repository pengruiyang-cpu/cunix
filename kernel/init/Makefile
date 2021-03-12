C_FLAGS = -mcmodel=large -fno-builtin -m64 -I ../../include/

all: main.o print.o

%.o: %.c
	gcc -c $*.c $(C_FLAGS)


clear:
	rm *.o

