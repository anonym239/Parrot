CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -O2 -Wall -nostdlib

all: parrotos.iso

boot.o: boot.s
	as --32 boot.s -o boot.o

kernel.o: kernel.c
	gcc $(CFLAGS) -c kernel.c -o kernel.o

parrotos.bin: boot.o kernel.o linker.ld
	ld -m elf_i386 -T linker.ld -o parrotos.bin boot.o kernel.o

parrotos.iso: parrotos.bin grub.cfg
	mkdir -p isodir/boot/grub
	cp parrotos.bin isodir/boot/parrotos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o parrotos.iso isodir

run: parrotos.iso
	qemu-system-i386 -cdrom parrotos.iso

clean:
	rm -rf *.o parrotos.bin parrotos.iso isodir
