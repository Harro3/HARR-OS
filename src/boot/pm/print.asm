[bits 32] ; 32 bits protected mode

VIDEO_MEM equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
  pusha
  mov edx, VIDEO_MEM

print_string_pm_loop:
  mov al, [ebx] ; address of the 1st char
  mov ah, WHITE_ON_BLACK ; bits on the left are the colors

  cmp al, 0 ; check for null byte
  je print_string_pm_done

  mov [edx], ax ; copy to video memory
  add ebx, 1 ; next char
  add edx, 2 ; next pos in memory

  jmp print_string_pm_loop

print_string_pm_done:
  popa
  ret

