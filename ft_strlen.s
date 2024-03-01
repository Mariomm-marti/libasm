        global ft_strlen

; rdi -> string to get the length from
; rax -> length of the string (return)

        section .text
ft_strlen:
        xor     rax, rax
        cmp     rdi, 0x0
        je      end

count_char:
        cmp     byte [rdi], 0x0
        je      end
        inc     rdi
        inc     rax
        jmp     count_char

end:
        ret
