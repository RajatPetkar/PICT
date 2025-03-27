section .data
    prompt_choice db "Choose (1=HEX to BCD, 2=BCD to HEX, 3=EXIT): ", 0
    prompt_hex db "Enter 4-digit Hex (0x): ", 0
    prompt_bcd db "Enter 5-digit BCD: ", 0
    invalid_msg db "Invalid input!", 0xA, 0
    hex_result db "BCD result: ", 0
    bcd_result db "Hex result: 0x", 0
    newline db 0xA, 0

section .bss
    choice resb 2
    input resb 6
    output resb 6

section .text
    global _start

_start:
    call show_menu
    jmp _start

show_menu:
    ; Display menu
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt_choice
    mov edx, 43
    int 0x80

    ; Get choice
    mov eax, 3
    mov ebx, 0
    mov ecx, choice
    mov edx, 2
    int 0x80

    ; Process choice
    cmp byte [choice], '1'
    je do_hex_to_bcd
    cmp byte [choice], '2'
    je do_bcd_to_hex
    cmp byte [choice], '3'
    je exit
    call show_error
    ret

do_hex_to_bcd:
    ; Get hex input
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt_hex
    mov edx, 23
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, input
    mov edx, 5
    int 0x80

    ; Convert hex to binary
    xor eax, eax
    mov ecx, 4
    mov esi, input
hex_loop:
    shl eax, 4
    mov bl, [esi]
    cmp bl, '9'
    jbe .digit
    sub bl, 7
.digit:
    sub bl, '0'
    or al, bl
    inc esi
    loop hex_loop

    ; Convert to BCD
    xor edx, edx
    mov ebx, 10
    mov ecx, 5
    mov edi, output+4
bcd_loop:
    xor edx, edx
    div ebx
    add dl, '0'
    mov [edi], dl
    dec edi
    loop bcd_loop

    ; Show result
    mov eax, 4
    mov ebx, 1
    mov ecx, hex_result
    mov edx, 12
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, output
    mov edx, 5
    int 0x80
    call new_line
    ret

do_bcd_to_hex:
    ; Get BCD input
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt_bcd
    mov edx, 19
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, input
    mov edx, 6
    int 0x80

    ; Convert BCD to binary
    xor eax, eax
    mov ecx, 5
    mov esi, input
    mov ebx, 10
num_loop:
    imul eax, ebx
    mov dl, [esi]
    sub dl, '0'
    add eax, edx
    inc esi
    loop num_loop

    ; Convert to hex string
    mov ecx, 4
    mov edi, output+3
hexstr_loop:
    mov edx, eax
    and edx, 0xF
    cmp dl, 9
    jbe .hexdigit
    add dl, 7
.hexdigit:
    add dl, '0'
    mov [edi], dl
    shr eax, 4
    dec edi
    loop hexstr_loop

    ; Show result
    mov eax, 4
    mov ebx, 1
    mov ecx, bcd_result
    mov edx, 14
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, output
    mov edx, 4
    int 0x80
    call new_line
    ret

show_error:
    mov eax, 4
    mov ebx, 1
    mov ecx, invalid_msg
    mov edx, 13
    int 0x80
    ret

new_line:
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80
    ret

exit:
    mov eax, 1
    xor ebx, ebx
    int 0x80
