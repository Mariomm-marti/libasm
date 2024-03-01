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
        jne     end
        inc     rdi
        inc     rsi
        jmp     compare_loop

end:
        mov     r8b, byte [rdi]
        sub     r8b, byte [rsi]
        movsx   rax, r8b
        ret
