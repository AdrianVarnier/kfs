# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gdt_flush.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 18:13:32 by avarnier          #+#    #+#              #
#    Updated: 2026/02/09 18:13:32 by avarnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.globl gdt_flush

gdt_flush:
    mov 4(%esp), %eax
    lgdt (%eax)

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    jmp $0x08, $flush
flush:
    ret
