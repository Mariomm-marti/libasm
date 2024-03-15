        global  ft_atoi_base
        extern  ft_strlen

        section .text
; The code for ft_atoi_base can be optimised by setting common
; registries, avoiding unecessary moves in memory
; rdi -> string of origin
; rsi -> base of origin
; r10 -> length of the base
; r11 -> result temporary
; r12 -> sign of result
; r13 -> length of the number
; r14 -> temporary base pos
; rax -> number after rsi to base 10
ft_atoi_base: ; get ready the registries
        xor     r11, r11
        xor     r13, r13
        mov     r12, 1
        push    rdi
        mov     rdi, rsi
        call    ft_strlen
        mov     r10, rax
        pop     rdi
ft_atoi_base_validate_base: ; checks if base has + or - and return
        push    rdi
        mov     rdi, 45
        call    basepos
        pop     rdi
        cmp     rax, -1
        jne     ft_atoi_base_end
        push    rdi
        mov     rdi, 43
        call    basepos
        pop     rdi
        cmp     rax, -1
        jne     ft_atoi_base_end
ft_atoi_base_skip_space: ; skips spaces and advances rdi to the point after it
        push    rdi
        movzx   rdi, byte [rdi]
        call    ft_atoi_base_isspace
        pop     rdi
        cmp     rax, 0
        je      ft_atoi_base_signs
        inc     rdi
        jmp     ft_atoi_base_skip_space
ft_atoi_base_signs: ; adjusts the sign to + or - for the final number using r12
        cmp     byte [rdi], 43
        je      ft_atoi_base_sign_pos
        cmp     byte [rdi], 45
        je      ft_atoi_base_sign_neg
        jmp     ft_atoi_base_calculate_numlen
ft_atoi_base_sign_pos:
        inc     rdi
        jmp     ft_atoi_base_signs
ft_atoi_base_sign_neg:
        inc     rdi
        neg     r12
        jmp     ft_atoi_base_signs
ft_atoi_base_calculate_numlen: ; calculates number len for exponent
        push    rdi
        movzx   rdi, byte [rdi + r13]
        call    basepos
        pop     rdi
        cmp     rax, 0
        jl      ft_atoi_base_main_loop
        inc     r13
        jmp     ft_atoi_base_calculate_numlen
ft_atoi_base_main_loop: ; while the number still exists, add current as base 10
        cmp     r13, 0
        jle     ft_atoi_base_end
        dec     r13
        push    rdi
        movzx   rdi, byte [rdi]
        call    basepos
        pop     rdi
        mov     r14, rax
        push    rdi
        push    rsi
        mov     rdi, r10
        mov     rsi, r13
        call    exponent
        mul     r14
        add     r11, rax
        pop     rsi
        pop     rdi
        inc     rdi
        jmp     ft_atoi_base_main_loop
ft_atoi_base_end: ; sets the number with the correct sign and returns it
        mov     rax, r11
        mul     r12
        ret

; rdi -> character to check
; rax -> 0 no space, 1 space
ft_atoi_base_isspace:
        cmp     rdi, 9
        je      ft_atoi_base_isspace_true
        cmp     rdi, 10
        je      ft_atoi_base_isspace_true
        cmp     rdi, 11
        je      ft_atoi_base_isspace_true
        cmp     rdi, 12
        je      ft_atoi_base_isspace_true
        cmp     rdi, 13
        je      ft_atoi_base_isspace_true
        cmp     rdi, 32
        je      ft_atoi_base_isspace_true
        xor     rax, rax
        ret
ft_atoi_base_isspace_true:
        mov     rax, 1
        ret

; rdi -> base number
; rsi -> exponent
; rax -> resulting number
exponent:
        mov     rax, 1
exponent_loop:
        cmp     rsi, 0
        je      exponent_end
        dec     rsi
        mul     rdi
        jmp     exponent_loop
exponent_end:
        ret

; rdi -> lookup char (num)
; rsi -> base string (ptr)
; rax -> position (num)
basepos:
        xor     rax, rax
basepos_loop:
        cmp     byte [rsi + rax], 0
        je      basepos_error
        cmp     byte [rsi + rax], dil
        je      basepos_end
        inc     rax
        jmp     basepos_loop
basepos_error:
        mov     rax, -1
basepos_end:
        ret
