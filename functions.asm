section .bss
    x resq 1
section .data
    string_scanf db "%lf", 0
    two dq 2.0
    four dq 4.0
    string_out db "%.10lf", 10, 13, 0
section .text
global f1
global f2
global f3

f1:
    push ebp
    mov ebp, esp
    fld qword[esp+0x8]
    fld st0
    fmulp
    fld1
    faddp
    fld qword[four]
    fdivr
    fld1
    fadd
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp
    fld qword[esp+0x8]
    fld st0
    fld st0
    fmulp
    fmulp
    pop ebp
    ret
    
f3:
    push ebp
    mov ebp, esp
    fld qword[esp+0x8]
    fchs
    fld qword[two] 
    fyl2x 
    fld st0 
    frndint 
    fsubr st1,st0 
    fxch st1
    fchs 
    f2xm1 
    fld1 
    faddp st1,st0 
    fscale 
    fstp st1   
    pop ebp
    ret