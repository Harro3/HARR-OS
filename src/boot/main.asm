[org 0x7c00]
KERNEL_OFFSET equ 0x1000

  mov [BOOT_DRIVE], dl ; BIOS sets the boot drive in dl
  mov bp, 0x9000
  mov sp, bp
  
  mov bx, MSG_REAL_MODE
  call print
  call print_nl

  call load_kernel ; load the kernel from disk
  call switch_to_pm ; go to protected mode

  jmp $

%include "rm/print.asm"
%include "rm/print_hex.asm"
%include "rm/disk.asm"
%include "pm/gdt.asm"
%include "pm/print.asm"
%include "pm/pm_switch.asm"

[bits 16]
load_kernel:
  mov bx, MSG_LOAD_KERNEL
  call print
  call print_nl

  mov bx, KERNEL_OFFSET ; read from disk and store in 0x1000
  mov dh, 0x36
  mov dl, [BOOT_DRIVE]
  call disk_load
  ret

[bits 32]
BEGIN_PM:
  mov ebx, MSG_PROT_MODE
  call print_string_pm
  call KERNEL_OFFSET ; switch to kernel
  jmp $ ; loop if kernel exits

BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_LOAD_KERNEL db "Loading kernel into RAM", 0

; padding
times 510 - ($ - $$) db 0
dw 0xaa55
