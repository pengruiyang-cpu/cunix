all: tty.o panic.o

%.o: %.S
	gcc -E $*.S -I ../../include > $*.s
	as --64 $*.s -o $*.o 

clear:
	rm *.o *.s

