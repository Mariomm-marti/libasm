        global ft_list_push_front
        extern malloc

        section .text
; rdi -> beginning of the list as t_list **
; rsi -> allocated data ready to be placed in a node at the beginning
; r8  -> first node of linked list as t_list *
ft_list_push_front:
        push    rdi
        push    rsi
        mov     rdi, nodesize
        call    malloc ; malloc node size (16 bytes)
        pop     rsi
        pop     rdi
        cmp     rax, 0 ; malloc error
        je      ret
        mov     qword [rax + nodedata], rsi ; new->data = data
        mov     r8, qword [rdi]
        mov     qword [rax + nodenext], r8
        mov     qword [rdi], rax
        jmp     ret
ret:
        xor     rax, rax
        ret

        section .data
nodedata equ    0
nodenext equ    8 ; 64-bit pointer size
nodesize equ   16 ; 2x 64-bit pointers. One data, one next node
