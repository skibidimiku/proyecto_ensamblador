bits 64
default rel

global generar_pixel_art
global NextLehmer16
global generar_cantidad_monedas
global contar_monedas
global intercambiar_celdas

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

    cmp eax, 3
    je .jugador

    mov al, '.'
    jmp .escribir

.pared:
    mov al, 219
    jmp .escribir

.moneda:
    mov al, '$'
    jmp .escribir

.jugador:
    mov al, 'P'
    jmp .escribir

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

intercambiar_celdas:
    ;calcular el indice= fila1 * columnas + columna1
    mov eax, r8d;
    imul eax, edx;
    add eax, r9d;

    ;convertitr indice a desplazamiento
    movsxd rax, eax
    lea r10, [rcx + rax * 4]

    ;fila2 y columna2
    mov r11d, [rsp + 40]
    mov eax, r11d
    imul eax, edx
    mov r11d, [rsp + 48]
    add eax, r11d
    
    movsxd rax, eax
    lea r11, [rcx + rax * 4]

    ;ver si es pared o moneda
    mov eax, [r11]

    cmp eax, 1
    je .pared

    cmp eax, 2
    je .moneda

    jmp .intercambiar
 
.moneda:
    mov dword [r11], 0
    mov eax, [r10]
    mov r8d, [r11]

    mov [r10], r8d
    mov [r11], eax

    mov eax, 2
    ret

.intercambiar:
    ;intercambiar
    mov eax, [r10]
    mov r8d, [r11]

    mov [r10], r8d
    mov [r11], eax
    mov eax, 1
    ret

.pared:
    mov eax, 0
    ret
