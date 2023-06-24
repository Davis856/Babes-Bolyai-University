%replaceEl(L:list, E1:number, E2:number, R:list)
%flow_model: (i,i,i,o)
replaceEl([], _, _, []).
replaceEl([H|T], E1, E2, [E2|R]):-
    H =:= E1,
    !,
    replaceEl(T, E1, E2, R).
replaceEl([H|T], E1, E2, [H|R]):-
    replaceEl(T, E1, E2, R).

%maxim_number(A:number, B:number, R:number)
%flow_model: (i,i,o)
maxim_number(A, B, A):-
    A >= B.
maxim_number(A, B, B):-
    A < B.

%maxim_list(L:list, R:number)
%flow_model: (i,o)
maxim_list([H], H).
maxim_list([H|T], R):-
    number(H),
    !,
    maxim_list(T, RM),
    maxim_number(H, RM, R).
maxim_list([_|T], R):-
    maxim_list(T, R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], _, []).
heterList([H|T], M, [HR|R]):-
    is_list(H),
    !,
    maxim_list(H, RM),
    replaceEl(H, M, RM, HR),
    heterList(T, M, R).
heterList([H|T], M, [H|R]):-
    heterList(T,M,R).

%mainHeter(L:list, R:list)
%flow_model: (i,o)
mainHeter(L, R):-
    maxim_list(L, RM),
    heterList(L, RM, R).