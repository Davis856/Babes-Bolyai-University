bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 25, 54, 68, 36, 79
    len equ ($-a)/2
    b times len db 0

; our code starts here
segment code use32 class=code
    start:
        mov esi, a
        mov edi, b
        mov ecx, len ; counter for loop
        mov bx, 10; basically we find out the remainder in dx which is the last digit by number%10
        jecxz Exit
        repeat_:
            lodsw ; add in ax and increments esi by 2, basically mov ax, [a+esi]
            mov dx, 0 ; clear the register dx for remainder after div
            div bx ; to get the remainder in dx
            mov ax, dx
            stosb ; stores in edi from ax
        loop repeat_
        Exit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
