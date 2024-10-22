% Rafael Candeias, 93748.

:- consult(codigo_comum).
%---------------------------------------------------------------------------------

% R = #N numa lista, X(contador) iniciado sempre a 0.
conta_n(X, _, [], R) :- !, R = X.
conta_n(X, N, [H|T], R) :- N==H, !, X1 is X+1, conta_n(X1, N, T, R).
conta_n(X, N, [H|T], R) :- N\==H, conta_n(X, N, T, R). 


% N = #var numa lista, X(contador) iniciado sempre a 0.
conta_var(X, [], N) :- !, N = X.
conta_var(X, [H|R], N) :- \+var(H), !, conta_var(X, R, N).
conta_var(X, [H|R], N) :- var(H), X1 is X+1, !, conta_var(X1, R, N).


% N = #var numa lista de listas, X(contador) iniciado sempre a 0.
total_var(X, [], N) :- !, N = X.
total_var(X, [H|R], N) :- conta_var(0, H, N1), X1 is X+N1, 
	total_var(X1, R, N). 


% verifica se duas variaveis sao iguais
igual(A, B) :- A==B, !.
igual(A, B) :- var(A), var(B).


% Devolve uma lista com X no lugar das variaveis.
insere(_, [], []) :- !.
insere(X, [H|T], [H|T1]):- \+var(H), !, insere(X, T, T1).
insere(X, [H|T], [X|T1]):- var(H), insere(X, T, T1).


% Aplica R1 e R2 a linha da matriz.
aplica_R1_R2_L([], []) :- !. 
aplica_R1_R2_L([Fila|R], Puz) :- aplica_R1_R2_fila(Fila, N_Fila),
	aplica_R1_R2_L(R, Puz_R),
	Puz = [N_Fila|Puz_R].


% Aplica R1 e R2 as colunas da matriz.
aplica_R1_R2_C([Fila|R], Puz) :- mat_transposta([Fila|R], Puz_I), 
	aplica_R1_R2_L(Puz_I, N_Puz),
	mat_transposta(N_Puz, Puz).


% Aplica a R3 a uma lista tipo puz.
compara(_, _, _, []) :- !.												           % termina quando nao ha mais nada a comparar.
compara(X, N, [H|_], [[I|_]|_]) :- H==I, X==N, !, fail.                            % da false quando descobre que os elementos sao iguais e o contador ja chegou ao limite.
compara(X, N, [H|T], [[I|R]|LR]) :- H==I, X<N, !, X1 is X+1,                       % descobre que os elementos sao iguais, mas o contador de colunas ainda nao terminou,
	compara(X1, N, T, [R|LR]).                                                     % por isso permanece na mesma linha e chama a funcao com a coluna seguinte
compara(_, N, [H|T], [[I|_]|LR]) :- H\==I, !, compara(1, N, [H|T], LR).            % quando descobre que os elementos sao diferentes 


% Aplica aplica_R1_R2_fila na linha L e coluna C de Puz. 
aplica_R1_R2_local((L,C), Puz, N_Puz) :- mat_elementos_coluna(Puz, C, Col),
	aplica_R1_R2_fila(Col, N_Col), mat_muda_coluna(Puz, C, N_Col, Puz_C),
	mat_transposta(Puz_C, Puz_C_I), mat_elementos_coluna(Puz_C_I, L, Line),
	aplica_R1_R2_fila(Line, N_Line), mat_muda_coluna(Puz_C_I, L, N_Line, Puz_CL_I),
	mat_transposta(Puz_CL_I, N_Puz).


% devolve uma lista com todas as posicoes onde Puz1 difere de Puz2,
% Pos inicado como [].
compara_guarda(Lc, Cc, Lim, Puz1, Puz2, Pos, Lista_pos_errada) :- Lc==Lim, Cc==Lim,
	mat_ref(Puz1, (Lc, Cc), P1), mat_ref(Puz2, (Lc, Cc), P2), 
	not(igual(P1, P2)), append(Pos, [(Lc, Cc)], Lista_pos_errada).
compara_guarda(Lc, Cc, Lim, Puz1, Puz2, Pos, Lista_pos_errada) :- Lc==Lim, Cc==Lim,
	mat_ref(Puz1, (Lc, Cc), P1), mat_ref(Puz2, (Lc, Cc), P2), 
	igual(P1, P2), Lista_pos_errada = Pos.
compara_guarda(Lc, Cc, Lim, Puz1, Puz2, Pos, Lista_pos_errada) :- 
	mat_ref(Puz1, (Lc, Cc), P1), mat_ref(Puz2, (Lc, Cc), P2), 
	not(igual(P1, P2)), append(Pos, [(Lc, Cc)], Pos1),
	Cc<Lim, !,Cc1 is Cc+1,
	compara_guarda(Lc, Cc1, Lim, Puz1, Puz2, Pos1, Lista_pos_errada).
