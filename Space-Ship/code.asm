;**********************************************************************************************************************
;*-----------------------------------  INTRODUCAO A ARQUITETURA DE COMPUTADORES  -------------------------------------*
;**********************************************************************************************************************
;*Daniel Lopes          93696                                                                                         *
;*Antonio Venancio      93689                                                                                            *
;*Rafael Candeias       93748                                                                                             *
;**********************************************************************************************************************

;**********************************************************************************************************************
;*------------------------------------------------ CONSTANTES  -------------------------------------------------------*
;**********************************************************************************************************************
PIXELSCREEN      EQU 08000H                 ; ENDEREÇO DO ECRA 
FIM_PIXELSCREEN  EQU 08080H                 ; Fim do pixelscreen
DISPLAYS         EQU 0A000H                 ; ENDEREÇO DOS DISPLAYS (7 segmentos) 
TEC_LIN          EQU 0C000H                 ; ENDEREÇO DAS LINHAS   
TEC_COL          EQU 0E000H                 ; ENDEREÇO DAS COLUNAS
TECLA_ESQUERDA   EQU 00000H                 ; tecla para virar à esquerda 
TECLA_DIREITA    EQU 00003H                 ; tecla para virar à direita
TECLA_INICIAR    EQU 0000CH                 ; tecla para começar o jogo
TECLA_PAUSA      EQU 0000CH                 ; tecla para pausar o jogo
SOMA_PONTUACAO   EQU 00003H                 ; pontuação a somar
PONTUACAO_FINAL  EQU 00099H                 ; pontuação em que o jogo acaba


;**********************************************************************************************************************
;*-------------------------------------------  MASCARAS PARA PINTAR PIXEL  -------------------------------------------*
;**********************************************************************************************************************
PLACE       3000H
mascaras:
    STRING  080H, 040H, 020H, 010H, 08H, 04H, 02H, 01H

;**********************************************************************************************************************
;*-------------------------------  TABELA DO ECRA INICIAL (BRANCO COM LIMITES DA NAVE  -------------------------------*
;********************************************************************************************************************** 
ecra_limpo:                                ; ecra branco com a nave desenhada
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  00FH, 0FFH, 0FFH, 0F0H
    STRING  010H, 000H, 000H, 008H
    STRING  020H, 000H, 000H, 004H
    STRING  040H, 003H, 0C0H, 002H
    STRING  080H, 000H, 000H, 001H

ecra_inicio:                            ; ecra inicial
    STRING  000H, 000H, 000H, 000H
    STRING  01DH, 0DDH, 0C0H, 0B8H
    STRING  015H, 015H, 001H, 0A0H
    STRING  01DH, 09DH, 09CH, 0B8H
    STRING  011H, 011H, 000H, 0A8H
    STRING  011H, 0D1H, 0C0H, 0B8H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  003H, 000H, 002H, 040H
    STRING  007H, 080H, 001H, 080H
    STRING  007H, 080H, 001H, 080H
    STRING  003H, 000H, 002H, 040H
    STRING  000H, 000H, 000H, 000H 
    STRING  038H, 002H, 080H, 022H
    STRING  07CH, 005H, 040H, 014H
    STRING  07CH, 002H, 080H, 008H
    STRING  07CH, 005H, 040H, 014H
    STRING  038H, 002H, 080H, 022H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 001H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 001H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  000H, 001H, 000H, 000H
    STRING  000H, 000H, 000H, 000H
    STRING  00FH, 0FFH, 0FFH, 0F0H
    STRING  010H, 000H, 000H, 008H
    STRING  020H, 000H, 000H, 004H
    STRING  040H, 003H, 0C0H, 002H
    STRING  080H, 000H, 000H, 001H

ecra_final:                                         ;ecra final
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 003H, 0FFH, 0FFH, 080H
    STRING 002H, 022H, 0E8H, 080H
    STRING 002H, 0EAH, 04BH, 080H 
    STRING 002H, 0EAH, 04BH, 000H
    STRING 002H, 02AH, 0A9H, 000H
    STRING 002H, 0AAH, 0ABH, 000H
    STRING 002H, 0A2H, 0ABH, 080H
    STRING 002H, 02AH, 0A8H, 080H
    STRING 007H, 0FFH, 0FFH, 0C0H
    STRING 004H, 054H, 043H, 040H
    STRING 005H, 055H, 0DBH, 040H 
    STRING 005H, 055H, 0DBH, 040H
    STRING 005H, 054H, 0C3H, 040H
    STRING 005H, 055H, 0D7H, 040H
    STRING 005H, 06DH, 0D5H, 0C0H
    STRING 004H, 06CH, 055H, 040H
    STRING 007H, 0FFH, 0FDH, 0C0H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H
    STRING 000H, 000H, 000H, 000H

;**********************************************************************************************************************
;*------------------------------------------  TABELAS DOS OBJETOS A PINTAR  ------------------------------------------*
;**********************************************************************************************************************
volante_norm:                               ; volante na posicao
    STRING  3,4                             ; dimensoes (linhas, colunas)
    STRING  0,0,0,0                         ; tabela de pixeis
    STRING  1,1,1,1
    STRING  0,0,0,0

volante_drt:                                ; volante a virar para a direita
    STRING  3,4                             ; dimensoes (linhas, colunas)
    STRING  1,0,0,0                         ; tabela de pixeis
    STRING  0,1,1,0
    STRING  0,0,0,1

volante_esq:                                ; volante a virar para a esquerda
    STRING  3,4                             ; dimensoes (linhas, colunas)
    STRING  0,0,0,1                         ; tabela de pixeis
    STRING  0,1,1,0                     
    STRING  1,0,0,0

missil:                                     ; missil
    STRING  1,1
    STRING  1

asteroide_1:                                ; asteroide de tamanho 1
    STRING  1,1
    STRING  1

asteroide_2:                                ; asteroide de tamanho 2
    STRING  2,2
    STRING  1,1
    STRING  1,1

asteroide_bom_1:                            ; asteroide de tamanho 3 bom
    STRING  3,3
    STRING  1,0,1
    STRING  0,1,0
    STRING  1,0,1

asteroide_mau_1:                            ; asteroide de tamanho 3 mau
    STRING  3,3
    STRING  0,1,0
    STRING  1,1,1
    STRING  0,1,0

asteroide_bom_2:                            ; asteroide de tamanho 4 bom
    STRING  4,4
    STRING  1,0,0,1
    STRING  0,1,1,0
    STRING  0,1,1,0
    STRING  1,0,0,1

asteroide_mau_2:                            ; asteroide de tamanho 4 mau
    STRING  4,4
    STRING  0,1,1,0
    STRING  1,1,1,1
    STRING  1,1,1,1
    STRING  0,1,1,0

asteroide_bom_3:                            ; asteroide de tamanho 5 bom
    STRING  5,5
    STRING  1,0,0,0,1
    STRING  0,1,0,1,0
    STRING  0,0,1,0,0
    STRING  0,1,0,1,0
    STRING  1,0,0,0,1

asteroide_mau_3:                            ; asteroide de tamanho 5 mau
    STRING  5,5
    STRING  0,1,1,1,0
    STRING  1,1,1,1,1
    STRING  1,1,1,1,1
    STRING  1,1,1,1,1
    STRING  0,1,1,1,0

asteroide_destruido:                        ; asteroide de tamanho 5 com colisão do missil
    STRING  5,5
    STRING  0,1,0,1,0
    STRING  1,0,1,0,1
    STRING  0,1,0,1,0
    STRING  1,0,1,0,1
    STRING  0,1,0,1,0

;**********************************************************************************************************************
;*----------------------------------------------------  PILHA  -------------------------------------------------------*
;**********************************************************************************************************************
PLACE       2000H
pilha:      TABLE 200H                      ; espaço reservado para a pilha 
                                            ; (400H bytes, pois são 200H words)
SP_inicial:                                 ; este é o endereço (24000H) com que o SP deve ser 
                                            ; inicializado. O 1.º end. de retorno será 
                                            ; armazenado em 23FEH 2400H-2)

