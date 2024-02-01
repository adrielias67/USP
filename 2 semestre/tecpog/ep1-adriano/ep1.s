global _start

section .text
_start:





;lê a entrada da forma "modo_de_execução (espaço) número"
mov rdi, STDIN
mov rsi, buffer
mov rdx, 12 		; são no máximo 12 caracteres lidos na entrada
mov rax, 0         
syscall
                  
; transforma o número (de 1 a 999999936) de ASCII para um número real
mov rcx, 0 			; limpa o rcx
sub eax, 2      	; o clock começa da posição em que o número termina no buffer
mov ecx, eax   		; escaneia o número de trás pra frente
mov rdx, 0 			; dl terá a grandeza da casa decimal sendo lida

loop_scan:
mov rax, 0 			; limpa o rax
mov al, [buffer+ecx]
sub eax, '0' 		; transforma de ASCII para o número real
mov [grava_dl], dl 	; guarda dl, que em loop_mul10 terá seu valor alterado
call loop_mul10
mov dl, [grava_dl]

add [scan], eax		; soma dígito por dígito em scan, que guarda o número real

dec ecx
inc dl
cmp ecx, 2 			; o número acaba na posição 2, pois na 0 e 1 estão o modo e o espaço
jnl loop_scan

; [scan] tem o número





; lê o modo de execução
mov al, [buffer] 	; o modo está na posição 0 do buffer
sub al, '0'			; de ASCII para valor real
cmp al, 0
jz  modo0
jmp modo1





modo0:
mov eax, [scan] 	; [scan] tem o número lido
call proxPrimo 		; eax guarda o próximo primo
call imprime
jmp final





modo1:
mov eax, [scan] 	;[scan] tem o número lido
mov [numero], eax
mov ecx, 1          ; inicializa o clock (ao entrar no loop será mudado para 2, de onde começa)

loop_multiplos:
; o loop procura por 2 números (aqui chamados de múltiplos) que sejam resposta
mov eax, ecx      
call proxPrimo    	; o contador anda em primos
mov ecx, eax      
call quadrado     
mov ebx, [numero] 
cmp eax, ebx      	; faz o loop até a raiz do número 
jg  fim_modo1     	; nao imprime nada caso o quadrado do contador fique maior que o número
mov eax, [numero]
div ecx            
cmp edx, 0        	; se o resto (edx) é diferente de 0, não é um múltiplo possível
jnz loop_multiplos 	; 

; eax já tem o quociente
mov [quociente], eax; o quociente deve ser guardado, pois ele é o segundo número desejado
mov [grava_clock2], ecx
call ehPrimo        ; vê se segundo número achado , (quociente), também é primo
mov ecx, [grava_clock2]
cmp rax, 0        	
jz loop_multiplos 	; se não for primo, busca outro

; imprime os dois números, se achados
mov eax, ecx 	  	; ecx tem o primeiro múltiplo
call imprime

;imprime espaço entre os números
mov al, 32			; código do espaço em ASCII
mov [espaco], al
mov rdi, STDOUT
mov rsi, espaco
mov rdx, 1      
mov rax, 1      
syscall         
 
mov eax, [quociente]; [quociente] tem o segundo múltiplo
call imprime

fim_modo1:
jmp final





final:
	 ; finaliza o programa, depois de ter executado
	 ; imprime um \n no final
	 mov al, 10
	 mov [espaco], al 	; a variável espaco pode ser usada para este propósito
	 mov rdi, STDOUT
	 mov rsi, espaco
	 mov rdx, 1       	
	 mov rax, 1       
	 syscall          

     mov rdi, 0        	; cóigo de saída 0 = sucesso
     mov rax, 60       	; exit
     syscall           	; 





