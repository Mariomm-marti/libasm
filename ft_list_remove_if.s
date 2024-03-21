        global ft_list_remove_if
        extern free

        section .text
; r12 to 15 are used as they are callee-safe
; r12 -> head of linked list (t_list **)
; r13 -> data to use as a reference to remove
; r14 -> function used to compare (data ref) with current node
; r15 -> function called for the content of the node, if freed
;
; rdx -> current node
; rcx -> previous node
ft_list_remove_if: ; saving all registers that are callee-safe
        push    r12
        push    r13
        push    r14
        push    r15
        mov     r12, rdi ; reassigning registers to not push / pop everywhere
        mov     r13, rsi
        mov     r14, rdx
        mov     r15, rcx
        mov     rdx, qword [ rdi ] ; rdx current node, ** dereferencing
        mov     rcx, 0x0 ; previous node is null by default
loop:
        cmp     rdx, 0x0 ; if current node is null, we are done
        je      end
        mov     rdi, qword [ rdx ] ; load into rdi the data from curr node
        mov     rsi, r13 ; and into rsi the data ref to compare
        push    rdx ; not callee-safe registers push
        push    rcx
        call    r14 ; compare
        pop     rcx
        pop     rdx
        cmp     rax, 0 ; check if the data is the same
        jne     loop_skip ; if it is not, then we skip
        cmp     rdx, qword [ r12 ] ; data is same, is it head node?
        je      loop_free_head ; if head node, we need to update head ptr
        mov     rdi, qword [ rdx + nodenext ] ; rdi: curr->next
        mov     qword [ rcx + nodenext ], rdi ; prev->next = curr->next
        mov     rdi, [ rdx ] ; rdi is data of current node
        push    rcx
        push    rdx
        call    r15 ; free current node data
        pop     rdx
        mov     rdi, rdx ; free current node
        call    free wrt ..plt
        pop     rcx
        mov     rdx, qword [ rcx + nodenext ] ; not change previous only current
        jmp     loop
loop_skip:
        mov     rcx, rdx
        mov     rdx, qword [ rdx + nodenext ]
        jmp     loop
loop_free_head:
        mov     rdi, qword [ rdx + nodenext ]
        mov     qword [ r12 ], rdi
        mov     rcx, 0x0
        mov     rdi, qword [ rdx + nodedata ]
        push    rdx
        push    rcx
        call    r15
        pop     rcx
        pop     rdx
        mov     rdi, rdx
        push    rcx
        push    rdx
        call    free wrt ..plt
        pop     rdx
        pop     rcx
        mov     rdx, qword [ r12 ]
        jmp     loop
end:
        pop     r15
        pop     r14
        pop     r13
        pop     r12
        ret

        section .data
nodedata equ    0
nodenext equ    8 ; 64-bit pointer
