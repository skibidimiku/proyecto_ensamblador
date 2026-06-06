bits 64
default rel

global generar_pixel_art

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
    je .valor_1

    ; camino
    mov al, '.'
    jmp .escribir

.valor_1:
    ; pared
    mov al, 219

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
