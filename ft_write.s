        global ft_write
        extern __errno_location

; rdi -> fd
; rsi -> buff
; rdx -> count
; rax -> amount of printed chars or -1 if fail

        section .text
ft_write:
        mov     rax, 0x01
        syscall
        cmp     rax, 0
        jl      set_error
        ret

set_error:
        neg     rax
        mov     r8, rax
        call    __errno_location
        mov     [rax], r8
        mov     rax, -1
        ret
