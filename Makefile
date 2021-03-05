all:
	touch boot/x86/bootloader.bin
	make -C boot/x86/
	make -C kernel/
	make cunix.img

clear:
	rm *.bin boot/x86/*.bin kernel/*.o kernel/*.bin kernel/init/*.o kernel/hal/*.o cunix.img -rf


lines:
	wc boot/x86/boot.asm boot/x86/loader.asm kernel/init/*.c kernel/hal/*.c include/arch/x86/* include/kernel/* -l


cunix.img: boot/x86/bootloader.bin kernel/kernel.bin
	dd if=/dev/zero of=cunix.img bs=1024 count=1440
	cat boot/x86/bootloader.bin kernel/kernel.bin > boot.bin
	dd if=boot.bin of=cunix.img conv=notrunc
