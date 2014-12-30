:-use_module(library(random)).
:-use_module(library(sockets)).

port(60070).
% consult('/Users/ricardo/Documents/laig/LAIG/almostfinale.pl').
% launch me in sockets mode
server:-
	port(Port),
	socket_server_open(Port, Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('Accepted connection'), nl,
	serverLoop(Stream),
	socket_server_close(Socket).

% wait for commands
serverLoop(Stream) :-
	repeat,
	read(Stream, ClientMsg),
	write('Received: '), write(ClientMsg), nl,
	parse_input(ClientMsg, MyReply),
	format(Stream, '~q.~n', [MyReply]),
	write('Wrote: '), write(MyReply), nl,
	flush_output(Stream),
	(ClientMsg == quit; ClientMsg == end_of_file), !.

parse_input(comando(Tabuleiro,Jogador,Jogada,Xinicial,Xfinal,Yinicial,Yfinal,TabuleiroNovo), Answer) :-
	comando(Tabuleiro,Jogador,Jogada,Xinicial,Xfinal,Yinicial,Yfinal,TabuleiroNovo, Answer).

parse_input(comandoPC(Tabuleiro,Points,TabuleiroNovo), Answer) :-
	comandoPC(Tabuleiro, TabuleiroNovo, Points, Answer).

parse_input(verificarPeca(Jogador, Tabuleiro, PosX, PosY, CounterX, CounterY, Lista, PieceMoves), Answer) :-
	verificarPeca(Jogador, Tabuleiro, PosX, PosY, CounterX, CounterY, Lista, PieceMoves, Answer).

	
parse_input(quit, ok-bye) :- !.
		
comando(Tabuleiro,Jogador,Jogada,Xinicial,Xfinal,Yinicial,Yfinal,TabuleiroNovo,Answer) :-
	cicloJogo1vs1(Tabuleiro,Jogador,Jogada,Xinicial,Xfinal,Yinicial,Yfinal,TabuleiroNovo),
	!,
	append([],TabuleiroNovo,Answer).

comandoPC(Tabuleiro,TabuleiroNovo,Points,Answer) :-
	cicloJogo1vsPC(Tabuleiro,TabuleiroNovo, Points),
	!,
	append([],Points,Answer).

verificarPeca(Jogador, Tabuleiro, PosX, PosY, CounterX, CounterY, Lista, PieceMoves, Answer):-
	checkPiece(Jogador,Tabuleiro,PosX,PosY,0,0,[],PieceMoves),
	!,
	append([],PieceMoves,Answer).

showBoard([ROW|REST]):-
write('____________________________________'), write('\n'),
write('| '),
showRow(ROW),
write(' |'), write('\n'),
showBoard(REST).
  
showBoard([]):-
write('____________________________________').
  
showRow([ELEM]):-
ELEM is 99,
write('  ').
 
showRow([ELEM]):-
write(ELEM).
  
showRow([ELEM|REST]):-
ELEM is 99,
write('  ') , write(' | '), showRow(REST).
 
showRow([ELEM|REST]):-
write(ELEM) , write(' | '), showRow(REST).

%Aux funcs

elementAt(X,[X|_],1).
elementAt(X,[_|L],K) :- K > 1, K1 is K - 1, elementAt(X,L,K1).

reverse([],Z,Z).
reverse([H|T],Z,Acc) :- reverse(T,Z,[H|Acc]).

replace([_|T], 0, X, [X|T]).
replace([H|T], I, X, [H|R]):- I > -1, NI is I-1, replace(T, NI, X, R), !.
replace(L, _, _, L).

replace2d(List, IndexX, IndexY, Value, Return) :-
	GetElementY is IndexY+1,
	elementAt(Row, List, GetElementY),
	replace(Row, IndexX, Value, X),
	!,
	replace(List, IndexY, X, Return).

aplica(P,LArgs) :-
	G =.. [P|LArgs], G.

not(X) :- X, !, fail.
not(X).


cicloJogo1vs1(Tabuleiro,Jogador,1,Xinicial,Xfinal,Yinicial,Yfinal,TabuleiroNovo):-
	aplica(mover,[[Xinicial, Yinicial],[Xfinal,Yfinal], Jogador ,Tabuleiro, TabuleiroNovo]).

cicloJogo1vs1(Tabuleiro,Jogador,2,Xinicial,Xfinal,Yinicial,Yfinal,TabuleiroNovo) :-
	aplica(fusao,[[Xinicial, Yinicial],[Xfinal,Yfinal], Jogador ,Tabuleiro, TabuleiroNovo]).

cicloJogo1vsPC(Tabuleiro,TabuleiroNovo,Points) :-
	listAvailableMoves(2,Tabuleiro,1,1,[],Moves),
	length(Moves,MovesLength),
	random(0,MovesLength,RandomNumber),
	RandomNumberSelect is RandomNumber+1,
	elementAt(Move, Moves,RandomNumberSelect),
	elementAt(InitCoords,Move,1),
	elementAt(FinalCoords,Move,2),
	elementAt(Xinit, InitCoords, 1),
	elementAt(Yinit, InitCoords, 2),
	elementAt(Xfinal, FinalCoords, 1),
	elementAt(Yfinal, FinalCoords, 2),
	!,
	aplica(mover,[[Xinit, Yinit],[Xfinal,Yfinal], 2 ,Tabuleiro, TabuleiroNovo]),
	append([],[Yinit,Xinit,Yfinal,Xfinal],Points).


%start game

startGame :-
	write('Escolha o modo de Jogo: \n'),
	write('1- 1v1\n'),
	write('2- 1vCOM\n'),
	write('3- COMvCOM\n'),
	read(Choice),
	Choice < 4,
	append([], [[99,99,99,99,99,99,99],[99,13,23,13,23,13,99],[99,23,13,99,13,23,99],[99,23,13,23,13,23,99],[99,99,99,99,99,99,99]] , Tabuleiro),
		showBoard(Tabuleiro),
	nl,
	!,
	gameCycle(Tabuleiro, 1,Choice, A).


gameCycle(Tabuleiro, 1, 3,TabuleiroNovo) :-
	listAvailableMoves(1,Tabuleiro,1,1,[],Moves),
	length(Moves,MovesLength),
	random(0,MovesLength,RandomNumber),
	RandomNumberSelect is RandomNumber+1,
	elementAt(Move, Moves,RandomNumberSelect),
	elementAt(InitCoords,Move,1),
	elementAt(FinalCoords,Move,2),
	elementAt(Xinit, InitCoords, 1),
	elementAt(Yinit, InitCoords, 2),
	elementAt(Xfinal, FinalCoords, 1),
	elementAt(Yfinal, FinalCoords, 2),
	!,
	write('Computador mexeu da posicao '), write(Xinit), write(','), write(Yinit), write(' para a posicao '), write(Xfinal),write(',') ,write(Yfinal), nl,
	aplica(mover,[[Xinit, Yinit],[Xfinal,Yfinal], 1 ,Tabuleiro, TabuleiroNovo]),
	aplica(contaPecas,[TabuleiroNovo,1,1,0,Pecas]),
	nl,write('Numero de pecas do Computador: '),
	!,
	write(Pecas), nl,
	not(Pecas is 1),
	!,
	read(X),
	listAvailableMoves(2,Tabuleiro,1,1,[],Moves2),
	length(Moves2,MovesLength2),
	random(0,MovesLength2,RandomNumber2),
	RandomNumberSelect2 is RandomNumber2+1,
	elementAt(Move2, Moves2,RandomNumberSelect2),
	elementAt(InitCoords2,Move2,1),
	elementAt(FinalCoords2,Move2,2),
	elementAt(Xinit2, InitCoords2, 1),
	elementAt(Yinit2, InitCoords2, 2),
	elementAt(Xfinal2, FinalCoords2, 1),
	elementAt(Yfinal2, FinalCoords2, 2),
	!,
	write('Computador mexeu da posicao '), write(Xinit2), write(','), write(Yinit2), write(' para a posicao '), write(Xfinal2),write(',') ,write(Yfinal2), nl,	
	aplica(mover,[[Xinit2, Yinit2],[Xfinal2,Yfinal2], 2 ,TabuleiroNovo, TabuleiroNovoCOM]),
	aplica(contaPecas,[TabuleiroNovoCOM,2,1,0,Pecas2]),
	nl,write('Numero de pecas do Computador: '),
	!,
	write(Pecas2), nl,
	not(Pecas2 is 1),
	read(Y),
	gameCycle(TabuleiroNovoCOM, 1, 3,TabuleiroNovo2), nl.



gameCycle(Tabuleiro, 1, 2,TabuleiroNovo) :-
	write('Jogador 1: \n'),
	write('1- Mover\n'),
	write('2- Fundir\n'),
	write('3- Passar Vez\n'),
	read(Choice),
	Choice > 0,
	Choice < 3,
	write(Choice), nl,
	write('Pos Init X'),
	read(InitX),
	write('Pos Init Y'),
	read(InitY),
	write('Pos Final X'),
	read(FinalX),
	write('Pos Final Y'),
	read(FinalY),
	runChoice(Choice, [InitX, InitY], [FinalX, FinalY], Tabuleiro, 1, TabuleiroNovo),
	nl,
	!,
	aplica(contaPecas,[TabuleiroNovo,1,1,0,Pecas]),
	write('Numero de pecas: '),
	write(Pecas), nl,
	!,
	not(Pecas is 1),
	Choice2 is 2,
	listAvailableMoves(2,Tabuleiro,1,1,[],Moves),
	length(Moves,MovesLength),
	random(0,MovesLength,RandomNumber),
	RandomNumberSelect is RandomNumber+1,
	elementAt(Move, Moves,RandomNumberSelect),
	elementAt(InitCoords,Move,1),
	elementAt(FinalCoords,Move,2),
	elementAt(Xinit, InitCoords, 1),
	elementAt(Yinit, InitCoords, 2),
	elementAt(Xfinal, FinalCoords, 1),
	elementAt(Yfinal, FinalCoords, 2),
	!,
	write('Computador mexeu da posicao '), write(Xinit), write(','), write(Yinit), write(' para a posicao '), write(Xfinal),write(',') ,write(Yfinal), nl,
	aplica(mover,[[Xinit, Yinit],[Xfinal,Yfinal], 2 ,TabuleiroNovo, TabuleiroNovoCOM]),
	aplica(contaPecas,[TabuleiroNovoCOM,2,1,0,Pecas2]),
	nl,write('Numero de pecas do Computador: '),
	!,
	write(Pecas2), nl,
	not(Pecas2 is 1),
	gameCycle(TabuleiroNovoCOM, 1, 2,TabuleiroNovo2), nl.

gameCycle(Tabuleiro, 1, 2,TabuleiroNovo) :-
	showBoard(Tabuleiro),
	write('\nO teu oponente cedeu a sua vez\n'),
	listAvailableMoves(2,Tabuleiro,1,1,[],Moves),
	length(Moves,MovesLength),
	random(0,MovesLength,RandomNumber),
	RandomNumberSelect is RandomNumber+1,
	elementAt(Move, Moves,RandomNumberSelect),
	elementAt(InitCoords,Move,1),
	elementAt(FinalCoords,Move,2),
	elementAt(Xinit, InitCoords, 1),
	elementAt(Yinit, InitCoords, 2),
	elementAt(Xfinal, FinalCoords, 1),
	elementAt(Yfinal, FinalCoords, 2),
	!,
	write('Computador mexeu da posicao '), write(Xinit), write(','), write(Yinit), write(' para a posicao '), write(Xfinal),write(',') ,write(Yfinal), nl,
	aplica(mover,[[Xinit, Yinit],[Xfinal,Yfinal], 2 ,Tabuleiro, TabuleiroNovo]),
	aplica(contaPecas,[TabuleiroNovo,2,1,0,Pecas2]),
	nl,write('Numero de pecas do Computador: '),
	!,
	write(Pecas2), nl,
	not(Pecas2 is 1),
	gameCycle(TabuleiroNovo, 1, 2,TabuleiroNovo2), nl.

gameCycle(Tabuleiro, 1, 1,TabuleiroNovo) :-
	write('\nJogador 1: \n'),
	write('1- Mover\n'),
	write('2- Fundir\n'),
	write('3- Passar Vez\n'),
	read(Choice),
	Choice > 0,
	Choice < 3,
	write(Choice), nl,
	write('Pos Init X'),
	read(InitX),
	write('Pos Init Y'),
	read(InitY),
	write('Pos Final X'),
	read(FinalX),
	write('Pos Final Y'),
	read(FinalY),
	runChoice(Choice, [InitX, InitY], [FinalX, FinalY], Tabuleiro, 1, TabuleiroNovo),
	nl,
	!,
	aplica(contaPecas,[TabuleiroNovo,1,1,0,Pecas]),
	write('Numero de pecas: '),
	write(Pecas), nl,
	!,
	not(Pecas is 1),
	gameCycle(TabuleiroNovo, 2, A).


gameCycle(Tabuleiro, 1, 1,TabuleiroNovo) :-
	showBoard(Tabuleiro),
	write('\nO teu oponente cedeu a sua vez\n'),
	gameCycle(Tabuleiro, 2,1, A).	

gameCycle(Tabuleiro, 2, 1,TabuleiroNovo) :-
	write('Jogador 2: \n'),
	write('1- Mover\n'),
	write('2- Fundir\n'),
	write('3- Passar Vez\n'),
	read(Choice),
	Choice > 0,
	Choice < 3,
	write('Pos Init X'),
	read(InitX),
	write('Pos Init Y'),
	read(InitY),
	write('Pos Final X'),
	read(FinalX),
	write('Pos Final Y'),
	read(FinalY),
	runChoice(Choice, [InitX, InitY], [FinalX, FinalY], Tabuleiro, 2, TabuleiroNovo),
	nl,
	!,
	aplica(contaPecas,[TabuleiroNovo,2,1,0,Pecas]),
	write('Numero de pecas: '),
	write(Pecas), nl,
	!,
	not(Pecas is 1),
	gameCycle(TabuleiroNovo, 1, A).

gameCycle(Tabuleiro, 2, 1,TabuleiroNovo) :-
	showBoard(Tabuleiro),
	write('\nO teu oponente cedeu a sua vez\n'),
	gameCycle(Tabuleiro, 1,1, A).		
	
runChoice(1, [InitX|[InitY|_]], [FinalX|[FinalY|_]], Tabuleiro, 1, TabuleiroNovo) :-
	aplica(mover,[[InitX, InitY],[FinalX,FinalY], 1 ,Tabuleiro, TabuleiroNovo]).

runChoice(2, [InitX|[InitY|_]], [FinalX|[FinalY|_]], Tabuleiro, 1, TabuleiroNovo) :-
	aplica(fusao,[[InitX, InitY],[FinalX,FinalY], 1 ,Tabuleiro, TabuleiroNovo]).
	
runChoice(1, [InitX|[InitY|_]], [FinalX|[FinalY|_]], Tabuleiro, 2, TabuleiroNovo) :-
	aplica(mover,[[InitX, InitY],[FinalX,FinalY], 2 ,Tabuleiro, TabuleiroNovo]).

runChoice(2, [InitX|[InitY|_]], [FinalX|[FinalY|_]], Tabuleiro, 2, TabuleiroNovo) :-
	aplica(fusao,[[InitX, InitY],[FinalX,FinalY], 2 ,Tabuleiro, TabuleiroNovo]).


%game funcs

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xtemp is Xfinal/6,
	(Xtemp is Float0; Xtemp is Float1),
	Yfinal < 5,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaX is 2; DeltaX is 0),
	DeltaY < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	Peca1 > 1,
	PecaFinal1 is NumPeca-1, 
	PecaFinal2 is NumPeca2+1,
	replace2d(TabuleiroActual, Xinit, Yinit, PecaFinal1, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal2, TabuleiroNovo).

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xtemp is Xfinal/6,
	(Xtemp is Float0; Xtemp is Float1),
	Yfinal < 5,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaX is 2; DeltaX is 0),
	DeltaY < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	Peca1 is 1,
	PecaFinal1 is 99,
	PecaFinal2 is NumPeca2+1,
	replace2d(TabuleiroActual, Xinit, Yinit, PecaFinal1, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal2, TabuleiroNovo).

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xtemp is Xfinal/6,
	(Xtemp is Float0; Xtemp is Float1),
	Yfinal < 5,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaX is 2; DeltaX is 0),
	DeltaY < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1 > 1,
	Peca2 is 9,
	PecaFinal1 is NumPeca-1,  
	PecaFinal2 is Jogador*10+1,
	replace2d(TabuleiroActual, Xinit, Yinit, PecaFinal1, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal2, TabuleiroNovo).

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xtemp is Xfinal/6,
	(Xtemp is Float0; Xtemp is Float1),
	Yfinal < 5,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaX is 2; DeltaX is 0),
	DeltaY < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1 is 1,
	Peca2 is 9,
	PecaFinal1 is 99,  
	PecaFinal2 is NumPeca,
	replace2d(TabuleiroActual, Xinit, Yinit, PecaFinal1, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal2, TabuleiroNovo).


mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xfinal < 7,
	Ytemp is Yfinal/4,
	(Ytemp is Float0; Ytemp is Float1),
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaY is 2;DeltaY is 0),
	DeltaX < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	Peca1 > 1,
	PecaFinal1 is NumPeca-1, 
	PecaFinal2 is NumPeca2+1,
	replace2d(TabuleiroActual, Xinit, Yinit, PecaFinal1, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal2, TabuleiroNovo).

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xfinal < 7,
	Ytemp is Yfinal/4,
	(Ytemp is Float0; Ytemp is Float1),
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaY is 2;DeltaY is 0),
	DeltaX < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	Peca1 is 1,
	PecaFinal1 is 99,
	PecaFinal2 is NumPeca2+1,
	replace2d(TabuleiroActual, Xinit, Yinit, PecaFinal1, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal2, TabuleiroNovo).

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xfinal < 7,
	Ytemp is Yfinal/4,
	(Ytemp is Float0; Ytemp is Float1),
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaY is 2;DeltaY is 0),
	DeltaX < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1 > 1,
	Peca2 is 9,
	PecaFinal1 is NumPeca-1,  
	PecaFinal2 is Jogador*10+1,
	replace2d(TabuleiroActual, Xinit, Yinit, PecaFinal1, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal2, TabuleiroNovo).

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xfinal < 7,
	Ytemp is Yfinal/4,
	(Ytemp is Float0; Ytemp is Float1),
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaY is 2;DeltaY is 0),
	DeltaX < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1 is 1,
	Peca2 is 9,
	PecaFinal1 is 99,  
	PecaFinal2 is NumPeca,
	replace2d(TabuleiroActual, Xinit, Yinit, PecaFinal1, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal2, TabuleiroNovo).

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Xfinal > 0, Xfinal < 6,
	Yfinal > 0, Yfinal < 4,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	DeltaY < 2,
	DeltaX < 2,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0),
	elementAt(Rowtemp, TabuleiroActual, Yinit+1),
	elementAt(NumPeca, Rowtemp, Xinit+1),
	replace2d(TabuleiroActual, Xinit, Yinit, 99, Novo),
	replace2d(Novo, Xfinal, Yfinal, NumPeca, TabuleiroNovo).