;**********************************************************************************************************************
;*--------------------------------------------  TABELA DE INTERRUPCOES  ----------------------------------------------*
;**********************************************************************************************************************
tab:      
    WORD rot_int_0                          ; rotina de atendimento da interrupção 0
    WORD rot_int_1                          ; rotina de atendimento da interrupção 1

;**********************************************************************************************************************
;*--------------------------------------------  TABELAS DE ESTADOS  --------------------------------------------------*
;**********************************************************************************************************************
evento_int:
    WORD 0                                  ; se 1, indica que a interrupção 0 ocorreu
    WORD 0                                  ; se 1, indica que a interrupção 1 ocorreu

asteroides:                                 ; tabela dos vários asteróides ativos
    WORD asteroide_ativo_1
    WORD asteroide_ativo_2
    WORD asteroide_ativo_3
    WORD 0                                  ; variável de fim

asteroide_a_pintar:                         
    WORD 0

asteroide_ativo_1:
    WORD 2                                  ; tipo de asteroide (0-mau e 2-bom)
    WORD 0                                  ; direção do asteroide
    WORD 0                                  ; linha do asteroide
    WORD 13                                 ; coluna do asteroide
tamanho_asteroide_ativo_1:
    WORD asteroide_1                        ; tipo de tamanho de asteroide

asteroide_ativo_2:
    WORD 0                                  ; tipo de asteroide (0-mau e 2-bom)
    WORD 1                                  ; direção do asteroide
    WORD 0                                  ; linha do asteroide
    WORD 13                                 ; coluna do asteroide
tamanho_asteroide_ativo_2:
    WORD asteroide_1                        ; tipo de tamanho de asteroide

asteroide_ativo_3:
    WORD 0                                 ; tipo de asteroide (0-mau e 2-bom)
    WORD -1                                 ; direção do asteroide
    WORD 0                                  ; linha do asteroide
    WORD 13                                 ; coluna do asteroide
tamanho_asteroide_ativo_3:
    WORD asteroide_1                        ; tipo de tamanho de asteroide

tipo_asteroide_tab:                         ; tabela do tipo de asteróide 
    WORD asteroide_mau_tab
    WORD asteroide_bom_tab

asteroide_bom_tab:                          ; tabela dos vários tamanhos de asteroides bons
    WORD asteroide_1
    WORD asteroide_2
    WORD asteroide_bom_1
    WORD asteroide_bom_2
    WORD asteroide_bom_3

asteroide_mau_tab:                          ; tabela dos vários tamanhos de asteroides maus
    WORD asteroide_1
    WORD asteroide_2
    WORD asteroide_mau_1
    WORD asteroide_mau_2
    WORD asteroide_mau_3

soma_tab:                                   ; tabela do valor da pontuação
    WORD 0                                  ; pontuação que está nos displays

tecla_pressionada:                          ; guarda na tabela a tecla que foi pressionada
    WORD 0                                  ; se nenhum tecla foi carregada o valor vai ser FFH

exec_anterior:                              ; guarda na tabela a tecla que foi pressionada na ação anterior
    WORD 0                                  

funcoes_teclado:                            ; cada word é um call para uma função dependendo da tecla pressionada
    WORD  virar_esquerda                    ; Tecla "0"
    WORD  ativar_missil                     ; Tecla "1"
    WORD  ativar_missil                     ; Tecla "2"
    WORD  virar_direita                     ; Tecla "3"
    WORD  0                                 ; Tecla "4"
    WORD  0                                 ; Tecla "5"
    WORD  0                                 ; Tecla "6"
    WORD  0                                 ; Tecla "7"
    WORD  0                                 ; Tecla "8"
    WORD  0                                 ; Tecla "9"
    WORD  0                                 ; Tecla "A"
    WORD  0                                 ; Tecla "B"
    WORD  iniciar_jogo                      ; Tecla "C"
    WORD  pausa_jogo                        ; Tecla "D"
    WORD  termina_jogo                      ; Tecla "E"
    WORD  0                                 ; Tecla "F"
    WORD  virar_normal                      ; Tecla "10"

tab_missil:                                 ; tabela de estrutura do misisil
    WORD 26                                 ; LINHAS
    WORD 16                                 ; COLUNAS

estado_missil:                              ; se o missil está ativo
    WORD 0                                  ; se tiver a 0 está desativo

estado_tecla_pausa:                         ; guarda na tabela se o jogo está em pausa ou não (1- está em pausa)
    WORD 0

estado_tecla_iniciar:
    WORD 0                                  ; guarda na tabela se o jogo vai iniciar

estado_tecla_terminar:
    WORD 0                                  ; guarda na tabela se o jogo vai terminar

estado_pinta_limpa:
    WORD 0                                  ; vai saber se pinta ou limpa o asteroide

estado_soma_max:
    WORD 0                                  ; vai ver se chegou à pontuação máxima

direcao_nave:                               ; guarda na tabela a direção para onde a nave está a virar
    WORD 0 

volante_atual:
    WORD 0                                  ; guarda o ultimo volante escrito

num_random:                                 ; guarda o nr pseudo-aleatório do gerador
     WORD 0

tab_gerador:                                 ; tabela de estrutura do asteroide a ser formado pelo gerador
     WORD 0                                  ; tipo do asteroide                     
     WORD 0                                  ; direção do asteroide

PLACE 0000H 
inicio: 
    MOV   BTE,  tab                         ; incializa BTE (registo de Base da Tabela de Exceções)          
    MOV   SP,   SP_inicial                  ; inicializa SP para a palavra a seguir
                                            ; à última da pilha
    CALL  escreve_ecra_inicial              ; escreve um ecrã de inicio
    
    EI0                                     ; permite interrupção 0
    EI1                                     ; permite interrupção 1
    EI                                      ; permite interrupções geral


pre_loop:                                   ; loop inicial
    CALL  teclado                           ; vai ver se a tecla de iniciar o jogo foi pressionada
    CALL  exec_teclado                      ; vai executar a tecla pressionada
    CALL  gerador_random                    ; vai atualizar a tabela de valores random
    MOV   R10, estado_tecla_iniciar         ; vê se a tecla de inicio (C) ativou a flag ou não
    MOV   R10,[R10]
    CMP   R10, 0
    JZ    pre_loop                          ; se não tiver ativado o ciclo não continua
    CALL  escreve_ecra_limpo                ; limpa o ecra
    CALL  iniciar_displays                  ; inicializa os displays a 00

main_loop:                                  ; loop principal
    CALL  teclado                           ; vai ver se a tecla de iniciar o jogo foi pressionada
    CALL  gerador_random                    ; vai atualizar a tabela de valores random
    CALL  exec_teclado                      ; vai executar a tecla pressionada
    CALL  movimenta_asteroide               ; vai mexer qualquer asteroide ativo
    CALL  disparar_missil                   ; vai poder disparar ou não um missil
    CALL  gerador_random                    ; vai atualizar a tabela de valores random
    MOV   R10, estado_tecla_terminar        ; vê se a tecla de fim foi pressionada ou se o jogo chegou ao máximo de pontuação ativando a flag
    MOV   R10,[R10]
    CMP   R10, 1
    JZ    end_loop                          ; setiver ativa a flag procede para o último loop
    JMP   main_loop

end_loop:
    CALL  teclado                           ; vai ver se a tecla de iniciar o jogo foi pressionada
    CALL  exec_teclado                      ; vai executar a tecla pressionada
    CALL  escreve_ecra_final                ; escreve o ecra final 
    CALL  reset_asteroides                  ; dá reset à estrutura dos novos asteroides
    MOV   R10, estado_tecla_terminar        ; vê se a tecla de fim foi pressionada ou se o jogo chegou ao máximo de pontuação ativando a flag
    MOV   R10,[R10]
    CMP   R10, 0
    JZ    pre_loop                          ; se~estiver uma nota muito bom?
    JMP   end_loop

