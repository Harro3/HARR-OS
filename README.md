# HARR-OS

Experimenting with C and x86, making an OS

For now, timer, tty, and keyboard support with very basic shell with echo, help and clear commands, may be extended in the future.

![[./docs/assets/example.png]]

# Booting with qemu:

You must have qemu installed, as well as a cross compiled version of gcc and ld (with target i386-elf).

For cross compilers: https://wiki.osdev.org/GCC_Cross-Compiler

Then, in the makefile, replace CC and LD variables

```sh
make boot
```
