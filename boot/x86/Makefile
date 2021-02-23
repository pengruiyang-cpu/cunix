ASM_FLAGS = -I ../../include/

remake: 
	rm bootloader.bin
	make first

first: 
	make bootloader.bin

boot.bin: boot.asm
	nasm boot.asm -o boot.bin $(ASM_FLAGS)

loader.bin: loader.asm
	nasm loader.asm -o loader.bin $(ASM_FLAGS)

bootloader.bin: boot.bin loader.bin 
	cat boot.bin loader.bin >> bootloader.bin

clear:
	rm *.bin 
