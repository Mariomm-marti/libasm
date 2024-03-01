        global ft_strcpy

; rdi -> dst
; rsi -> src
; rax -> will not change and will hold dst

        section .text
ft_strcpy:
        mov     rax, rdi ; we already know that we are returning the dst
        cld

copy_loop:
        cmp     byte [rsi], 0x0 ; if our src reached \0 we are done
        je      end
        movsb
        jmp     copy_loop

end:
        mov     byte [rdi], 0x0 ; add a final \0 :)
        ret
