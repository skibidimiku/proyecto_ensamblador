bits 64
default rel

global generar_pixel_art

section .text

generar_pixel_art:
    cmp r8d, 0
    jle .salida_vacia

    cmp r9d, 0
    jle .salida_vacia

    ; contador de filas
    mov r10d, r8d

.fila_loop:
    ; contador de columnas
    mov r11d, r9d

.columnas_loop:
    ; obtener valor actual de la matriz
    mov eax, [rcx]

    cmp eax, 1
    je .valor_1

    ; 0 -> '.'
    mov al, '.'
    jmp .escribir

.valor_1:
    ; 1 -> '#'
    mov al, '#'

.escribir:
    ; escribir carácter en salida
    mov [rdx], al

    ; avanzar matriz y salida
    add rcx, 4
    inc rdx

    ; siguiente columna
    dec r11d
    jnz .columnas_loop

    ; salto de línea al final de cada fila
    mov byte [rdx], 10
    inc rdx

    ; siguiente fila
    dec r10d
    jnz .fila_loop

    ; terminador de cadena
    mov byte [rdx], 0
    ret

.salida_vacia:
    mov byte [rdx], 0
    ret