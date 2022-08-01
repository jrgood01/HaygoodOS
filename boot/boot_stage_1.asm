.print_char:
    mov ah, 09h
    mov bh, 00h
    mov cx, 0fh
    int 10h
    ret
.print_str:
    .print_char_loop:
        lea si, [loaded_text_1]
        mov al, [si]
        cmp al, 0
        je .end_print_char_loop
        call .print_char
        inc si
        jmp .print_char_loop
    .end_print_char_loop:
    ret
.boot:
    mov si, loaded_text_1
    call .print_str
    
loaded_text_1 db "BOOT STAGE 1 [LOADED]",0