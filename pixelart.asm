bits 64
default rel

global generar_pixel_art
global NextLehmer16
global generar_cantidad_monedas
global contar_monedas

section .data

seed dw 1234
A dw 25173
M dw 65535

section .text


generar_pixel_art:

    cmp r8d, 0
    jle .salida_vacia

    cmp r9d, 0
    jle .salida_vacia

    mov r10d, r8d

.fila_loop:

    mov r11d, r9d

.columnas_loop:

    mov eax, [rcx]

    cmp eax, 1
    je .pared

    cmp eax, 2
    je .moneda

    mov al, '.'
    jmp .escribir

.pared:
    mov al, 219
    jmp .escribir

.moneda:
    mov al, '$'

.escribir:
    mov [rdx], al

    add rcx, 4
    inc rdx

    dec r11d
    jnz .columnas_loop

    mov byte [rdx], 10
    inc rdx

    dec r10d
    jnz .fila_loop

    mov byte [rdx], 0
    ret

.salida_vacia:
    mov byte [rdx], 0
    ret



NextLehmer16:

    mov ax, [seed]
    mul word [A]
    div word [M]
    mov [seed], dx
    ret



generar_cantidad_monedas:

    call NextLehmer16

    mov ax, dx
    xor dx, dx

    mov bx, 11
    div bx

    mov ax, dx
    add ax, 5

    ret



contar_monedas:

    mov eax, edx        
    imul eax, r8d       

    mov r10d, eax
    xor eax, eax

.contar_loop:

    cmp dword [rcx], 2
    jne .siguiente

    inc eax

.siguiente:

    add rcx, 4
    dec r10d
    jnz .contar_loop

    ret