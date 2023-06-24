bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import printf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s1 db '10100111b', '01100011b', '110b', '101011b'
   len equ $-s1
    s2 times len/2 dw 0
    two dd 2
    cnt db 0
    format db "Number is %d", 10, 13, 0
; our code starts here
segment code use32 class=code

pow_2:
    mov eax, 1
    mov ecx, [esp+4]
    jecxz do_none
    power2:
        mul dword [two]
    loop power2
    do_none:
    
    ret 4
    
start:
    ; ...
    mov ecx, len
    mov ebx, 0
    mov edx, 0
    dec ecx
    mov esi, 0
    base_convert:
        mov edi, ecx
        mov al, [s1+ecx-1]
        cmp al, 'b'
        je set_bh
        
        cmp al, '1'
        je convert
        
        cmp al, '0'
        je skip
        
        convert:
            mov eax, esi
            push dword eax
            call pow_2
            add ebx, eax
            inc esi
            cmp esi, 0
            ja end_l
        set_bh:
            push dword ebx
            push dword formatp
            call [printf]
            add esp, 4*2
            mov ebx, 0
            mov esi, 0
            cmp esi, 0
            je end_l
            
        skip:
            inc esi
        end_l:
        mov ecx, edi
    loop compute_numbers
    push dword ebx
    push dword format
    call [printf]
    add esp, 4*2
    ; exit(0)
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program