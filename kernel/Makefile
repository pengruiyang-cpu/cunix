default:
	make kernel.bin

init/main.o: init/main.c
	make -C init/

kernel.o: init/main.o
	ld -b elf64-x86-64 -o kernel.o init/main.o -T kernel.lds
	
kernel.bin: kernel.o
	objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary kernel.o kernel.bin



