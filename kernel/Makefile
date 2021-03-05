default:
	make -C init/
	make -C hal/
	make kernel.bin

kernel.o: init/main.o hal/terminal.o
	ld -b elf64-x86-64 -o kernel.o init/main.o hal/terminal.o -T kernel.lds
	
kernel.bin: kernel.o
	objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary kernel.o kernel.bin



