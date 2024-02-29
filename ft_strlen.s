        global ft_strlen

; rdi -> string to get the length from
; rax -> length of the string (return)

        section .text
ft_strlen:
        xor     rax, rax
        cmp     rdi, 0x0
        je      _ft_strlen_end

_ft_strlen_count_char:
        cmp     byte [rdi], 0x0
        je      _ft_strlen_end
        inc     rdi
        inc     rax
        jmp     _ft_strlen_count_char

_ft_strlen_end:
        ret