;**********************************************************************************************************************
;*------------------------------------------------  RESET ASTEROIDES  ------------------------------------------------*
;**********************************************************************************************************************
reset_asteroides:                       ; dá reset à estrutura dos novos asteroides           
    PUSH  R0
    PUSH  R1
    PUSH  R2
    PUSH  R3
    PUSH  R4
    PUSH  R5

    MOV   R0, asteroides
    SUB   R0, 2

    CALL gerador_random                 ; vai atualizar a tabela de valores random
inicio_reset_asteroides:                ; permite fazer inumeras iterações até encontrar um 0 numa word
    ADD   R0, 2
    MOV   R2, [R0]
    MOV   R1, 0
    CMP   R2, R1
    JZ    sai_reset_asteroides

    CALL gerador_random
    MOV   R3, tab_gerador               ; vai retirar informação para o tipo e a direção dos asteroides a criar
    MOV   R4,[R3]
    MOV   R5,[R3+2]


    MOV  [R2], R4                       ; vai guardar no asteroide ativo correspondente a estrutura que vai ter
    MOV  [R2+2],R5
    MOV   R1,0
    MOV  [R2+4],R1
    MOV   R1,13
    MOV  [R2+6],R1

    JMP   inicio_reset_asteroides

sai_reset_asteroides:
    POP   R5
    POP   R4
    POP   R3
    POP   R2
    POP   R1
    POP   R0
    RET
;**********************************************************************************************************************
;*-------------------------------------------------  INTERRUPÇÃO 0  --------------------------------------------------*
;**********************************************************************************************************************
rot_int_0:                      ; ativa a flag de interrupção 0
     PUSH R0
     PUSH R1

     MOV  R0, evento_int
     MOV  R1, 1               ; assinala que houve uma interrupção 0
     MOV [R0], R1            ; na componente 0 da variável evento_int

     POP  R1
     POP  R0
     RFE

;**********************************************************************************************************************
;*-------------------------------------------------  INTERRUPÇÃO 1  --------------------------------------------------*
;**********************************************************************************************************************
rot_int_1:                      ; ativa a flag de interrupção 1
     PUSH R0
     PUSH R1

     MOV  R0, evento_int
     MOV  R1, 1               ; assinala que houve uma interrupção 1
     MOV [R0+2], R1          ; na componente 1 da variável evento_int

     POP  R1
     POP  R0
     RFE

;**********************************************************************************************************************
;*---------------------------------------------------  TECLADO  ------------------------------------------------------*
;**********************************************************************************************************************
teclado:
    PUSH R0                                 ; armazena todos os registos para nao haver perda de informacao
    PUSH R1
    PUSH R3
    PUSH R4
    PUSH R5
    PUSH R6
    PUSH R7
    PUSH R8
    PUSH R9
    PUSH R10

inicio_teclado:
    MOV  R5, 0008H                          ; contador de linhas inicia na 4º linha (1000B = 0008H)
    MOV  R6, 0000H                          ; garantir que começa a 0

verificar_tecla:                            ; ver se há tecla
    MOV  R0, TEC_LIN                        ; endereço do periférico das linhas
    MOV  R1, TEC_COL                        ; endereço do periférico das colunas
    MOV  R3, 0000H                          ; garantir que começa a 0
    MOV  R8, tecla_pressionada              ; endereço da tabela onde se guarda a tecla que foi pressionada
    
    MOV  R4, R5                             ; aponta a linha a testar
    MOVB[R0],R4                             ; escreve no periférico de saída qual é a linha
    MOVB R3,[R1]                            ; ler a coluna
    SHR  R5, 1                              ; passar da linha 2 para a linha 1 (passar do nibble 0010 para 0001)
    ADD  R6, 1                              ; contar quantas vezes iniciou o ciclo
    CMP  R6, 5                              ; ver se já percorreu 4 vezes o ciclo
    JZ   tecla_10                           ; se já tiver percorrido o teclado vai meter a tecla pressionada como 10
    CMP  R3, 0                              ; ver se foi premida alguma coluna na linha
    JZ   verificar_tecla                    ; se nenhuma tecla for premida reinicia o ciclo até alguma o ser
    JMP  calc_linha                         ; vai calcular a linha

encontrou_tecla:                            ; encontrou um tecla e vai guardá-la numa tabela
    SHL  R4, 2                              ; multiplica por 4
    ADD  R4, R3                             ; adiciona a coluna
    MOV [R8],R4                             ; guarda na tabela da tecla pressionada a tecla
    JMP  sai_teclado

;*------------------------------------------------  CALCULO DA TECLA  ------------------------------------------------*

calc_linha:                                 ; calcular a linha (0 a 3)
    MOV  R7, 4                              ; meter este registo a 4
    SUB  R7, R6                             ; linha = 4 - nr do contador
    MOV  R4, R7                             ; guardar esse resultado
    JMP  ver_se_coluna_1                    ; vai calcular a coluna

ver_se_coluna_1:                            ; se for a primeira coluna mete esta com valor 0
    MOV  R7, 0                              ; coloca o contador de divisões a 0
    CMP  R3, 1                              ; vê se a coluna é a 1
    JNZ  calc_coluna                        ; se não for a 1 vai para o processo de calculo da coluna
    MOV  R3, 0                              ; se for a 1, vai passar a 0
    JMP  encontrou_tecla                    ; retoma o processo

calc_coluna:                                ; calcular a coluna (1 a 3)
    SHR  R3, 1                              ; dividir por 2
    ADD  R7, 1                              ; conta quantas vezes divide até dar 1
    CMP  R3, 1                              ; ve se já chegou a 1
    JNZ  calc_coluna                        ; se ainda nao chegou a 1 repete este ciclo
    MOV  R3, R7                             ; guarda o novo valor para a coluna
    JMP  encontrou_tecla                    ; retoma o processo
;*--------------------------------------------------------------------------------------------------------------------* 

tecla_10:   
    MOV  R1,  010H
    MOV [R8], R1                            ; guarda na tabela da tecla pressionada a tecla 10
    JMP  sai_teclado

sai_teclado:  
    POP  R10
    POP  R9
    POP  R8                                 ; recupera todos os registos que foram armazenados
    POP  R7
    POP  R6
    POP  R5
    POP  R4
    POP  R3
    POP  R1
    POP  R0
    RET                                     ; retorna a onde estava (lugar do call)

;**********************************************************************************************************************
;*---------------------------------------------  FUNÇÕES DO TECLADO  -------------------------------------------------*
;**********************************************************************************************************************
exec_teclado:
    PUSH  R0
    PUSH  R1
    PUSH  R2
    PUSH  R3
    PUSH  R4 

    MOV   R0, funcoes_teclado               ; endereço da tabela de funçoes do teclado
    MOV   R1, tecla_pressionada             ; endereço da tecla pressionada
    MOV   R2,[R1]                           ; guarda o valor da tecla pressionada num registo
    SHL   R2, 1                             ; multiplica esse valor de tecla por 2
    ADD   R0, R2                            ; soma para saber a word na tabela de funçoes a que corresponde à tecla pressionada
    MOV   R3,[R0]                           ; guarda o valor da word num registo

    MOV   R2, virar_normal                  ; se a execução for a da tecla "vazia", executa sempre 
    CMP   R3, R2
    JZ    exec_qualquer

    MOV   R2, pausa_jogo                    ; se a ultima instrução tiver sido a de pausa ele não a repete evitanto assim tirar a pausa por acidente
    MOV   R4, exec_anterior
    MOV   R4, [R4]
    CMP   R4, R2
    JZ    sai_exec_teclado

    CMP   R3, 0                             ; vê se essa word é 0
    JZ    sai_exec_teclado                  ; se for 0 não realiza o call da função da tecla pressionada

