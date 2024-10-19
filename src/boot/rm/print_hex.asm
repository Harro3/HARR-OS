print_hex:
  pusha

  mov cx, 0 ; index var

hex_loop:
  cmp cx, 4 ; loop 4 times
  je hex_end

  ; convert last char to ascii
  mov ax, dx
  and ax, 0x000f
  add al, 0x30 ; move to ascii digits
  cmp al, 0x39 ; if > 9 -> move further to caps letters
  jle w_char
  add al, 7

w_char: ; write char to the string
  ; position = base_addr + len - index of char
  mov bx, HEX_OUT + 5
  sub bx, cx
  mov [bx], al

  ror dx, 4 ; next char

  add cx, 1
  jmp hex_loop

hex_end:

  ; call print subroutine
  mov bx, HEX_OUT
  call print
  popa
  ret

HEX_OUT:
  db "0x0000", 0
