all:
	touch boot/x86/bootloader.bin
	make -C boot/x86/
	make -C kernel/

clear:
	rm boot/x86/*.bin kernel/*.bin cunix.img