exec_qualquer:
    CALL  R3                                ; se não for 0 dá call da função da tecla pressionada

    MOV   R4, exec_anterior                 ; guarda numa tabela a ultima execução
    MOV  [R4],R3        

sai_exec_teclado:
    POP   R4    
    POP   R3
    POP   R2
    POP   R1
    POP   R0
    RET

;**********************************************************************************************************************
;*-------------------------------------------------  INICIAR O JOGO  -------------------------------------------------*
;**********************************************************************************************************************
iniciar_jogo:
    PUSH  R0
    PUSH  R1
    PUSH  R2

    MOV   R0, estado_tecla_iniciar              ; vê se a flag de iniciar já estava ativa
    MOV   R1, 1
    MOV   R2,[R0]
    CMP   R1, R2
    JZ    sai_iniciar_jogo                      ; se estiver ativa salta este processo
    MOV  [R0],R1

    MOV  R0, estado_tecla_terminar              ; desativa a flag de fim
    MOV  R1, 0
    MOV [R0],R1

    JMP   sai_iniciar_jogo

sai_iniciar_jogo:
    POP  R2
    POP  R1
    POP  R0
    RET

;**********************************************************************************************************************
;*---------------------------------------------------  PAUSA JOGO  ---------------------------------------------------*
;**********************************************************************************************************************
pausa_jogo:                                 ; altera o estado da tabela de pausa (1- está em pausa)
    PUSH R0
    PUSH R1

    MOV  R0, estado_tecla_pausa             ; endereço da tabela onde se guarda o estado da tecla pausa
    MOV  R1,[R0]                            ; mete o valor do estado num registo
    CMP  R1, 0                              ; ve se esse registo estava a 0 (se o jogo não estava em pausa)
    JZ   mete_pausa                         ; se não estava em pausa vai colocar em pausa
    JMP  tira_pausa                         ; se estava em pausa vai tirar da pausa

mete_pausa:                                 ; mete em pausa
    MOV  R1, 1                              
    MOV [R0],R1                             ; mete o estado a 1
    JMP  sai_pausa_jogo                     ; sai fora do pausa_jogo

tira_pausa:                                 ; tira de pausa
    MOV  R1, 0
    MOV [R0],R1                             ; mete o estado a 0
    JMP  sai_pausa_jogo                     ; sai fora do pausa_jogo

sai_pausa_jogo:                             ; para sair do pausa_jogo
    POP  R1
    POP  R0
    RET

;**********************************************************************************************************************
;*-----------------------------------------------  FINALIZAR O JOGO  -------------------------------------------------*
;**********************************************************************************************************************
termina_jogo:
    PUSH  R0
    PUSH  R1
    PUSH  R2

    MOV   R0, estado_tecla_terminar             ; se a flag de terminar já estiver ativa salta este processo
    MOV   R1, 1
    MOV   R2,[R0]
    CMP   R1, R2
    JZ    sai_termina_jogo
    MOV  [R0],R1                                ; senão desativa a flag de iniciar

    MOV  R0, estado_tecla_iniciar             ; endereço da tabela onde se guarda o estado da tecla pausa
    MOV  R1,0
    MOV [R0],R1

    JMP   sai_termina_jogo

sai_termina_jogo:
    POP  R2
    POP  R1
    POP  R0
    RET  

;**********************************************************************************************************************
;*----------------------------------  PINTAR O ECRA LIMPO (BRANCO COM OS LIMITES DA NAVE)  ---------------------------*
;**********************************************************************************************************************
escreve_ecra_limpo:                        ; pintar o ecra inicial
    PUSH  R0
    PUSH  R1
    PUSH  R2
    PUSH  R3

    MOV   R0, PIXELSCREEN                   ; R0 = valor RAM de onde o Pixelscreen começa
    MOV   R1, FIM_PIXELSCREEN               ; R1 = valor RAM onde o Pixelscreen acaba
    MOV   R2, ecra_limpo                   ; R2 = valor do endereço onde começa as strings para pintar o ecra inicial

continuar_escreve_ecra_limpo:              
    MOVB  R3, [R2]                          ; R3 = o valor dentro da string (a pintura do byte)
    MOVB [R0], R3                           ; [R0] = pintura do byte no Pixelscreen
    ADD   R0, 1                             ; passa para o proximo byte
    ADD   R2, 1                             ; passa para o proximo valor de pintura do byte
    CMP   R0, R1                            ; ver se ja chegou ao valor RAM onde o Pixelscreen acaba
    JNZ   continuar_escreve_ecra_limpo     ; se ainda nao tiver acabado o Pixelscreen todo continua a pintar

    POP   R3
    POP   R2
    POP   R1
    POP   R0

    RET                                     ; retorna a onde estava (lugar do call) 

;**********************************************************************************************************************
;*-------------------------------------------  PINTAR O ECRA INICIAL (DESENHO)  --------------------------------------*
;**********************************************************************************************************************
escreve_ecra_inicial:                        ; pintar o ecra inicial
    PUSH  R0
    PUSH  R1
    PUSH  R2
    PUSH  R3

    MOV   R0, PIXELSCREEN                   ; R0 = valor RAM de onde o Pixelscreen começa
    MOV   R1, FIM_PIXELSCREEN               ; R1 = valor RAM onde o Pixelscreen acaba
    MOV   R2, ecra_inicio                   ; R2 = valor do endereço onde começa as strings para pintar o ecra inicial

continuar_escreve_ecra_inicial:              
    MOVB  R3, [R2]                          ; R3 = o valor dentro da string (a pintura do byte)
    MOVB [R0], R3                           ; [R0] = pintura do byte no Pixelscreen
    ADD   R0, 1                             ; passa para o proximo byte
    ADD   R2, 1                             ; passa para o proximo valor de pintura do byte
    CMP   R0, R1                            ; ver se ja chegou ao valor RAM onde o Pixelscreen acaba
    JNZ   continuar_escreve_ecra_inicial     ; se ainda nao tiver acabado o Pixelscreen todo continua a pintar

    POP   R3
    POP   R2
    POP   R1
    POP   R0

    RET                                     ; retorna a onde estava (lugar do call) 

;**********************************************************************************************************************
;*--------------------------------------------  PINTAR O ECRA FINAL (DESENHO)  ---------------------------------------*
;**********************************************************************************************************************
escreve_ecra_final:                         ; pintar o ecra final
    PUSH  R0
    PUSH  R1
    PUSH  R2
    PUSH  R3

    MOV   R0, PIXELSCREEN                   ; R0 = valor RAM de onde o Pixelscreen começa
    MOV   R1, FIM_PIXELSCREEN               ; R1 = valor RAM onde o Pixelscreen acaba
    MOV   R2, ecra_final                      ; R2 = valor do endereço onde começa as strings para pintar o ecra inicial

continuar_escreve_ecra_final:              
    MOVB  R3, [R2]                          ; R3 = o valor dentro da string (a pintura do byte)
    MOVB [R0], R3                           ; [R0] = pintura do byte no Pixelscreen
    ADD   R0, 1                             ; passa para o proximo byte
    ADD   R2, 1                             ; passa para o proximo valor de pintura do byte
    CMP   R0, R1                            ; ver se ja chegou ao valor RAM onde o Pixelscreen acaba
    JNZ   continuar_escreve_ecra_final     ; se ainda nao tiver acabado o Pixelscreen todo continua a pintar

    POP   R3
    POP   R2
    POP   R1
    POP   R0

    RET                                     ; retorna a onde estava (lugar do call) 

