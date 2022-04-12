%include "io.inc"
section .bss
    x resq 1
section .data
    string_scanf db "%lf", 0
    two dq 2.0
    four dq 4.0
    string_out db "%.10lf", 10, 13, 0
section .text
global CMAIN
f1:
    push ebp
    mov ebp, esp
    
    fld qword [x]
    fld qword [x]
    fmulp
    fld1
    faddp
    fld qword[four]
    fdivr
    fld1
    fadd
    
    fstp qword[x] ;результат положили в переменную X. Но можно было бы не доставать из флоат стека, тогда ответ просто бы лежал сверху стека и в мейне можно его просто оттуда взять после кола
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp
    
    fld qword [x]
    fld qword [x]
    fld qword [x]
    fmulp
    fmulp
    
    fstp qword[x] ;результат положили в переменную X. Но можно было бы не доставать из флоат стека, тогда ответ просто бы лежал сверху стека и в мейне можно его просто оттуда взять после кола
    pop ebp
    ret
    
f3:
    push ebp
    mov ebp, esp
    
    fld qword[x]
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
           
    fstp qword[x] ;результат положили в переменную X. Но можно было бы не доставать из флоат стека, тогда ответ просто бы лежал сверху стека и в мейне можно его просто оттуда взять после кола
    pop ebp
    ret
     
CMAIN:
    mov ebp, esp; for correct debugging
    
    ;--------------------------------------------------------------------------------------
    ;считывание double x -> scanf ("%ld", &x). Аргументы в стек грузятся в обратном порядке
    ;--------------------------------------------------------------------------------------
    push x ;замечу, что здесь пушится указатель на икс
    push string_scanf
    call scanf
    add esp, 8 ;чтобы стек забыл про x, i, оба размера 4

    call f3
    
    ;------------------------------------------------------------------------------------------------
    ;т.к. система 32битная, мы не можем просто сказать pushq [x]. Поэтому стандартный алгоритм пуша qword
    ;это типа замена pushq
    ;------------------------------------------------------------------------------------------------
    fld qword[x]
    sub esp, 8  ;обычно push за нас сдвигает стек и записывает новое значение. А тут мы должны сами сдвинуть стек и записать в новое место, чтобы старые значения не повредить
    fstp qword[esp]
    push string_out
    call printf
    add esp, 12

    xor eax, eax
    ret
