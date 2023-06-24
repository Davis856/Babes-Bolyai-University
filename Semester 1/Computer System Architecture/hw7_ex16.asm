bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll             ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll     ; indicating to the assembler that the printf fct can be found in the msvcrt.dll library
import scanf msvcrt.dll 
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    result dd 0
    formatnrs db "%d", 0
    formatres db "%x", 0

; our code starts here
segment code use32 class=code
    start: ; Read two numbers a and b (in base 10) from the keyboard. Calculate and print their arithmetic average in base 16
        ;we ask for the values, a and b
        push dword result
        call [printf] ;call function printf for printing 
        add esp, 4*1 ; free parameters on the stack; 4 = size of dword; 1 = number of parameters
        
        ;first value asked is a
        push dword a
        push dword formatnrs
        call [scanf] ; call function scanf for reading
        add esp, 4*2 ; free parameters on the stack; 4 = size of dword; 2 = number of parameters
        
        push dword b
        push dword formatnrs
        call [scanf] ; call function scanf for reading
        add esp, 4*2 ; free parameters on the stack; 4 = size of dword; 2 = number of parameters
        
        ; we get the average
        mov ax, [a] ; ax = 15, for example
        add ax, [b] ; ax = 60, for example(b is 45)
        
        mov cl, 2
        idiv cl ; ax = 30
    
        push dword eax
        push dword formatres ; format in hexa
        call [printf] ;call function printf for printing 
        add esp, 4*2 ; free parameters on the stack; 4 = size of dword; 2 = number of parameters
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
