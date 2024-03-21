        global ft_list_push_front
        extern malloc

        section .text
; rdi -> beginning of the list as t_list **
; rsi -> allocated data ready to be placed in a node at the beginning
ft_list_push_front:
        push    rdi
        push    rsi
        mov     rdi, nodesize
        call    malloc ; malloc node size (16 bytes)
        cmp     rax, 0 ; malloc error
        je      ret
        pop     rsi
        pop     rdi
        mov     qword [rax + nodedata], rsi ; new->data = data
        cmp     qword [rdi], 0 ; check if current head is NULL
        je      nullhead
        mov     r8, qword [rdi]
        mov     qword [rax + nodenext], r8
        mov     qword [rdi], rax
        jmp     ret
nullhead:
        mov     qword [rdi], rax
        mov     qword [rax + nodenext], 0
ret:
        xor     rax, rax
        ret

        section .data
nodedata equ    0
nodenext equ    8 ; 64-bit pointer size
nodesize equ   16 ; 2x 64-bit pointers. One data, one next node
