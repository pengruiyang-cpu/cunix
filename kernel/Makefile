default:
	make -C init/
	make -C hal/
	make -C lib/
	make kernel.bin

kernel.o: init/main.o hal/vgatext/vgatext.o lib/bitmap.o lib/bitman.o init/print.o
	ld -b elf64-x86-64 -o kernel.o init/main.o init/print.o hal/vgatext/vgatext.o lib/bitmap.o lib/bitman.o -T kernel.lds
	
kernel.bin: kernel.o
	objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary kernel.o kernel.bin


clear:
	make -C init/ clear
	make -C hal/ clear
	make -C lib/ clear
	rm kernel.o kernel.bin

