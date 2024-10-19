[bits 16]
switch_to_pm:
  cli ; disable interrupts
  lgdt [gdt_descriptor] ; load the gdt descriptor

  ; set 32 bit mode in cr0
  mov eax, cr0
  or eax, 0x1
  mov cr0, eax

  jmp CODE_SEG:init_pm ; jump to new code segment


[bits 32]
init_pm: ; now we use 32 bits instructions
  ; update all segment registers
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov ebp, 0x90000 ; stack pointer at the top of free space
  mov esp, ebp

  call BEGIN_PM

