bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        


extern exit, fopen, fclose, printf, fread
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

; "%120[^\n]"

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "hw.txt", 0 ;filename to be created
    access_mode db "r", 0 ; file access mode : r - opens a file for reading. The file must exist.
    file_descriptor dd -1 ; variable to hold the file descriptor
    len equ 100
    text times (len+1) db 0
    format db "Y: %d, Z: %d", 0

; our code starts here
segment code use32 class=code
    start:
        ;A text file is given. Read the content of the file, 
        ;count the number of letters 'y' and 'z' and display the values on the screen. The file name is defined in the data segment.
        
        
        ; call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4*2 ; clean-up the stack
        
        mov [file_descriptor], eax ; store the file descriptor returned by fopen
        
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final
        
        ; read the file
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        mov ecx, eax ; counter for loop, where eax is my string's length in the file
        mov esi, 0 ; index for our array
        
        ; initialize counters for y and z, ebx = y, edx = z
        mov ebx, 0
        mov edx, 0
        
        find_letters:
            mov al, [text+esi] ; move in al each letter from the text to compare
            inc esi ; increase esi so that when the loop is getting here again it will take the next letter of the text
            cmp al, "y" ; compare the letter with y
            je for_ebx ; if the letter is y jump to for_ebx and increase the counter
            cmp al, "z" ; compare the letter with z
            je for_edx ; if the letter is z jump to for_edx and increase the counter
            jmp continue ; jump to continue which redoes the loop (if we don't jump it will increase ebx and then jump)
            for_ebx:
                inc ebx ; counter for y
                jmp continue ; if we don't jump to loop it will go to for_edx and increase counter for z which would be false
            for_edx:
                inc edx ; counter for z
                jmp continue ; this is not really necessary but for the sake of the beauty of the code, without it it just goes to loop
        continue:
            loop find_letters
            
        ; we prepare for printf, parameters in assembly work from right to left(imagine it in C)
        push dword text
        push dword edx ; counter for z
        push dword ebx ; counter for y
        push dword format ; %d
        call [printf]
        add esp, 4*4
        
        ; we prepare for closing the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
    final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
