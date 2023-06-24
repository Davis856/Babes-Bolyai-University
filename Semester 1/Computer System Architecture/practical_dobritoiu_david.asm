bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fprintf, printf, fscanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll


; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "test.txt", 0 ; filename to be created
    access_mode db "r+", 0 ; file access mode : r+ - opens a file for reading and writing. The file must exist.
    file_descriptor dd -1 ; variable to hold the file descriptor
    len equ 100
    current_number dd 0
    format db "%d", 0
    format_console db "Sum: %d, difference: %d", 0

; our code starts here
segment code use32 class=code
    start:
        
        
        ; we call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode ; r+ - read and write
        push dword file_name ; name of the file
        call [fopen]
        add esp, 4*2 ; clean up the stack
        
        mov [file_descriptor], eax ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final
        
    mov edi, 0 ; register for sum
    mov esi, 0 ; register for difference
    read:
        ;we read the grades one by one without spaces
        push dword current_number              ; address of the read number
        push dword format           
        push dword [file_descriptor]
        call [fscanf]
        add esp, 4*3 ; we clean up the stack
        
        cmp eax, 1                  ; if eax = 1 then read was a success
        jne print_console                    ; if eax is not 1, reading stops
        
        mov eax, [current_number]
        adc edi, eax
        sub esi, eax
        loop read
        
    print_console:
        ; we print the sum and difference in console
        push dword current_number
        push dword esi ; register for difference
        push dword edi ; register for sum
        push dword format_console ; sum : %d, diff : %d
        call [printf]
        add esp, 4*4
    
        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
    
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
