bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 db 'a', 'b', 'c', 'b', 'e', 'f'
    l1 equ $-s1
    s2 db '1', '2', '3', '4', '5'
    l2 equ $-s2
    l equ l1+l2
    D times l db 0

; our code starts here
segment code use32 class=code
    start:
        ;Two character strings S1 and S2 are given. 
        ;Obtain the string D by
        ;concatenating the elements found on odd positions in S2 and the elements found on even positions in S1.
        mov ecx, l2
        program:
            mov esi, 0
            jecxz Exit
            Repeat_loop: ; 1, 3, 5
                mov edx, l2
                sub edx, ecx
                test edx, 1 ; test if odd
                jpo repeat_even
                mov al, [s2+edx]
                mov [D+esi], al ;1,3,5
                inc esi ;1,2,3
            repeat_even:
                loop Repeat_loop
            mov ecx, l1
            Repeat_loop2: ;b, b, f
                mov edx, l1
                sub edx, ecx
                test edx, 1 ;test if even
                jpe repeat_odd
                mov al, [s1+edx]
                mov [D+esi], al ; b, b, f
                inc esi ;4,5,6
            repeat_odd:
                loop Repeat_loop2
        Exit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
