%contains(L:list, R:list)
%flow_model: (i,o)
contains([V|_], V):-
    !.
contains([_|T], V):-
    contains(T, V).

%difference(A: list, B: list, R:list)
%flow_model: (i,i,o)
difference([], [], []).
difference([H|T], B, R):-
    contains(B, H),
    difference(T, B, R),
    !.
difference([H|T], B, [H|R]):-
    difference(T,B,R).

% insert1(L:list, R:list)
% flow_model: (i, o)

insert1([], []).
insert1([H|T], [H, 1|R]) :- 
    H mod 2 =:= 0,
    insert1(T, R).
insert1([H|T], [H|R]) :- 
    H mod 2 =\= 0,
    insert1(T, R).