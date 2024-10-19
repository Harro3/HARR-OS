CC=$(PWD)/cross/bin/i386-elf-gcc
LD=$(PWD)/cross/bin/i386-elf-ld
GDB=$(PWD)/cross/bin/i386-elf-gdb
AS=nasm
QEMU=qemu-system-x86_64

CFLAGS=-Iinclude -Iinclude/stdlib -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Wvla -pedantic -std=c99

BUILDDIR=./build
OBJDIR=$(BUILDDIR)/obj

SRC=$(wildcard src/kernel/*.c src/drivers/*.c src/stdlib/*.c)
HEADERS=$(wildcard src/kernel/*.h src/drivers/*.c src/stdlib/*.h)
KERNEL_ENTRY=src/kernel/entry.asm

KERNEL_ENTRY_OBJ=$(patsubst src/%.asm, $(OBJDIR)/%.o, $(KERNEL_ENTRY))
OBJ=$(patsubst src/%.c, $(OBJDIR)/%.o, $(SRC))

BS_BIN=$(BUILDDIR)/boot/main.bin
KERNEL_BIN=$(BUILDDIR)/kernel.bin
KERNEL_ELF=$(BUILDDIR)kernel.elf
BIN=$(BUILDDIR)/harr-os.bin

all: $(BIN)

boot: $(BIN)
	$(QEMU) -fda $(BIN)

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

$(KERNEL_ELF): $(KERNEL_ENTRY_OBJ) $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^

debug: CFLAGS+=-g
debug: $(BIN) $(KERNEL_ELF)
	$(QEMU) -s -fda $(BIN) &
	$(GDB)  -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL_ELF)"

$(OBJDIR)/%.o: src/%.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -ffreestanding -c $< -o $@

$(OBJDIR)/%.o: src/%.asm
	mkdir -p $(dir $@)
	$(AS) $< -f elf -o $@

$(BUILDDIR)/%.bin: src/%.asm
	mkdir -p $(dir $@)
	$(AS) -Isrc/boot $< -f bin -o $@

$(BIN): $(BS_BIN) $(KERNEL_BIN)
	cat $^ > $@


clean:
	$(RM) $(BIN)
	$(RM) $(KERNEL_BIN)
	$(RM) $(KERNEL_ELF)
	$(RM) $(BS_BIN)
	$(RM) $(OBJ)
	$(RM) $(KERNEL_ENTRY_OBJ)

.PHONY: all clean boot debug