;**********************************************************************************************************************
;*---------------------------------------------  INICIAR OS DISPLAYS  ------------------------------------------------*
;**********************************************************************************************************************
iniciar_displays:                               ; mete os displays a 00
    PUSH R0
    PUSH R1

    MOV  R0, DISPLAYS
    MOV  R1, 0000H
    MOVB[R0],R1

    POP  R1
    POP  R0
    RET

;**********************************************************************************************************************
;*---------------------------------------------  NÃO VIRAR O VOLANTE  ------------------------------------------------*
;**********************************************************************************************************************
virar_normal:                                   ; não há direção de virar
    PUSH  R0
    PUSH  R1

    CALL  pinta_volante_norm                    ; pinta o volante normal
    MOV   R0, direcao_nave                      ; dá reset à tabela de direção de nave
    MOV   R1, 0
    MOV  [R0],R1

    POP   R1
    POP   R0
    RET
    
;**********************************************************************************************************************
;*-------------------------------------  PINTAR VOLANTE NA POSICAO NORMAL  -------------------------------------------*
;**********************************************************************************************************************
pinta_volante_norm:                         ; pintar o volante na posicao normal 
    PUSH  R0                                
    PUSH  R1
    PUSH  R2
    PUSH  R3
    PUSH  R4
    PUSH  R5

    MOV   R2, volante_norm
    MOV   R5, volante_atual
    MOV   R5,[R5]
    CMP   R2, R5
    JZ    sai_pinta_volante_norm          

    MOV   R3, estado_pinta_limpa            ; define na flag que é para apagar ou para pintar (0 - apagar)
    MOV   R4, 0
    MOV  [R3],R4

    MOV   R5, volante_atual                 ; guarda o volante atual
    MOV   R2,[R5]
    MOV   R0, 29                            ; vai começar a pintar o objeto na linha 29
    MOV   R1, 14                            ; vai começar a pintar o objeto na coluna 14

    CALL  pinta_objeto

    MOV   R2, volante_norm                  ; vai ver o sitio onde está as linhas a pintar
 
    MOV   R5, volante_atual
    MOV  [R5], R2

    MOV   R3, estado_pinta_limpa            ; define na flag que é para apagar ou para pintar (1 - limpar)
    MOV   R4, 1
    MOV  [R3],R4

    CALL  pinta_objeto                      ; chama a rotina de pintar um objeto

sai_pinta_volante_norm:
    POP   R5
    POP   R4
    POP   R3
    POP   R2
    POP   R1
    POP   R0
    RET                                     ; retorna a onde estava (lugar do call) 

;**********************************************************************************************************************
;*--------------------------------------------  VIRAR PARA A DIREITA  ------------------------------------------------*
;**********************************************************************************************************************
virar_direita:                                   ; direção para a direita
    PUSH  R0
    PUSH  R1
    PUSH  R4
    PUSH  R5

    MOV   R4, estado_tecla_pausa
    MOV   R5, [R4]                         ; valor da variável que diz se o jogo está em pausa ou não
    CMP   R5, 1                            ; se estiver em 1 o jogo está em pausa e então não pinta asteroide
    JZ    sai_virar_direita                ; sai do pinta asteroide

    CALL  pinta_volante_drt
    MOV   R0, direcao_nave                  ; adiciona à tabela de direção para depois somar na deslocação do asteroide
    MOV   R1,[R0]
    CMP   R1, 0
    JZ    sub_direcao_nave
    JMP   sai_virar_direita

sub_direcao_nave:
    SUB   R1, 2
    MOV  [R0],R1

sai_virar_direita:
    POP R5
    POP R4
    POP R1
    POP R0
    RET

;**********************************************************************************************************************
;*-------------------------------------  PINTAR VOLANTE A VIRAR PARA A DIREITA  --------------------------------------*
;**********************************************************************************************************************
pinta_volante_drt:                          ; pintar o volante na posicao de virar a direita
    PUSH  R0                                ; armazena todos os registos para nao haver perda de informacao
    PUSH  R1
    PUSH  R2
    PUSH  R3
    PUSH  R4
    PUSH  R5

    MOV   R2, volante_drt
    MOV   R5, volante_atual
    MOV   R5,[R5]
    CMP   R2, R5
    JZ    sai_pinta_volante_drt         

    MOV   R3, estado_pinta_limpa
    MOV   R4, 0
    MOV  [R3],R4

    MOV   R5, volante_atual
    MOV   R2,[R5]
    MOV   R0, 29                            ; vai começar a pintar o objeto na linha 29
    MOV   R1, 14                            ; vai começar a pintar o objeto na coluna 14

    CALL  pinta_objeto

    MOV   R2, volante_drt                  ; vai ver o sitio onde está as linhas a pintar
 
    MOV   R5, volante_atual
    MOV  [R5], R2

    MOV   R3, estado_pinta_limpa
    MOV   R4, 1
    MOV  [R3],R4

    CALL  pinta_objeto                      ; chama a rotina de pintar um objeto

sai_pinta_volante_drt:
    POP   R5
    POP   R4
    POP   R3
    POP   R2
    POP   R1
    POP   R0
    RET                                     ; retorna a onde estava (lugar do call) 

;**********************************************************************************************************************
;*--------------------------------------------  VIRAR PARA A ESQUERDA  ------------------------------------------------*
;**********************************************************************************************************************
virar_esquerda:                         ; direção para a esquerda
    PUSH  R0
    PUSH  R1
    PUSH  R4
    PUSH  R5

    MOV   R4, estado_tecla_pausa
    MOV   R5, [R4]                         ; valor da variável que diz se o jogo está em pausa ou não
    CMP   R5, 1                            ; se estiver em 1 o jogo está em pausa e então não pinta asteroide
    JZ    sai_virar_esquerda               ; sai do pinta asteroide

    CALL  pinta_volante_esq
    MOV   R0, direcao_nave                  ; adiciona à tabela de direção para depois somar na deslocação do asteroide
    MOV   R1,[R0]
    MOV   R1,0
    JZ    add_direcao_nave

add_direcao_nave:
    ADD   R1, 2
    MOV  [R0],R1

sai_virar_esquerda:
    POP R5
    POP R4
    POP R1
    POP R0
    RET

;**********************************************************************************************************************
;*-------------------------------------  PINTAR VOLANTE A VIRAR PARA A ESQUERDA  -------------------------------------*
;**********************************************************************************************************************
pinta_volante_esq:                          ; pintar o volante na posicao de virar a esquerda
    PUSH  R0                                ; armazena todos os registos para nao haver perda de informacao
    PUSH  R1
    PUSH  R2
    PUSH  R3
    PUSH  R4
    PUSH  R5

    MOV   R2, volante_esq
    MOV   R5, volante_atual
    MOV   R5,[R5]
    CMP   R2, R5
    JZ    sai_pinta_volante_esq         

    MOV   R3, estado_pinta_limpa
    MOV   R4, 0
    MOV  [R3],R4

    MOV   R5, volante_atual
    MOV   R2,[R5]
    MOV   R0, 29                            ; vai começar a pintar o objeto na linha 29
    MOV   R1, 14                            ; vai começar a pintar o objeto na coluna 14

    CALL  pinta_objeto

    MOV   R2, volante_esq                  ; vai ver o sitio onde está as linhas a pintar
 
    MOV   R5, volante_atual
    MOV  [R5], R2

    MOV   R3, estado_pinta_limpa
    MOV   R4, 1
    MOV  [R3],R4

    CALL  pinta_objeto                      ; chama a rotina de pintar um objeto

sai_pinta_volante_esq:
    POP   R5
    POP   R4
    POP   R3
    POP   R2
    POP   R1
    POP   R0
    RET                                     ; retorna a onde estava (lugar do call) 

