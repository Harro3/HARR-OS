gdt_start:
  ; gdt start with 8 null bytes
  dd 0x0
  dd 0x0

  ; we define two segments in the header, code and data.
  ; base = 0, length = 0xfffff
gdt_code:
  dw 0xffff ; segment length bits 0-15
  dw 0x0    ; segment base lo
  db 0x0    ; segment base hi

  db 10011010b  ; flags
  db 11001111b  ; flags (4 bits) + segment length bits 16-19 ( why ??)
  db 0x0

  ; some flags change but basically the same for data segment
gdt_data:
  dw 0xffff
  dw 0x0
  db 0x0
  db 10010010b
  db 11001111b
  db 0x0

gdt_end:

gdt_descriptor:
  dw gdt_end - gdt_start - 1
  dd gdt_start

; constants for later
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
