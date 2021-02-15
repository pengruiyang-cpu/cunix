ASM_FLAGS = -I ../../include/

remake: 
	rm bootloader.bin
	make cunix.img

first: 
	make cunix.img

boot.bin: boot.asm
	nasm boot.asm -o boot.bin $(ASM_FLAGS)

loader.bin: loader.asm
	nasm loader.asm -o loader.bin $(ASM_FLAGS)

bootloader.bin: boot.bin loader.bin
	cat boot.bin loader.bin >> bootloader.bin

cunix.img: bootloader.bin
	dd if=/dev/zero of=cunix.img bs=1024 count=1440
	dd if=bootloader.bin of=cunix.img conv=notrunc


clear:
	rm *.bin cunix.img
