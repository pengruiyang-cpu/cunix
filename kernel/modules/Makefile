SRCS = tty.o
C_FLAGS = -mcmodel=large -fno-builtin -m64 -I ../../include -Wall -Werror -O3 

all: $(SRCS)

%.o: %.c
	gcc -c $*.c $(C_FLAGS)

clear:
	rm *.o

