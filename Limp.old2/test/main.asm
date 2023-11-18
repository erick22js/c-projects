
;.include "outro.asm"

;mov eax, 150
;mov ebx, 64
;mov ecx, 16
;strd ebx, eax, ecx
;ldmd edx, ebx, ecx

;adc ebx, 1:d
;begin:
;adc eax, 1:d
;jso @begin

mov ecx, 12
loop:
add eax, 1
sub ecx, 2-1
jnz @loop, ecx
