        global ft_list_sort

        section .text
; Implemented sorting algorithm: bubble sort
; rdi -> pointer to a pointer of beginning of the list
; rsi -> pointer for the comparing function
;
; rcx -> temporary in-loop variable
; r8  -> auxiliar ft_list_sort_swap
ft_list_sort:
        cmp     rdi, 0
        je      ft_list_sort_end
        mov     rdi, qword [rdi] ; we can discard the ** and just leave *
ft_list_sort_outloop:
        cmp     rdi, 0
        je      ft_list_sort_end
        mov     rcx, qword [rdi + nodenext]
ft_list_sort_inloop:
        cmp     rcx, 0
        je      ft_list_sort_outloopnext
        push    rdi
        push    rsi
        push    rcx
        mov     r8, rsi
        mov     rdi, qword [rdi + nodedata]
        mov     rsi, qword [rcx + nodedata]
        call    r8
        pop     rcx
        pop     rsi
        pop     rdi
        cmp     eax, 0
        jg      ft_list_sort_swap
        mov     rcx, qword [rcx + nodenext]
        jmp     ft_list_sort_inloop
ft_list_sort_swap:
        mov     r8, qword [rdi + nodedata]
        push    r8
        mov     r8, qword [rcx + nodedata]
        mov     qword [rdi + nodedata], r8
        pop     r8
        mov     qword [rcx + nodedata], r8
        mov     rcx, qword [rcx + nodenext]
        jmp     ft_list_sort_inloop
ft_list_sort_outloopnext:
        mov     rdi, qword [rdi + nodenext]
        jmp     ft_list_sort_outloop
ft_list_sort_end:
        ret

        section .data
nodedata equ    0
nodenext equ    8 ; 64-bit pointer
