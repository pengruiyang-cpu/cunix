default:
	make -C init/
	make -C lib/
	make -C asm/
	make kernel.bin

kernel.o: init/head.o init/main.o lib/bitmap.o lib/bitman.o asm/tty.o
	ld -b elf64-x86-64 -o kernel.o init/head.o init/main.o lib/bitmap.o lib/bitman.o asm/tty.o -T kernel.lds
	
kernel.bin: kernel.o
	objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary kernel.o kernel.bin


clear:
	make -C init/ clear
	make -C lib/ clear
	make -C asm/ clear
	rm kernel.o kernel.bin

