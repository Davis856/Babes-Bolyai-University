%insert_list(L:list, E:number, Pos:number, R:list)
%flow_model: (i,i,i,o)
insert_list([], _, _, []).
insert_list([H|T], E, Pos, [H,E|R]):-
    Pos mod 2 =:= 1,
    !,
    NPos is Pos + 1,
    insert_list(T, E, NPos, R).
insert_list([H|T], E, Pos, [H|R]):-
    NPos is Pos+1,
    insert_list(T, E, NPos, R).

%insertNb(L:list, E:number, R:list)
%flow_model: insertNb(i, i, o)
insertNb(L, E, R):-
    insert_list(L,E,1,R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([E], [E]).
heterList([H1, H2|T], [H1,HR|R]):-
    is_list(H2),
    number(H1),
    !,
    insertNb(H2, H1, HR),
    heterList(T, R).
heterList([H|T], [H|R]):-
    heterList(T, R).