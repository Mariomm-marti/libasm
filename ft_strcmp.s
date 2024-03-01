        global ft_strcmp

; rdi -> s1
; rsi -> s2

        section .text
ft_strcmp:
        cmp     byte [rdi], 0x0
        je      end
        mov     r8b, byte [rdi]
        cmp     byte [rsi], r8b
        jne     end
        inc     rdi
        inc     rsi
        jmp     ft_strcmp

end:
        mov     r8b, byte [rdi]
        sub     r8b, byte [rsi]
        movsx   rax, r8b
        ret
