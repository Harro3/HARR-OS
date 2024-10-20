[extern isr_handler]
[extern irq_handler]

; This is called when an interrup is detected, with some info about said interrupt in the stack, so when the isr_handler function is called, it has all the info in its argument (registers_t)
isr_common_sr:
  pusha
  mov ax, ds
  push eax ; save the data segment descriptor
  mov ax, 0x10 ; kernel data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call isr_handler
  ; hlt

  ; restore state
  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs ,ax
  popa
  add esp, 8 ; Cleans up the pushed error code and ISR number
  sti
  iret

irq_common_sr:
  pusha
  mov ax, ds
  push eax
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  call irq_handler
  pop ebx
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx
  popa
  add esp, 8
  sti
  iret

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_sr

; 1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_sr

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_sr

; 3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_sr

; 4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_sr

; 5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_sr

; 6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_sr

; 7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_sr

; 8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8
    jmp isr_common_sr

; 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_sr

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push byte 10
    jmp isr_common_sr

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push byte 11
    jmp isr_common_sr

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push byte 12
    jmp isr_common_sr

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push byte 13
    jmp isr_common_sr

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push byte 14
    jmp isr_common_sr

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_sr

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_sr

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_sr

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_sr

; 19: Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_sr

; 20: Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_sr

; 21: Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_sr

; 22: Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_sr

; 23: Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_sr

; 24: Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_sr

; 25: Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_sr

; 26: Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_sr

; 27: Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_sr

; 28: Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_sr

; 29: Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_sr

; 30: Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_sr

; 31: Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_sr

  ; IRQ handlers
irq0:
	cli
	push byte 0
	push byte 32
	jmp irq_common_sr

irq1:
	cli
	push byte 1
	push byte 33
	jmp irq_common_sr

irq2:
	cli
	push byte 2
	push byte 34
	jmp irq_common_sr

irq3:
	cli
	push byte 3
	push byte 35
	jmp irq_common_sr

irq4:
	cli
	push byte 4
	push byte 36
	jmp irq_common_sr

irq5:
	cli
	push byte 5
	push byte 37
	jmp irq_common_sr

irq6:
	cli
	push byte 6
	push byte 38
	jmp irq_common_sr

irq7:
	cli
	push byte 7
	push byte 39
	jmp irq_common_sr

irq8:
	cli
	push byte 8
	push byte 40
	jmp irq_common_sr

irq9:
	cli
	push byte 9
	push byte 41
	jmp irq_common_sr

irq10:
	cli
	push byte 10
	push byte 42
	jmp irq_common_sr

irq11:
	cli
	push byte 11
	push byte 43
	jmp irq_common_sr

irq12:
	cli
	push byte 12
	push byte 44
	jmp irq_common_sr

irq13:
	cli
	push byte 13
	push byte 45
	jmp irq_common_sr

irq14:
	cli
	push byte 14
	push byte 46
	jmp irq_common_sr

irq15:
	cli
	push byte 15
	push byte 47
	jmp irq_common_sr