compara_guarda(Lc, Cc, Lim, Puz1, Puz2, Pos, Lista_pos_errada) :- 
	mat_ref(Puz1, (Lc, Cc), P1), mat_ref(Puz2, (Lc, Cc), P2), 
	not(igual(P1, P2)), append(Pos, [(Lc, Cc)], Pos1),
	Lc<Lim, !,Lc1 is Lc+1,
	compara_guarda(Lc1, 1, Lim, Puz1, Puz2, Pos1, Lista_pos_errada).
compara_guarda(Lc, Cc, Lim, Puz1, Puz2, Pos, Lista_pos_errada) :- 
	mat_ref(Puz1, (Lc, Cc), P1), 
	mat_ref(Puz2, (Lc, Cc), P2), igual(P1, P2), Cc<Lim, !, Cc1 is Cc+1,
	compara_guarda(Lc, Cc1, Lim, Puz1, Puz2, Pos, Lista_pos_errada).
compara_guarda(Lc, Cc, Lim, Puz1, Puz2, Pos, Lista_pos_errada) :- 
	mat_ref(Puz1, (Lc, Cc), P1), 
	mat_ref(Puz2, (Lc, Cc), P2), igual(P1, P2), Lc<Lim, Lc1 is Lc+1,
	compara_guarda(Lc1, 1, Lim, Puz1, Puz2, Pos, Lista_pos_errada).


start(Lc, Cc, N, Puz, _) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1), 
	total_var(0, Puz1, NV), NV\==0, Lc==N, Cc==N, !, fail.
start(Lc, Cc, _, Puz, N_Puz) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1), 
	total_var(0, Puz1, NV), NV==0, !, N_Puz = Puz1.
start(Lc, Cc, N, Puz, N_Puz) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1),
	total_var(0, Puz1, NV), NV\==0, Cc<N, !, Cc1 is Cc+1,
	start(Lc, Cc1, N, Puz, N_Puz).
start(Lc, Cc, N, Puz, N_Puz) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1),
	total_var(0, Puz1, NV), NV\==0, Lc<N, !, Lc1 is Lc+1,
	start(Lc1, 1, N, Puz, N_Puz).

/*
start(Lc, Cc, N, Puz, _) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1), 
	total_var(0, Puz1, NV), NV\==0, Lc==N, Cc==N, !, fail.
start(Lc, Cc, _, Puz, N_Puz) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1), 
	total_var(0, Puz1, NV), NV==0, 
	verifica_R3(Puz1), !, N_Puz = Puz1.
start(Lc, Cc, _, Puz, N_Puz) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1), 
	total_var(0, Puz1, NV), NV==0, not(verifica_R3(Puz1)), 
	Cc<N, !, Cc1 is Cc+1,
	start(Lc, Cc1, N, Puz, N_Puz).
start(Lc, Cc, _, Puz, N_Puz) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1), 
	total_var(0, Puz1, NV), NV==0, not(verifica_R3(Puz1)), 
	Lc<N, !, Lc1 is Lc+1,
	start(Lc1, 1, N, Puz, N_Puz).
start(Lc, Cc, N, Puz, N_Puz) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1),
	total_var(0, Puz1, NV), NV\==0, Cc<N, !, Cc1 is Cc+1,
	start(Lc, Cc1, N, Puz, N_Puz).
start(Lc, Cc, N, Puz, N_Puz) :- propaga_posicoes([(Lc, Cc)], Puz, Puz1),
	total_var(0, Puz1, NV), NV\==0, Lc<N, !, Lc1 is Lc+1,
	start(Lc1, 1, N, Puz, N_Puz).*/
%---------------------------------------------------------------------------------

aplica_R1_triplo([A, B, C], _) :- A==0, B==0, C==0, !, fail.
aplica_R1_triplo([A, B, C], _) :- A==1, B==1, C==1, !, fail.
aplica_R1_triplo([A, _, C], R) :- A==0, C==0, !, R = [0, 1, 0].
aplica_R1_triplo([A, _, C], R) :- A==1, C==1, !, R = [1, 0, 1].
aplica_R1_triplo([A, B, _], R) :- A==0, B==0, !, R = [0, 0, 1].
aplica_R1_triplo([A, B, _], R) :- A==1, B==1, !, R = [1, 1, 0].
aplica_R1_triplo([_, B, C], R) :- B==0, C==0, !, R = [1, 0, 0].
aplica_R1_triplo([_, B, C], R) :- B==1, C==1, !, R = [0, 1, 1].
aplica_R1_triplo([A, B, C], R) :- B==1, C==0, !, R = [A, 1, 0].
aplica_R1_triplo([A, B, C], R) :- B==0, C==1, !, R = [A, 0, 1].
aplica_R1_triplo([A, B, C], R) :- A==0, B==1, !, R = [0, 1, C].
aplica_R1_triplo([A, B, C], R) :- A==1, B==0, !, R = [1, 0, C].
aplica_R1_triplo([A, B, C], R) :- A==1, C==0, !, R = [1, B, 0].
aplica_R1_triplo([A, B, C], R) :- A==0, C==1, !, R = [0, B, 1].
aplica_R1_triplo([A, B, C], R) :- C==0, !, R = [A, B, 0].
aplica_R1_triplo([A, B, C], R) :- C==1, !, R = [A, B, 1].
aplica_R1_triplo([A, B, C], R) :- B==0, !, R = [A, 0, C].
aplica_R1_triplo([A, B, C], R) :- B==1, !, R = [A, 1, C].
aplica_R1_triplo([A, B, C], R) :- A==0, !, R = [0, B, C].
aplica_R1_triplo([A, B, C], R) :- A==1, !, R = [1, B, C].
aplica_R1_triplo([A, B, C], R) :- R = [A, B, C].


