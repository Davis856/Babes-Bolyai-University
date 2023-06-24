%maxim_number(A:number, B:number, R:number)
%flow_model: (i,i,o)
maxim_number(A, B, A):-
    A>=B.
maxim_number(A, B, B):-
    A < B.

%maxim_list(L:list, R:number)
%flow_model: (i,o)
maxim_list([H], H).
maxim_list([H|T], R):-
    maxim_list(T, RM),
    maxim_number(H, RM, R).

%replace_pos(L:list, E:number, Pos:number, R:list)
%flow_model: (i,i,i,o)
replace_pos([], _, _, []).
replace_pos([H|T], E, Pos, [Pos|R]):-
    H =:= E,
    NPos is Pos + 1,
    replace_pos(T, E, NPos, R).
replace_pos([H|T], E, Pos, R):-
    H =\= E,
    NPos is Pos + 1,
    replace_pos(T, E, NPos, R).

%maxpos(L:list, R:list)
%flow_model: (i,o)
maxpos(H, R):-
    maxim_list(H, RM),
    replace_pos(H, RM, 1, R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([H|T], [HR|R]):-
    is_list(H),
    !,
    maxpos(H, HR),
    heterList(T, R).
heterList([H|T], [H|R]):-
    heterList(T, R).	