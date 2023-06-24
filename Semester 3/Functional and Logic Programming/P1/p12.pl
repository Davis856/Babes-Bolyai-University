%insert(L:list, List:list, R:list)
%flow_model: (i,i,o)
insert([], L, L).
insert([H|T], L, [H|R]):-
    insert(T,L,R).

%substitute_elem(L:list, E:elem, List:List, R:list)
%flow_modeL: (i,i,o)
substitute_elem([], _, _, []).
substitute_elem([H|T], E, List, R) :-
    H =:= E,
    insert(List, T, RI),
    substitute_elem(RI, E, List, R).
substitute_elem([H|T], E, List, [H|R]) :-
    H =\= E,
    substitute_elem(T, E, List, R).

%remove_n(L:list, K:elem, R:list)
%flow_model: (i,i,o)
remove_n([], _, []).
remove_n([_|T], 1, T).
remove_n([H|T], K, [H|R]):-
    K1 is K-1,
    remove_n(T, K1, R).