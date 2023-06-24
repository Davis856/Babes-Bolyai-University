bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 5
    e dw 2
    f dw 7

; our code starts here
segment code use32 class=code
    start:
        mov AL, [a] ; AL = a
        mul BYTE [a] ; AX = a*a
        
        mov BX, [e] ; BX=e
        add BX, [f] ; BX=e+f
        
        sub AX,BX ; AX = AX-BX
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
