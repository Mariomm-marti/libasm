        global ft_strdup
        extern malloc
        extern ft_strlen
        extern ft_strcpy

; rdi -> string to duplicate
; rax -> duplicated string beginning or NULL (0) if ENOMEM

        section .text
ft_strdup:
        push    rdi
        call    ft_strlen
        mov     rdi, rax
        inc     rdi
        call    malloc wrt ..plt
        cmp     rax, 0
        je      exit
        pop     rsi
        mov     rdi, rax
        call    ft_strcpy

exit:
        ret
