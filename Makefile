all:
	touch boot/x86/bootloader.bin
	make -C boot/x86/
	make -C kernel/
	make cunix.img

clear:
	make -C kernel/ clear
	make -C boot/x86/ clear
	rm cunix.img boot.bin



lines:
	wc boot/x86/boot.asm boot/x86/loader.asm kernel/init/*.c kernel/lib/*.c kernel/hal/vgatext/*.c include/arch/x86/* include/arch/*.h include/kernel/* include/lib/* -l


cunix.img: boot/x86/bootloader.bin kernel/kernel.bin
	dd if=/dev/zero of=cunix.img bs=1024 count=1440
	cat boot/x86/bootloader.bin kernel/kernel.bin > boot.bin
	dd if=boot.bin of=cunix.img conv=notrunc