aplica_R1_fila_aux([A, B, C| R], [A1 | N_Fila]) :- 
	aplica_R1_triplo([A, B, C], [A1, B1, C1]), !, 
	aplica_R1_fila_aux([B1, C1| R], N_Fila).
aplica_R1_fila_aux([A, B], [A, B]).


aplica_R1_fila(Fila, N_Fila) :- 
	aplica_R1_fila_aux(Fila, N_Fila1), 
	conta_var(0, Fila, Cont), 
	conta_var(0, N_Fila1, Cont1),
	Cont==Cont1, !,
	N_Fila = Fila.
aplica_R1_fila(Fila, N_Fila) :- 
	aplica_R1_fila_aux(Fila, N_Fila1), 
	conta_var(0, Fila, Cont), 
	conta_var(0, N_Fila1, Cont1), 
	Cont\==Cont1,
	aplica_R1_fila(N_Fila1, N_Fila).


aplica_R2_fila(Fila, _) :- length(Fila, NE), conta_n(0, 0, Fila, N0), 
	NEM is NE/2,
	N0>NEM, !, fail.
aplica_R2_fila(Fila, _) :- length(Fila, NE), conta_n(0, 1, Fila, N1), 
	NEM is NE/2,
	N1>NEM, !, fail.
aplica_R2_fila(Fila, N_Fila) :- conta_var(0, Fila, NV), NV==0, !, N_Fila = Fila.
aplica_R2_fila(Fila, N_Fila) :- length(Fila, NE), conta_n(0, 0, Fila, N0),
	NEM is NE/2,
	N0==NEM, !,
	insere(1, Fila, N_Fila).
aplica_R2_fila(Fila, N_Fila) :- length(Fila, NE), conta_n(0, 1, Fila, N1),
	NEM is NE/2,
	N1==NEM, !,
	insere(0, Fila, N_Fila).
aplica_R2_fila(Fila, N_Fila) :- length(Fila, NE), conta_n(0, 0, Fila, N0),
	NEM is NE/2,
	N0<NEM, !,
	N_Fila = Fila.
aplica_R2_fila(Fila, N_Fila) :- length(Fila, NE), conta_n(0, 1, Fila, N1),
	NEM is NE/2,
	N1<NEM, !,
	N_Fila = Fila.  


aplica_R1_R2_fila(Fila, N_Fila) :- aplica_R1_fila(Fila, Fila1),  
	aplica_R2_fila(Fila1, Fila12), N_Fila = Fila12.
 

aplica_R1_R2_puzzle(Puz, N_Puz) :- 
	aplica_R1_R2_L(Puz, PuzL),
	aplica_R1_R2_C(PuzL, N_Puz).


inicializa(Puz, N_Puz) :- 
	aplica_R1_R2_puzzle(Puz, Puz1),
	total_var(0, Puz, V), total_var(0, Puz1, V1), V==V1, !, N_Puz = Puz. 
inicializa(Puz, N_Puz) :- 
	aplica_R1_R2_puzzle(Puz, Puz1),
	inicializa(Puz1, N_Puz).


verifica_R3([]).
verifica_R3([H|R]) :- length(H, N), compara(1, N, H, R), mat_transposta([H|R], [H_I|R_I]), 
	compara(1, N, H_I, R_I), mat_transposta([H_I|R_I], [H|R]), verifica_R3(R).


propaga_posicoes([], Puz, N_Puz) :- !, N_Puz = Puz.
propaga_posicoes([(L, C)|Pos], Puz, N_Puz) :- 
	not(aplica_R1_R2_local((L,C), Puz, _)), !,
	propaga_posicoes(Pos, Puz, N_Puz).
propaga_posicoes([(L,C)|Pos], Puz, N_Puz) :- aplica_R1_R2_local((L,C), Puz, Puz1),
	length(Puz, N),
	compara_guarda(1, 1, N, Puz, Puz1, [], Lista_pos_errada), 
	Lista_pos_errada = [], !, 
	propaga_posicoes(Pos, Puz1, N_Puz).
propaga_posicoes([(L,C)|Pos], Puz, N_Puz) :- aplica_R1_R2_local((L,C), Puz, Puz1),
	length(Puz, N),
	compara_guarda(1, 1, N, Puz, Puz1, [], Lista_pos_errada), 
	append(Lista_pos_errada, Pos, Tries),
	propaga_posicoes(Tries, Puz1, N_Puz). 


resolve(Puz, Solucao) :- length(Puz, N), start(1, 1, N, Puz, Puz1), 
	Solucao = Puz1.
