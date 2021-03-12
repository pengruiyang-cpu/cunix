C_FLAGS = -mcmodel=large -fno-builtin -m64 -I ../../../include


all: vgatext.o


%.o: %.c
	gcc -c *$.c $(C_FLAGS)


clear:
	rm *.o