;**********************************************************************************************************************
;*------------------------------------------------  PINTAR UM OBJETO  ------------------------------------------------*
;**********************************************************************************************************************
pinta_objeto:                               ; rotina que pinta qualquer objeto                              
    PUSH  R2
    PUSH  R3
    PUSH  R4
    PUSH  R5
    PUSH  R6
    PUSH  R7
    PUSH  R8
    PUSH  R9
    PUSH  R10

    MOVB  R3, [R2]                          ; escreve em R3 a quantidade de linhas a pintar
    ADD   R2, 1                             ; vai ver o sitio onde está as colunas a pintar
    MOVB  R4, [R2]                          ; escreve em R4 a quantidade de colunas a pintar
    MOV   R6, 0                             ; mete o contador de linhas inicialmente a 0

pinta_linha:                                ; pinta linha a linha
    MOV   R7, 0                             ; mete o contador de colunas inicialmente a 0
    MOV   R9, R0                            ; mete a coluna inicial onde começa a pintar
    ADD   R9, R6                            ; soma o contador de linhas à linha inicial para saber que coluna pintar
    JMP   pinta_coluna                      ; vai para o pinta_coluna

continua_pinta_linha:
    ADD   R6, 1                             ; incrementa o contador de linhas por 1 
    CMP   R6, R3                            ; ve se ele já percorreu o pinta_linha o nr de vezes definido anteriormente
    JZ    acabou_pintar                     ; se já percorreu vai para o final da rotina
    JMP   pinta_linha                       ; repete o ciclo

pinta_coluna:                               ; dentro da linha em questao, pinta coluna a coluna
    CMP   R7, R4                            ; ve se ele já percorreu o pinta_coluna o nr de vezes definido anteriormente
    JZ    continua_pinta_linha              ; se já percorreu vai para o proximo pinta_linha
    MOV   R8, R1                            ; mete a coluna inicial onde começa a pintar
    ADD   R8, R7                            ; soma o contador de colunas à coluna inicial para saber que coluna pintar
    ADD   R2, 1                             ; passa para a próxima string
    MOVB  R5, [R2]                          ; vê o que está nessa string

    ADD   R7, 1                             ; incrementa o contador de colunas por 1
    CMP   R5, 1            
    JNZ   pinta_coluna    

    MOV   R10, estado_pinta_limpa           ; vê se é para limpar ou pintar
    MOV   R10,[R10]                         ; vê a word que lá está (0 ou 1)
    CMP   R10, 1                            ; se for 1 ele pinta
    JZ    continua_pinta_coluna             ; continua a pintar a coluna

    AND   R5, R10                           ; sendo 0, vai colocar os 1's a 0's
    JMP   continua_pinta_coluna             ; continua a pintar a coluna

continua_pinta_coluna:
    CALL  pintar_pixel                      ; rotina que pinta / limpa 1 pixel
    JMP   pinta_coluna                      ; volta para o pinta_coluna

acabou_pintar:
    POP   R10                                ; recupera todos os registos que foram armazenados
    POP   R9
    POP   R8
    POP   R7
    POP   R6
    POP   R5
    POP   R4
    POP   R3
    POP   R2
    RET                                     ; retorna a onde estava (lugar do call)  

