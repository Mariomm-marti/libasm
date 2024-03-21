        global ft_read
        extern __errno_location

; rdi -> fd
; rsi -> buff
; rdx -> count
; rax -> read amount or -1 if fail

        section .text
ft_read:
        xor     rax, rax
        syscall
        cmp     rax, 0
        jl      set_error
        ret

set_error:
        neg     rax
        mov     r8, rax
        call    __errno_location wrt ..plt
        mov     [rax], r8
        mov     rax, -1
        ret
