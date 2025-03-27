section .data
pm db "In protected mode!!!:",10,13
pmlen equ $-pm
newline db "",10,13
newlen equ $-newline
rm db "In Real Mode!!!!:",10,13
rmlen equ $-rm
gdtc db "Contents of GDT are->"
gdtclen equ $-gdtc
ldtc db "Contents of LDT are->"
ldtclen equ $-ldtc
idtc db "Contents of IDT are->"
idtclen equ $-idtc
trc db "Contents of TR are->"
trclen equ $-trc
colon db ":"
colonlen equ $-colon

section .bss
idt resb 01
gdt resb 01
ldt resb 01
tr resb 01
cr0_data resb 01
result resb 04

;macro to readwrite
%macro rw 3
mov rax,%1
mov rdi,%1
mov rsi,%2
mov rdx,%3
syscall
%endmacro

;macro to exit
%macro exit 0
mov rax,60
mov rdi,00
syscall
%endmacro

section .text
global _start
_start:
smsw ebx       ; msw is machine state word
mov [cr0_data],ebx
bt ebx,0
jc x1
rw 01,rm,rmlen
jmp exitt
x1:rw 01,pm,pmlen

;contents of gdt
rw 01,gdtc,gdtclen
sgdt [gdt]
mov bx,[gdt+4]
call display
mov bx,[gdt+2]
call display
rw 01,colon,colonlen
mov bx,[gdt]
call display
rw 01,newline,newlen

;contents of idt
rw 01,idtc,idtclen
sidt [idt]
mov bx,[idt+4]
call display
mov bx,[idt+2]
call display
rw 01,colon,colonlen
mov bx,[idt]
call display
rw 01,newline,newlen

;contents of ldt
rw 01,ldtc,ldtclen
sgdt [ldt]
mov bx,[ldt+4]
call display
mov bx,[ldt+2]
call display
rw 01,colon,colonlen
mov bx,[ldt]
call display
rw 01,newline,newlen

;contents of tr
rw 01,trc,trclen
str [tr]
mov bx,[tr]
call display
rw 01,newline,newlen

exitt:exit


display:mov bx,ax
	mov cx,04
	mov rdi,result
	loop1:rol bx,04H
		mov al,bl
		and al,0FH
		cmp al,09H
		jg b1
		add al,30H
		jmp b2
	b1:add al,37H
	b2:mov byte[rdi],al
		inc rdi
		dec cx
		jnz loop1
	rw 01,result,04
	ret