;////////////////////////FUNÇÕES////////////////////////
imprime:
	 ; imprime o número em eax
 	 mov ecx, 8 		; constrói o número a ser printado, de trás pra frente
	 loop_print:

	 mov ebx, 10
	 mov edx, 0 		; edx deve estar zerado para fazer a divisão
	 div ebx 			; quociente em eax, resto em dl
	 add dl, '0' 		; converte para ASCII
	 mov [print+ecx], dl; bota cada dígito em [print]
	 cmp eax, 0   		; se só tiver zeros à esquerda do último dígito lido, para 
	 jz fim_print
	 dec ecx
	 cmp ecx, 0
	 jnl loop_print

	 fim_print:

	 mov rdi, STDOUT 	
     mov rsi, print  	; [print] tem o número em ASCII
     mov rdx, 9      	; os números do programa têm 9 dígitos no máximo 
     mov rax, 1      	; write
     syscall         	

     ret





ehPrimo:
 	 ; dado um número (eax), verifica se é primo
     mov [num_ehP], eax; guarda uma cópia do número que está em eax para fazer comparações
     mov ecx, 2        ; inicializa o contador

     mov ebx, 1
     cmp eax, ebx      
     je  final_nao_ehPrimo; está definido que 1 não é primo

     loop_ehPrimo:
     mov eax, ecx      
     call quadrado     ; quadrado em eax

     cmp eax, [num_ehP]; compara o quadrado do contador com o número e faz comparações até a raiz do número
     jg  final_ehPrimo 

     mov eax, [num_ehP]
     div ecx           
     cmp edx, 0        ; o resto (edx) dirá se o número é divisível ou não
     jz  final_nao_ehPrimo
     inc ecx
     jmp loop_ehPrimo

     ; retorna 0 ou 1 de acordo com o resultado
     final_nao_ehPrimo:
     mov rax, 0        ; 0 : não é primo
     ret

     final_ehPrimo:
     mov rax, 1        ; 1 : é primo
     ret





proxPrimo:
     ; calcula o próximo número primo maior que o dado (eax)
     mov ecx, eax 				; o contador recebe o número atual e parte dele

     loop_proxPrimo:
     inc ecx
     mov eax, ecx
     mov [grava_clock], ecx 	; grava o valor do clock, que será mudado em ehPrimo
     call ehPrimo      		; rax=1: é primo / rax=0: não é primo
     mov ecx, [grava_clock]
     cmp rax, 0        
     jz  loop_proxPrimo 		; caso não seja primo, confira o próximo
     mov eax, ecx      
     ret                		; eax guarda o próximo primo





;////////////////////////FUNÇÕES DE CONTA////////////////////////
quadrado:
     ; calcula o quadrado de um número (eax)
     mul eax           ; 
     ret               ; produto guardado em eax





loop_mul10:
	 ; é usado para transformar o número lido em número real, em cada dígito
 	 ; multiplica um dígito por 10 até que ele corresponda à sua casa decimal 
 	 cmp dl, 0
  	 jz  final_loop_mul10
     mov [grava_dl2], dl ; é preciso gravar dl, pois a multiplicação altera edx 
 	 mov ebx, 10
     mul ebx 			; produto em eax
     mov dl, [grava_dl2]
 	 dec dl
 	 jmp loop_mul10

 	 final_loop_mul10:
 	 ret			; resultado em eax










section .data
STDIN: EQU 0
STDOUT: EQU 1



section .bss

;variáveis do scan
scan: resb 4 
buffer: resb 12
grava_dl: resb 1
grava_dl2: resb 1
modo: resb 1

;variáveis do print
print: resb 9
espaco: resb 1

;variáveis do modo0
num_ehP: resb 4         ; cópia de um número que será usada em "ehPrimo"
grava_clock: resb 4     ; guarda um valor de clock que será alterado, e precisa seer retomado

;variáveis para o modo1
numero: resb 4          ; guarda o número
grava_clock2: resb 4    ; guarda outro valor de clock que será alterado, e precisa ser retomado
quociente: resb 4       ; guarda um quociente para o modo 1