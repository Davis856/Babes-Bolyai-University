bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s1 db 'a', 'c', 'e', 'i'
    len1 equ ($-s1)
    s2 db 'b', 'd', 'f', 'g', 'h'
    len2 equ ($-s2)
    final_s times (len1+len2) db 0
; our code starts here
segment code use32 class=code
    start:
        ; Being given two alphabetical ordered strings of characters, 
        ; s1 and s2, build using merge sort the ordered string of bytes that contain all characters from s1 and s2.
        mov ebx, 0
        mov ecx, 0
        mov eax, 0
        
        program:
            mov dl, [s1+eax]
            cmp dl, [s2+ebx] ; compare char of s1 with char of s2
            
            jg from_s2
            
                ; place from s1
                mov dl, [s1+eax] ; get char of s1
                mov [final_s + ecx], dl ; place char of s1 in final_s
                inc ecx
                inc eax
            
                ; if we reach the end of len1 we stop
                cmp eax, len1
                je end_loop_s1 
                
                jmp program ; start over if the array is not finished
            
            from_s2:
                mov dl, [s2+ebx] ; get char of s2
                mov [final_s + ecx], dl ; place char of s2 in final_s
                inc ecx
                inc ebx
                
                cmp ebx, len2
                je end_loop_s2 
                
                jmp program 
        
        end_loop_s1:
            ; loop for ebx
            end_s2:
                mov dl, [s2+ebx]
                mov [final_s + ecx], dl
                inc ecx
                inc ebx
                
                cmp ebx, len2
                je Exit
                
                jmp end_s2 ; we check if there is something left in this array, if it is we put it in the destination
                
        end_loop_s2:
            ; loop for eax
            finish_s1:
                mov dl, [s1+eax]
                mov [final_s + ecx], dl
                inc ecx
                inc eax
                
                cmp eax, len1
                je Exit
                
                jmp finish_s1
         
        Exit:     
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program