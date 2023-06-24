bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

segment data use32 class=data
    x dq 20
    a dw 4
    b db 5
    e dd 8
    c dw 10
    d db 18
; our code starts here
segment code use32 class=code
    start:
    ; x/2+100*(a+b)-3/(c+d)+e*e; a,c-word; b,d-byte; e-doubleword; x-qword
        mov EAX, [x+0]
        mov EDX, [x+4] ; EDX:EAX = x
        
        mov EBX, 2
        
        idiv EBX ; EAX = x/2
        
        mov ECX, EAX
        
        mov AL, [b]
        cbw
        
        mov BX, [a]
        
        add BX, AX ; BX = (a+b)
        
        mov AX, 100
        imul BX
        
        push DX
        push AX
        pop EDX ; EDX = DX:AX
        
        add ECX, EDX ; ECX = x/2+100*(a+b)

        
        ;3/(c+d)        
        mov AL, [d]
        cbw
        mov DX, AX; DX = AX = d
        
        mov AX, 3
        cwd
        
        mov BX, [c]
        
        add BX, DX ; BX = c+d
        
        
        idiv BX ; AX = 3/(c+d)
        cwde ; EAX = 3/(c+d)
        
        sub ECX, EAX; ECX = x/2+100*(a+b)-3/(c+d)
    
        mov EAX, ECX ; EAX = ECX
        cdq ; EDX:EAX = EAX
        
        mov EBX, EAX
        mov ECX, EDX ;  ECX : EBX = EDX:EAX
    
        mov EAX, [e] ; EAX = e
        imul dword [e] ; EDX:EAX = e*e
        
        add EBX, EAX
        adc ECX, EDX; ECX = x/2+100*(a+b)-3/(c+d)+e*e
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
