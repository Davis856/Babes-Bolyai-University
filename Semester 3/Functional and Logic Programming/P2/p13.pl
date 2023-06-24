%remConsecutive(L:list, R:list)
%flow_model: (i,o)
remConsecutive([], []).
remConsecutive([E], [E]).
remConsecutive([H1, H2], []) :- H2 =:= H1 + 1.
remConsecutive([H1, H2], [H1, H2]) :- H2 =\= H1 + 1.
remConsecutive([H1, H2, H3|T], R) :- 
    H2 =:= H1 + 1,
    H3 =:= H2 + 1,
    remConsecutive([H2, H3|T], R).
remConsecutive([H1, H2, H3|T], R) :- 
    H2 =:= H1 + 1,
    H3 =\= H2 + 1,
    remConsecutive([H3|T], R).
remConsecutive([H1, H2, H3|T], [H1|R]) :- 
    H2 =\= H1 + 1,
    remConsecutive([H2,H3|T], R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([H|T], [HR|R]):-
    is_list(H),
    !,
    remConsecutive(H, HR),
    heterList(T, R).
heterList([H|T], [H|R]):-
    heterList(T,R).