mover([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	showBoard(TabuleiroActual),
	write('\n Jogada pretendida nao e permitida\n'),
	append(TabuleiroActual,[],TabuleiroNovo).	

fusao([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Xfinal > 0, Xfinal < 6,
	Yfinal > 0, Yfinal < 4,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	DeltaY < 2,
	DeltaX < 2,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0),
	elementAt(Rowtemp, TabuleiroActual, Yinit+1),
	elementAt(NumPeca, Rowtemp, Xinit+1),
	elementAt(Rowtemp2, TabuleiroActual, Yfinal+1),
	elementAt(NumPeca2, Rowtemp2, Xfinal+1),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	PecaFinal is Jogador*10+Peca1+Peca2,
	replace2d(TabuleiroActual, Xinit, Yinit, 99, Novo),
	replace2d(Novo, Xfinal, Yfinal, PecaFinal, TabuleiroNovo).
	
fusao([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, TabuleiroNovo) :-
	showBoard(TabuleiroActual),
	write('\n Jogada pretendida nao e permitida\n'),
	append(TabuleiroActual,[],TabuleiroNovo).

validaPos([X|[Y|_]], Jogador, [], Y) :- fail.

validaPos([X|[Y|_]], Jogador, [ROW|REST], Y) :-
	!,
	validaPosX(X, Jogador, ROW, 0).

validaPos([X|[Y|_]], Jogador, [ROW|REST], Counter) :-
	I is Counter+1, 
	validaPos([X|[Y|_]], Jogador, REST, I).



validaPosX(X, Jogador, [], X) :- fail.

validaPosX(X, Jogador, [ELEM|REST], Counter) :-
	I is Counter+1, 
	validaPosX(X, Jogador, REST, I).

validaPosX(X, Jogador, [ELEM|REST], X) :-
	!,
	Jogador is floor(ELEM/10).



validaPosVazio([X|[Y|_]], [], Y) :- fail.

validaPosVazio([X|[Y|_]], [ROW|REST], Y) :-
	!,
	validaPosVazioX(X, ROW, 0).

validaPosVazio([X|[Y|_]], [ROW|REST], Counter) :-
	I is Counter+1, 
	validaPosVazio([X|[Y|_]], REST, I).


validaPosVazioX(X, [], X) :- fail.

validaPosVazioX(X, [ELEM|REST], Counter) :-
	I is Counter+1, 
	validaPosVazioX(X, REST, I).

validaPosVazioX(X, [ELEM|REST], X) :-
	!,
	99 is ELEM.


validaDiag([Xinit|[Yinit|_]], [Xfinal|[Yfinal|_]], TabuleiroActual) :- 
	DeltaX is Xfinal - Xinit,
	DeltaY is Yfinal - Yinit,
	DeltaX is 0,
	DeltaY < 0,
	DiagY is Yinit+1+DeltaY+1,
	DiagX is Xinit+1,
	elementAt(Rowtemp, TabuleiroActual, DiagY),
	elementAt(Peca, Rowtemp, DiagX),
	not(99 is Peca).

validaDiag([Xinit|[Yinit|_]], [Xfinal|[Yfinal|_]], TabuleiroActual) :- 
	DeltaX is Xfinal - Xinit,
	DeltaY is Yfinal - Yinit,
	DeltaX is 0,
	DeltaY > 0,
	DiagY is Yinit+1+DeltaY-1,
	DiagX is Xinit+1,
	elementAt(Rowtemp, TabuleiroActual, DiagY),
	elementAt(Peca, Rowtemp, DiagX),
	not(99 is Peca).

validaDiag([Xinit|[Yinit|_]], [Xfinal|[Yfinal|_]], TabuleiroActual) :- 
	DeltaX is Xfinal - Xinit,
	DeltaY is Yfinal - Yinit,
	DeltaX < 0,
	DeltaY is 0,
	DiagY is Yinit+1,
	DiagX is Xinit+1+DeltaX+1,
	elementAt(Rowtemp, TabuleiroActual, DiagY),
	elementAt(Peca, Rowtemp, DiagX),
	not(99 is Peca).

validaDiag([Xinit|[Yinit|_]], [Xfinal|[Yfinal|_]], TabuleiroActual) :- 
	DeltaX is Xfinal - Xinit,
	DeltaY is Yfinal - Yinit,
	DeltaX > 0,
	DeltaY is 0,
	DiagY is Yinit+1,
	DiagX is Xinit+1+DeltaX-1,
	elementAt(Rowtemp, TabuleiroActual, DiagY),
	elementAt(Peca, Rowtemp, DiagX),
	not(99 is Peca).

validaDiag([Xinit|[Yinit|_]], [Xfinal|[Yfinal|_]], TabuleiroActual) :- 
	DeltaX is Xfinal - Xinit,
	DeltaY is Yfinal - Yinit,
	DeltaX < 0,
	DeltaY < 0,
	DiagY is Yinit+1+DeltaY+1,
	DiagX is Xinit+1+DeltaX+1,
	elementAt(Rowtemp, TabuleiroActual, DiagY),
	elementAt(Peca, Rowtemp, DiagX),
	not(99 is Peca).

validaDiag([Xinit|[Yinit|_]], [Xfinal|[Yfinal|_]], TabuleiroActual) :- 
	DeltaX is Xfinal - Xinit,
	DeltaY is Yfinal - Yinit,
	DeltaX < 0,
	DeltaY > 0,
	DiagY is Yinit+1+DeltaY-1,
	DiagX is Xinit+1+DeltaX+1,
	elementAt(Rowtemp, TabuleiroActual, DiagY),
	elementAt(Peca, Rowtemp, DiagX),
	not(99 is Peca).

validaDiag([Xinit|[Yinit|_]], [Xfinal|[Yfinal|_]], TabuleiroActual) :- 
	DeltaX is Xfinal - Xinit,
	DeltaY is Yfinal - Yinit,
	DeltaX > 0,
	DeltaY < 0,
	DiagY is Yinit+1+DeltaY+1,
	DiagX is Xinit+1+DeltaX-1,
	elementAt(Rowtemp, TabuleiroActual, DiagY),
	elementAt(Peca, Rowtemp, DiagX),
	not(99 is Peca).

validaDiag([Xinit|[Yinit|_]], [Xfinal|[Yfinal|_]], TabuleiroActual) :- 
	DeltaX is Xfinal - Xinit,
	DeltaY is Yfinal - Yinit,
	DeltaX > 0,
	DeltaY > 0,
	DiagY is Yinit+1+DeltaY-1,
	DiagX is Xinit+1+DeltaX-1,
	elementAt(Rowtemp, TabuleiroActual, DiagY),
	elementAt(Peca, Rowtemp, DiagX),
	not(99 is Peca).


contaPecas(Tabuleiro, Jogador, 4, IncPeca, NumPeca) :- NumPeca is IncPeca.

contaPecas(Tabuleiro, Jogador, Counter, IncPeca, NumPeca) :-
	Yelem is Counter+1,
	elementAt(Row, Tabuleiro, Yelem),
	contaPecasRow(Row, Jogador, 1, 0,TempPeca),
	NumPecaInc is IncPeca+TempPeca,
	!,
	contaPecas(Tabuleiro, Jogador, Yelem, NumPecaInc, NumPeca).


contaPecasRow(Row, Jogador, 6, IncPeca, NumPeca) :- NumPeca is IncPeca.

contaPecasRow(Row, Jogador, Counter, IncPeca, NumPeca) :-
	Xelem is Counter+1,
	elementAt(Peca, Row, Xelem),
	Jogador is floor(Peca/10),
	IncNumPeca is IncPeca+mod(Peca,10),
	!,
	contaPecasRow(Row, Jogador, Xelem, IncNumPeca, NumPeca).

contaPecasRow(Row, Jogador, Counter, IncPeca, NumPeca) :-
	Xelem is Counter+1,
	elementAt(Peca, Row, Xelem),
	!,
	contaPecasRow(Row, Jogador, Xelem, IncPeca,NumPeca).


% Lista = []
listAvailableMoves(Jogador,Tabuleiro,CounterX,4,Lista,NovaLista) :- append([],Lista,NovaLista).

listAvailableMoves(Jogador,Tabuleiro,6,CounterY,Lista,NovaLista) :-
	CounterYInc is CounterY+1,
	listAvailableMoves(Jogador,Tabuleiro,1,CounterYInc,Lista,NovaLista).

listAvailableMoves(Jogador,Tabuleiro,CounterX,CounterY,Lista,NovaLista) :-
	checkPiece(Jogador, Tabuleiro, CounterX, CounterY, 0,0, Lista, PieceMoves),
	CounterXInc is CounterX+1,
	listAvailableMoves(Jogador,Tabuleiro,CounterXInc,CounterY,PieceMoves,NovaLista).


checkPiece(Jogador,Tabuleiro,PosX,PosY,7,5,Lista,NovaLista) :- append([], Lista, NovaLista).

checkPiece(Jogador, Tabuleiro,PosX,PosY,7,CounterY,Lista,NovaLista) :- 
	CounterYInc is CounterY+1,
	checkPiece(Jogador,Tabuleiro,PosX,PosY,0,CounterYInc,Lista,NovaLista).

checkPiece(Jogador,Tabuleiro,PosX, PosY, CounterX, CounterY, Lista, NovaLista) :-
	canMove([PosX,PosY],[CounterX,CounterY],Jogador,Tabuleiro,Lista,Moves),
	CounterXInc is CounterX+1,
	checkPiece(Jogador,Tabuleiro,PosX,PosY,CounterXInc,CounterY,Moves,NovaLista).

canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada,NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xtemp is Xfinal/6,
	(Xtemp is Float0; Xtemp is Float1),
	Yfinal < 5,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaX is 2; DeltaX is 0),
	DeltaY < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	Peca1 > 1,
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).

canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada,NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xtemp is Xfinal/6,
	(Xtemp is Float0; Xtemp is Float1),
	Yfinal < 5,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaX is 2; DeltaX is 0),
	DeltaY < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	Peca1 is 1,
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).

canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada,NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xtemp is Xfinal/6,
	(Xtemp is Float0; Xtemp is Float1),
	Yfinal < 5,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaX is 2; DeltaX is 0),
	DeltaY < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1 > 1,
	Peca2 is 9,
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).

canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada,NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xtemp is Xfinal/6,
	(Xtemp is Float0; Xtemp is Float1),
	Yfinal < 5,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaX is 2; DeltaX is 0),
	DeltaY < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1 is 1,
	Peca2 is 9,
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).


canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada,NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xfinal < 7,
	Ytemp is Yfinal/4,
	(Ytemp is Float0; Ytemp is Float1),
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaY is 2;DeltaY is 0),
	DeltaX < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	Peca1 > 1,
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).

canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada,NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xfinal < 7,
	Ytemp is Yfinal/4,
	(Ytemp is Float0; Ytemp is Float1),
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaY is 2;DeltaY is 0),
	DeltaX < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1+Peca2 < 4,
	Peca1 is 1,
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).

canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada,NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xfinal < 7,
	Ytemp is Yfinal/4,
	(Ytemp is Float0; Ytemp is Float1),
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaY is 2;DeltaY is 0),
	DeltaX < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1 > 1,
	Peca2 is 9,
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).

canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada, NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Float0 is float(0), Float1 is float(1),
	Xfinal < 7,
	Ytemp is Yfinal/4,
	(Ytemp is Float0; Ytemp is Float1),
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	(DeltaY is 2;DeltaY is 0),
	DeltaX < 3,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	(validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0); validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0)),
	validaDiag([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], TabuleiroActual),
	GetElementY is Yinit+1,
	GetElement2Y is Yfinal+1,
	GetElementX is Xinit+1,
	GetElement2X is Xfinal+1,
	elementAt(Rowtemp, TabuleiroActual, GetElementY),
	elementAt(Rowtemp2, TabuleiroActual, GetElement2Y),
	elementAt(NumPeca, Rowtemp, GetElementX),
	elementAt(NumPeca2, Rowtemp2, GetElement2X),
	Peca1 is mod(NumPeca,10),
	Peca2 is mod(NumPeca2,10),
	Peca1 is 1,
	Peca2 is 9,
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).


canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada, NovasPoss) :-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Xfinal > 0, Xfinal < 6,
	Yfinal > 0, Yfinal < 4,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	DeltaY < 2,
	DeltaX < 2,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	validaPosVazio([Xfinal|[Yfinal|_]], TabuleiroActual, 0),
	elementAt(Rowtemp, TabuleiroActual, Yinit+1),
	elementAt(NumPeca, Rowtemp, Xinit+1),
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).

canMove([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada, NovasPoss) :-
	append([],PossivelJogada, NovasPoss).

checkFusion([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada, NovasPoss):-
	Xinit > 0, Xinit < 6,
	Yinit > 0, Yinit < 4,
	Xfinal > 0, Xfinal < 6,
	Yfinal > 0, Yfinal < 4,
	DeltaX is abs(Xinit - Xfinal),
	DeltaY is abs(Yinit - Yfinal),
	DeltaY < 2,
	DeltaX < 2,
	validaPos([Xinit|[Yinit|_]], Jogador, TabuleiroActual, 0),
	validaPos([Xfinal|[Yfinal|_]], Jogador, TabuleiroActual, 0),
	append([[[Xinit,Yinit],[Xfinal,Yfinal]]],PossivelJogada,NovasPoss).

checkFusion([Xinit|[Yinit|_]],[Xfinal|[Yfinal|_]], Jogador,  TabuleiroActual, PossivelJogada, NovasPoss).