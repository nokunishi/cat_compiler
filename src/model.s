.global _start
.align 2

_start:
    mov x0, #1        
    adrp x1,input@PAGE
    add x1, x1, input@PAGEOFF
    mov x2, #1024
    mov x16, #4       
    svc #0x80

    mov x0, #0
    mov x16, #1
    svc #0xFFFF


.data
input: .ascii "hello world"