bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 01110001b ; 0111 0001b
    b dw 1010010010111001b ; 1010 0100 1011 1001b
    c dd 0

; our code starts here
;Given the byte A and the word B, compute the doubleword C as follows:
;the bits 0-7 of C have the value 1
;the bits 8-11 of C are the same as the bits 4-7 of A
;the bits 12-19 are the same as the bits 2-9 of B
;the bits 20-23 are the same as the bits 0-3 of A
;the bits 24-31 are the same as the high byte of B
segment code use32 class=code
    start:
        mov ebx, 0
        
        or ebx, 00000000000000000000000011111111b ; bits 0-7 of C have value 1
        
        mov eax, [a] ; we isolate the bits 4-7 of A
        and eax, 00000000000000000000000011110000b
        mov cl, 4
        rol eax, cl ; we rotate 4 positions to left
        or ebx, eax ; we put the bits into the result
        
        
        mov eax, [b] ; we isolate the bits 2-9 of B
        and eax, 00000000000000000000001111111100b ; 0000 0000 0000 0000 0000 0011 1111 1100
        mov cl, 10
        rol eax, cl ; we rotate 10 positions to the left
        or ebx, eax ; we put the bits into the result
        
        
        mov eax, [a] ; we isolate the bits 0-3 of A
        and eax, 00000000000000000000000000001111b ; 0000 0000 0000 0000 0000 0000 0000 1111
        mov cl, 20
        rol eax, cl ; we rotate 20 positions to the left
        or ebx, eax ; we put the bits into the result

        
        mov eax, [b] ; we isolate the high byte of B
        and eax, 00000000000000001111111100000000b ; 0000 0000 0000 0000 1111 1111 0000 0000b
        mov cl, 16
        rol eax, cl ; we rotate 15 positions to the left
        or ebx, eax ; we put the bits into the result
        
        mov [c], ebx ; we move the result from the register to the result variable
        
                                    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
