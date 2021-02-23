all:
	touch boot/x86/bootloader.bin
	make -C boot/x86/
	make -C kernel/

clear:
	rm boot/x86/*.bin kernel/*.bin cunix.img


lines:
	wc boot/x86/boot.asm boot/x86/loader.asm kernel/kernel.asm include/arch/x86/* -l

