CC=$(PWD)/cross/bin/i386-elf-gcc
LD=$(PWD)/cross/bin/i386-elf-ld
GDB=$(PWD)/cross/bin/i386-elf-gdb
AS=nasm
QEMU=qemu-system-i386

CFLAGS=-Iinclude -Iinclude/stdlib -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Wvla -pedantic -std=c99

BUILDDIR=./build
OBJDIR=$(BUILDDIR)/obj

SRC=$(wildcard src/kernel/*.c src/kernel/**/*.c src/drivers/*.c src/stdlib/*.c src/stdlib/**/*.c src/x86/*.c)
HEADERS=$(wildcard include/**/*.h)
KERNEL_ENTRY=src/kernel/entry.asm
KERNEL_LD_SCRIPT="src/kernel/kernel.ld"

KERNEL_ENTRY_OBJ=$(patsubst src/%.asm, $(OBJDIR)/%.o, $(KERNEL_ENTRY))
OBJ=$(patsubst src/%.c, $(OBJDIR)/%.o, $(SRC)) $(OBJDIR)/x86/interrupt.o

BS_BIN=$(BUILDDIR)/boot/main.bin
KERNEL_BIN=$(BUILDDIR)/kernel.bin
KERNEL_ELF=$(BUILDDIR)/kernel.elf
BIN=$(BUILDDIR)/harr-os.bin

all: $(BIN)

boot: $(BIN)
	$(QEMU) -fda $(BIN)

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(OBJ)
	$(LD) -o $@ -T$(KERNEL_LD_SCRIPT) $^ --oformat binary

$(KERNEL_ELF): $(KERNEL_ENTRY_OBJ) $(OBJ)
	$(LD) -o $@ -T$(KERNEL_LD_SCRIPT) $^

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
	$(RM) -r $(BUILDDIR)

.PHONY: all clean boot debug