;**********************************************************************************************************************
;*--------------------------------------------  PINTAR OU LIMPAR PIXEL------------------------------------------------*
;**********************************************************************************************************************
pintar_pixel:                               ; rotina que pinta / limpa 1 pixel
    PUSH  R0                                ; armazena todos os registos para nao haver perda de informacao
    PUSH  R1
    PUSH  R2
    PUSH  R3
    PUSH  R5
    PUSH  R6
    PUSH  R7
    PUSH  R8
    PUSH  R9
    PUSH  R10

    MOV   R10,  PIXELSCREEN                 ; R0 = valor RAM de onde o Pixelscreen começa
    MOV   R6,   R9                          ; linha onde vai começar a pintar (definida no pintar do objeto em questão)
    MOV   R2,   R8                          ; coluna onde vai começar a pintar (definida no pintar do objeto em questão)

    MOV   R0,   32
    CMP   R2,   R0
    JGE   continua_pintar_pixel

    CMP   R2,   0
    JLT   continua_pintar_pixel  

    MOV   R3,   R2                          ; guarda o valor da coluna num auxiliar                         \
    SHR   R3,   3                           ; divisão inteira do valor da coluna por 8                      |    
    SHL   R6,   2                           ; multiplicaçao do valor da linha por 4                         |> (8000 + (4 * Linha + Coluna // 8)) = valor RAM a pintar
    ADD   R6,   R3                          ; soma os dois valores                                          | 
    ADD   R6,   R10                         ; soma os dois valores ao valor RAM onde o Pixelscreen começa   /
                
    MOV   R1,   mascaras                    ; valor de inicio das mascaras

    MOV   R7,   8                           ; R7 = 8                                                        \ 
    MOD   R2,   R7                          ; resto da divisão inteira do valor da coluna por 8             |> (mascaras + (coluna % 8))
    ADD   R1,   R2                          ; soma os dois valores para saber qual mascara utilizar         / 
    
    MOVB  R8,  [R6]                         ; guarda o que ja estava pintado
    MOVB  R9,  [R1]                         ; coloca em auxiliar a mascara a pintar
    CMP   R5,   1                           ; compara o estado do pixel a pintar com "1"
    JZ    pinta_1_pixel                     ; se for 1 vai pintar o pixel em questao
    JNZ   limpa_1_pixel                     ; se for 0 vai limpar o pixel em questao

pinta_1_pixel:
    OR    R8,   R9                          ; junta a mascara a pintar com o que ja estava pintado
    MOVB [R6],  R8                          ; pinta no byte de memória escolhido
    JMP  continua_pintar_pixel

limpa_1_pixel:
    NOT   R9                                ; inverte a mascara
    AND   R8,   R9                          ; junta a mascara invertida a "pintar" com o que ja estava pintado
    MOVB [R6],  R8                          ; pinta no byte de memória escolhido
    JMP  continua_pintar_pixel

continua_pintar_pixel:
    POP   R10                               ; recupera todos os registos que foram armazenados
    POP   R9
    POP   R8
    POP   R7
    POP   R6
    POP   R5
    POP   R3
    POP   R2
    POP   R1
    POP   R0
    RET                                     ; retorna a onde estava (lugar do call)


;**********************************************************************************************************************
;*----------------------------------------------  MOVIMENTA ASTERÓIDES  ----------------------------------------------*
;**********************************************************************************************************************
movimenta_asteroide:
    PUSH  R0
    PUSH  R1
    PUSH  R2
    PUSH  R4

    MOV   R4, evento_int
    MOV   R2, [R4]                         ; valor da variável que diz se houve uma interrupção para a linha de comandos do asteroide
    CMP   R2, 0
    JZ    sai_movimenta_asteroide          ; se não houve interrupção, vai-se embora

    MOV   R2, 0

    CALL  gerador_random

    MOV  [R4], R2                          ; coloca o valor da variável que diz se houve uma interrupção a zero (consome evento)

    MOV   R0, asteroides
    SUB   R0, 2
    JMP   inicio_movimenta_asteroide

inicio_movimenta_asteroide:     ; permite fazer inumeras iterações até encontrar um 0 numa word
    ADD   R0, 2
    MOV   R2, [R0]
    MOV   R1, 0
    CALL  gerador_random
    CMP   R2, R1
    JZ    sai_movimenta_asteroide

    MOV   R1, asteroide_a_pintar        
    MOV  [R1],R2

    CALL  pinta_asteroide

    JMP   inicio_movimenta_asteroide

sai_movimenta_asteroide:
    POP   R4
    POP   R2
    POP   R1
    POP   R0
    RET


;**********************************************************************************************************************
;*------------------------------------------------  PINTAR ASTERÓIDES  -----------------------------------------------*
;**********************************************************************************************************************
pinta_asteroide:
    PUSH  R0
    PUSH  R1
    PUSH  R2
    PUSH  R3
    PUSH  R4
    PUSH  R5
    PUSH  R6
    PUSH  R7
    PUSH  R8
    PUSH  R9
    PUSH  R10

    MOV   R4, estado_tecla_pausa
    MOV   R2, [R4]                         ; valor da variável que diz se o jogo está em pausa ou não
    CMP   R2, 1                            ; se estiver em 1 o jogo está em pausa e então não pinta asteroide
    JZ    sai_pinta_asteroide              ; sai do pinta asteroide

    MOV R3, asteroide_a_pintar
    MOV R3, [R3]                            ; asteroide_ativo_1

    MOV R4, 4
    ADD R3, R4                              ; Fica a apontar para as linhas
    MOV R0, [R3]                            ; Exemplo: Fica a 0

    ADD R3, 2                               ; Fica a apontar para as colunas
    MOV R1, [R3]                            ; Exemplo: Fica a D

    ADD R3, 2                               ; Fica a apontar para a forma
    MOV R2, [R3]                            ; Exemplo: Fica 31BA

    MOV R4, estado_pinta_limpa               ; apagar o asteroide anteriro
    MOV R5, 0
    MOV [R4], R5
    CALL pinta_objeto

    MOV R3, asteroide_a_pintar              ; atualizar as coordenadas do asteroide
    MOV R3, [R3]    
    CALL atualizar_coordenadas   

    MOV R4, estado_pinta_limpa              ; pintar o asteroide no sitio novo
    MOV R5, 1
    MOV [R4], R5
    CALL pinta_objeto

    MOV R5, 22
    CMP R0, R5
    JNZ sai_pinta_asteroide
    
    CALL ver_colisao                    ; caso esteja a pintar na linha 22 vai verificar as colisões

sai_pinta_asteroide:
    POP  R10
    POP  R9
    POP  R8
    POP  R7
    POP  R6
    POP  R5
    POP  R4
    POP  R3
    POP  R2
    POP  R1
    POP  R0
    RET                                     ; retorna a onde estava (lugar do call)

;**********************************************************************************************************************
;*----------------------------------------------  SOMAR 3 NOS DISPLAYS  ----------------------------------------------*
;**********************************************************************************************************************
somar_3_inicio:                         ; soma 3 aos displays
    PUSH R0
    PUSH R1
    PUSH R2
    PUSH R3
    PUSH R4
    PUSH R5
    PUSH R6
    PUSH R7

    MOV  R4, 000AH
    MOV  R1, DISPLAYS
    MOV  R5, PONTUACAO_FINAL

    MOV  R6, soma_tab                   ; tabela em memoria onde a pontuação fica guardada
    MOV  R7,[R6]
    CMP  R7, 0
    JNZ  somar_3
    MOV  R0, 3
    MOVB[R1],R0
    MOV [R6],R0
    JMP sai_somar_3

somar_3:
    MOV  R0, [R6]
    ADD  R0, 0003H                          ; soma 3 ao valor da pontuação
    MOV  R2, 0000H                          ; garantir que o auxiliar que vai ser usado está a 0
    JMP  hexa_to_dec                        ; vai transformar o valor de hexadecimal para decimal

hexa_to_dec: 
    MOV  R3, R0                             ; guardar o valor hexadecimal da pontuação
    MOV  R2, R0                             ; meter o valor da pontuação no auxiliar
    MOD  R2, R4                             ; calcular o valor das unidades do valor de pontuação
    DIV  R0, R4                             ; calcular o valor das dezenas do valor de pontuação
    SHL  R0, 4                              ; colocar o valor das dezenas no lugar das dezenas
    OR   R0, R2                             ; juntar ao valor das dezenas o valor das unidades obtendo o valor da pontuação pretendido
    MOVB[R1],R0                             ; colocar no display o valor
    MOV [R6], R3                            ; voltar a colocar o valor da pontuação em hexadecimal
    JMP  sai_somar_3                        ; sai do somar 3

sai_somar_3:
    POP  R7
    POP  R6
    POP  R5
    POP  R4
    POP  R3
    POP  R2
    POP  R1
    POP  R0
    RET

;**********************************************************************************************************************
;*-------------------------------------------  GERADOR DO TIPO E DIREÇÃO  --------------------------------------------*
;**********************************************************************************************************************
gerador_random:
     PUSH R0
     PUSH R1
     PUSH R2
     PUSH R3
     PUSH R4
     PUSH R5 

     MOV  R1, num_random           ; R1 = endereço do valor aleatório
     MOV  R2, tab_gerador          ; R2 = Endereço da variável do tipo de asteróide

verificar_tipo_asteroide:
     MOV  R0, [R1]                 ; ler o número aleatório
     MOV  R4, 4                    ; R4 = divisor (4)
     MOD  R0, R4                   ; resto da divisão inteira por 4
     JZ   asteroide_bom            ; se o resto for 0, vai 2 na variável do tipo de asteroide
     JMP  asteroide_mau

asteroide_mau:
     MOV  R5, 0                    ; registar 0 na variável do tipo de asteróide
     MOV  [R2], R5                 ; 0 --> asteróide mau
     JMP  verificar_direcao

asteroide_bom:
     MOV  R5, 2                    ; registar 2 na variável do tipo de asteróide
     MOV  [R2], R5                 ; 2 --> asteróide bom
     JMP  verificar_direcao

verificar_direcao:
     ADD  R2, 2                    ; passar para o endereço da variável de direção
     MOV  R4, 3                    ; R4 = divisor (3)
     MOV  R0, [R1]                 ; recuperar o valor aleatório
     MOD  R0, R4                   ; resto da divisão inteira por 3
     SUB  R0, 1                    ; subtrair por 1 para ter um valor entre -1 e 1 
     MOV  [R2], R0                 ; alterar variável da direção
     MOV  R3, [R1]                 ; adicionar 1
     ADD  R3, 1                    ; ao número aleatório 
     MOV  [R1], R3                 ; e guardá-lo na memória

     POP  R5
     POP  R4
     POP  R3
     POP  R2
     POP  R1
     POP  R0
     RET


;**********************************************************************************************************************
;*--------------------------------------------  ATUALIZAR AS COORDENADAS  --------------------------------------------*
;**********************************************************************************************************************
;   Recebe em R3 a Estrutura
;   R0 - As linhas; R1 - As colunas; R2 - a Forma 

atualizar_coordenadas:
    PUSH R3
    PUSH R4
    PUSH R5
    PUSH R6
    PUSH R7
    PUSH R8
    PUSH R9

    ADD R0, 1                       ; desce uma linha
    PUSH R0                         ; guarda a linha
    MOV R4, tipo_asteroide_tab
    MOV R5, [R3]                    ; estrutura do asteroide
    ADD R4, R5                      ; R4 a apontar para o tipo asteroide : asteroide_bom_tab
    MOV R5, [R4]                    ; R5 tem asteroid_bom_tab           

    MOV R6, 13              
    CMP R0, R6                      ; ver se ultrapassou a linha 12
    JGE nao_atualiza_forma_apenas_coordenadas   ; se for maior ou igual apenas atualiza as coordenadas
    MOV R4, 3                       ; mete em auxiliar o 3 para realizar cálculos
    DIV R0, R4                      ; saber qual o tamanho do asteroide (0,1,2,3,4)
    SHL R0, 1                       ; multiplica por 2 para depois somar ao endereço para saber a forma
    ADD R5, R0                      
    MOV R0, [R5]                    ; forma do asteroide
    MOV R4, 8                       ; soma 4 para depois
    MOV [R3+R4], R0                 ; guardar a foma na estrutura
    MOV R2, R0                      ; forma do asteroide

nao_atualiza_forma_apenas_coordenadas:
    POP R0
    MOV R7,direcao_nave
    MOV R7,[R7]                     ; direçao da nave
    MOV R4, [R3+2]                  ; direçao do asteroide
    ADD R1, R4                      ; somar ambas as direções ao movimento do asteroide
    ADD R1, R7                      ; continua a somar as direções
    MOV [R3+4], R0                  ; guardar na estrutura a linha do asteroide
    MOV [R3+6], R1                  ; guardar na estrutura a coluna do asteroide

    POP R9
    POP R8
    POP R7
    POP R6
    POP R5
    POP R4
    POP R3
    RET

;**********************************************************************************************************************
;*-------------------------------------------------  VERIFICA COLISÃO  -----------------------------------------------*
;**********************************************************************************************************************
;   Recebe em R3 a Estrutura
;   R0 - As linhas; R1 - As colunas; R2 - a Forma 
ver_colisao:
    PUSH R0
    PUSH R1
    PUSH R2
    PUSH R3
    PUSH R4
    PUSH R5
    PUSH R6
    PUSH R7
    PUSH R8

    MOV   R4,   32                          ; vê os limites em que o asteroide pode estar a ser pintado
    CMP   R1,   R4
    JGE   reset_linha_asteroide

    CMP   R1,   0
    JLT   reset_linha_asteroide   

    MOV   R5, [R3]
    CMP   R5, 0
    JNZ   vai_somar_3                       ; ve for colisão com asteroide bom vai somar
    JMP   perder_jogo                       ; se for colisão com asteroide mau perde o jogo

vai_somar_3:
    CALL somar_3_inicio                     ; vai somar 3
    JMP  reset_linha_asteroide              ; reset da linha do asteroide

perder_jogo:                                ; perde o jogo
    CALL termina_jogo
    JMP  reset_linha_asteroide              ; reset da linha do asteroide

reset_linha_asteroide:
    MOV   R4, estado_pinta_limpa            ; é para pintar ou para limpar
    MOV   R5, 0                             ; mete a 0
    MOV  [R4],R5                            ; muda o estado para 0
    CALL  pinta_objeto                      ; vai limpar o objeto

    MOV   R7, asteroide_a_pintar            ; endereço do tipo do asteroide
    MOV   R7,[R7]                           ;
    MOV   R8, tab_gerador                   ; endereço do tipo do asteroide que foi criado pelo gerador
    MOV   R8, [R8]                          ; a word do tipo do asteroide que foi criado pelo gerador (0 ou 2)
    MOV  [R7], R8                           ; atualiza o tipo do asteroide
    
    CALL  gerador_random

    ADD   R7, 2                             ; endereço da direção do asteroide    
    MOV   R8, tab_gerador                   ; endereço da direção do asteroide que foi criado pelo gerador
    MOV   R8, [R8+2]                        ; a word da direção do asteroide que foi criado pelo gerador (-1, 0 ou 1)
    MOV  [R7], R8                           ; atualiza a direção do asteroide

    MOV   R0, 0                             ; coluna nova a pintar
    MOV   R1, 13                            ; linha nova a pintar
    MOV  [R7+2],R0                            ; guardar a linha
    MOV  [R7+4],R1                          ; guardar a coluna
    MOV   R6,asteroide_1                    ; reset ao asteroide anterior 
    MOV  [R7+6],R6                          ; vai meter o "asteroide anterior" para ser apagado como se fosse o inicial

    POP R8
    POP R7
    POP R6
    POP R5
    POP R4
    POP R3
    POP R2
    POP R1
    POP R0
    RET

;**********************************************************************************************************************
;*----------------------------------------------  VERIFICAR PONTUAÇÃO  -----------------------------------------------*
;**********************************************************************************************************************
verificar_pontuacao:                            ; vai ver se já chegou ao maximo de pontuação
    PUSH R10
    PUSH R9

    MOV   R10, soma_tab
    MOV   R10,[R10]
    MOV   R9, 99
    CMP   R10, R9
    JZ    soma_max
    JMP   sai_verificar_pontuacao

soma_max:
    MOV   R9, estado_tecla_terminar                 ; se tiver chegado à pontuação máxima ativa a flag de fim de jogo
    MOV   R10, 1
    MOV  [R9],R10
    JMP   sai_verificar_pontuacao

sai_verificar_pontuacao:
    POP R9
    POP R10
    RET

;**********************************************************************************************************************
;*--------------------------------------------  DISPARAR MÍSSIL  -----------------------------------------------------*
;**********************************************************************************************************************
disparar_missil:
    PUSH R0
    PUSH R1
    PUSH R2
    PUSH R3
    PUSH R4
    PUSH R5
    PUSH R6
    PUSH R7
    PUSH R8

    MOV   R4, estado_tecla_pausa
    MOV   R2, [R4]                         ; valor da variável que diz se o jogo está em pausa ou não
    CMP   R2, 1                            ; se estiver em 1 o jogo está em pausa e então não pinta asteroide
    JZ    sai_disparar_missil             ; sai do pinta asteroide

    MOV   R4, evento_int
    MOV   R2, [R4+2]                         ; valor da variável que diz se houve uma interrupção para a linha de comandos do asteroide_mau
    CMP   R2, 0
    JZ    sai_disparar_missil                ; se não houve interrupção, vai-se embora
    MOV   R2, 0
    MOV  [R4+2], R2                          ; coloca o valor da variável que diz se houve uma interrupção a zero (consome evento)
    
    MOV R6, estado_missil                   ; tem de ver se o missil ainda está ativo pq caso esteja não pode lançar outro
    MOV R8,[R6]
    MOV R7, 1
    CMP R8,R7
    JZ missil_ativo
    JMP sai_disparar_missil


missil_ativo:
    MOV R4, tab_missil                          ; tira informação da estrutura do missil
    MOV R0, [R4]                             ; linha missil
    MOV R1, [R4+2]                           ; coluna missil
    MOV R2, missil

    MOV R3, estado_pinta_limpa
    MOV R5,0
    MOV[R3],R5

    CALL pinta_objeto

    SUB R0,1
    MOV R9, 11
    CMP R9, R0
    JZ  desativar_missil                    ; se já estiver for a pintar na linha 11 desativa o missil 
    JMP continua_disparar_missil

desativar_missil:
    MOV R6, estado_missil                   ; coloca o estado do missil a 0
    MOV R7, 0
    MOV[R6],R7
    JMP sai_disparar_missil

continua_disparar_missil:   
    MOV R5, direcao_nave                    ; faz a deslocação do missil com a direção da nava
    MOV R5,[R5]
    ADD R1, R5

    MOV[R4],R0                              ; atualizar os valor das coordenadas do missil
    MOV[R4+2],R1

    MOV R3, estado_pinta_limpa
    MOV R5,1
    MOV[R3],R5

    CALL pinta_objeto

    JMP sai_disparar_missil

sai_disparar_missil:
    POP  R8
    POP  R7
    POP  R6
    POP  R5
    POP  R4
    POP  R3
    POP  R2
    POP  R1
    POP  R0
    RET

;**********************************************************************************************************************
;*----------------------------------------------  ATIVAR MÍSSIL  -----------------------------------------------------*
;**********************************************************************************************************************
ativar_missil:
    PUSH R6
    PUSH R7
    PUSH R8
    PUSH R9
    PUSH R10

    MOV R6, estado_missil                   ; se o estado do missil for 0 mete a 1 ativando o
    MOV R8, [R6]
    MOV R7, 0
    CMP R7, R8
    JZ ativa_missil
    JMP sai_ativar_missil

ativa_missil:
    MOV R8, tab_missil              ; atualiza os valores da estrutura do missil
    MOV  R10, 26
    MOV [R8], R10
    MOV  R10, 16
    MOV [R8+2], R10

    MOV R7, 1
    MOV[R6],R7
    JMP sai_ativar_missil

sai_ativar_missil:
    POP R10
    POP R9
    POP R8
    POP R7
    POP R6
    RET