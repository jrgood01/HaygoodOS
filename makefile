CC = gcc
ASSEMBLE = nasm
AFLAGS = -f bin
CFLAGS = -c --freestanding -fno-stack-protector -nostdlib -march=x86-64
CFLAGS_BUILD_UTILS = -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -g
all: master_boot_record.bin
boot_tools: build_utils/create_boot_disk.c
	   $(CC) $(CFLAGS_BUILD_UTILS) build_utils/create_boot_disk.c build_utils/create_fat_boot_disk.c build_utils/utils.c -lglib-2.0 -o boot_tool -o create_boot_disk 
master_boot_record: master_boot_record.asm
	$(ASSEMBLE) $(AFLAGS) master_boot_record.asm -o master_boot_record.bin