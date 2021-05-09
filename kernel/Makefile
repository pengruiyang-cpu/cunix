OBJS = init/head.o init/main.o lib/bitmap.o lib/bitman.o asm/tty.o modules/tty.o asm/panic.o

default:
	make -C init/
	make -C lib/
	make -C asm/
	make -C modules/
	make kernel.bin

kernel.o: $(OBJS)
	ld -b elf64-x86-64 -o kernel.o $(OBJS) -T kernel.lds
	
kernel.bin: kernel.o
	objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary kernel.o kernel.bin


clear:
	make -C init/ clear
	make -C lib/ clear
	make -C asm/ clear
	make -C modules/ clear
	rm kernel.o kernel.bin

