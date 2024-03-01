        global ft_strcmp

; rdi -> s1
; rsi -> s2

        section .text
ft_strcmp:
        mov     rax, 0
        
compare_loop:
        cmp     byte [rdi], 0x0
        je      end
        mov     r8b, byte [rdi]
        cmp     byte [rsi], r8b
        jg      end_small
        jl      end_big
        inc     rdi
        inc     rsi
        jmp     compare_loop

end:
        mov     rax, 0
        ret

end_big:
        mov     rax, 1
        ret

end_small:
        mov     rax, -1
        ret
