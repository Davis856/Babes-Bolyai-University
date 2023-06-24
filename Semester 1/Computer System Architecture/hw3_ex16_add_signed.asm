bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
; a - byte, b - word, c - double word, d - qword - Signed representation

segment data use32 class=data
    a db 5
    b dw 10
    e dd 20
    d dq 50
; our code starts here
segment code use32 class=code
    start:
    ; (d-a)-(a-c)-d
        mov EBX, [d+0]
        mov ECX, [d+4] ; ECX:EBX = d
        
        mov AL, [a]
        cbw
        cwde
        cdq
        
        sub EBX, EAX
        sbb ECX, EDX ; ECX:EBX = d-a
        
        mov AL, [a]
        cbw
        cwde
        
        mov EDX, [e]
        sub EAX, EDX; EAX = a-c
        cdq
        
        sub ECX, EBX
        sbb EDX, EAX ; =(d-a)-(a-c)
        
        sub EBX, dword [d]
        sbb ECX, dword [d+4]
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
