.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

.global _wait_1us, _wait_100us, _wait_1ms

; FCY = 16mhz
_wait_1us:
    repeat #9
    nop
    return

_wait_100us:
    repeat #1595
    nop
    return

_wait_1ms:
    push w0
    mov #10, w0
loop:
    call _wait_100us
    dec w0,w0
    bra nz,loop
    pop w0
    return
