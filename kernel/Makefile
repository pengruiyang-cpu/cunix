ASM_FLAGS = -I ../include


default:
	make ../cunix.img

kernel.bin: kernel.asm
	nasm kernel.asm -o kernel.bin $(ASM_FLAGS)

../cunix.img: kernel.bin 
	cat ../boot/x86/bootloader.bin kernel.bin >> boot.bin
	dd if=boot.bin of=../cunix.img


