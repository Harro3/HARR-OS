; loads 'dh' sectors from drive 'dl' into ES:BX (Extra segment offset by bx)
disk_load:
  pusha

  ; save parameters 1 and 2
  push dx

  ; hard drive is: cylinder -> heads (layers) -> sectors (rings)

  mov ah, 0x02 ; -> read
  mov al, dh; -> number of sectors to read
  mov cl, 0x02 ; -> select sector, 1 is boot, 2 is available
  mov ch, 0x00 ; -> cylinder
  mov dh, 0x00 ; -> head number

  ; data will be stored at [es:bx] by the interrups
  int 0x13
  jc disk_error

  pop dx
  cmp al, dh  ; int sets al to sectors read, comparing with
              ; what was expected
  jne sectors_error
  popa
  ret

disk_error:
  mov bx, DISK_ERROR
  call print
  call print_nl
  mov dh, ah
  call print_hex ; check out error code: http://stanislavs.org/helppc/int_13-1.html
  jmp disk_loop

sectors_error:
  mov bx, SECTORS_ERROR
  call print

disk_loop:
  jmp $

DISK_ERROR: db "Disk read error:", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0

