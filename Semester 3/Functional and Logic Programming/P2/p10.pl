%nrPrim(N:number, Div:number)
%flow_model: (i, i)
nrPrim(N, _):-
    N > 0,
    N <= 3.
nrPrim(N, Div):- 
    N mod Div =\= 0,
    Div >= N/2,
    !.
nrPrim(N, Div):-
    N mod Div =\= 0,
    NDiv is Div + 2,
    nrPrim(N, NDiv).

%primeTice(L:list, R:list)
%flow_model: (i,o)
primeTwice([], []).
primeTwice([H|T], [H,H|R]):-
    nrPrim(H, 3),
    !,
    primeTwice(T,R).
primeTwice([H|T], [H|R]):-
    primeTwice(T,R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([E], [E]).
heterList([H|T], [HR|R]):-
    is_list(H),
    !,
    primeTwice(H, HR),
    heterList(T,R).
heterList([H|T], [H|R]):-
    heterList(T,R).