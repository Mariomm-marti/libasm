        global ft_list_size

        section .text
; rdi -> first node of the linked list
; rax -> total count
ft_list_size:
        xor     rax, rax
        cmp     rdi, 0
        je      ft_list_size_end
        inc     rax ; head element also counts!
ft_list_size_loop:
        cmp     qword [ rdi + nodenext ], 0
        je      ft_list_size_end
        inc     rax
        mov     rdi, [ rdi + nodenext ]
        jmp     ft_list_size_loop
ft_list_size_end:
        ret

        section .data
nodedata equ    0
nodenext equ    8 ; 64-bit pointer
