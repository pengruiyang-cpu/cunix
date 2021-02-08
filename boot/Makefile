remake: 
	echo "*** If there isn't 'bootloader.bin', use 'make first' ***"
	rm bootloader.bin
	make cunix.img

first: 
	make cunix.img

boot.bin: boot.asm
	nasm boot.asm -o boot.bin

loader.bin: loader.asm
	nasm loader.asm -o loader.bin

bootloader.bin: boot.bin loader.bin
	cat boot.bin loader.bin >> bootloader.bin

cunix.img: bootloader.bin
	dd if=/dev/zero of=cunix.img bs=1024 count=1440
	dd if=bootloader.bin of=cunix.img conv=notrunc


clear:
	rm *.bin cunix.img
