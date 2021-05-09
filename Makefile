all:
	touch boot/x86/bootloader.bin
	make -C boot/x86/
	make -C kernel/
	make cunix.img

clear:
	make -C kernel/ clear
	make -C boot/x86/ clear
	rm cunix.img bootable



lines:
	wc -l `find ./ -name *.c -o -name *.asm -o -name *.s -o -name *.inc -o -name *.h -o -name *.S`


cunix.img: boot/x86/bootloader.bin kernel/kernel.bin
	dd if=/dev/zero of=cunix.img bs=1024 count=1440
	cat boot/x86/bootloader.bin kernel/kernel.bin > bootable
	dd if=bootable of=cunix.img conv=notrunc
