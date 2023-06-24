%predecesor(L:list, C:number, R:list)
%flow_model: (i,i,o)
predecesor([], _, []):- !.
predecesor([0], 1, [9]):- !.
predecesor([N], 0, [NR]):-
    NR is N-1, !.
predecesor([0|T], 1, [9|R]):-
    predecesor(T, 1, R),
    !.
predecesor([H|T], 0, [HR|R]):-
    predecesor(T, C, R),
   	HR is H-C.

% heterList(L:list, R:list)
% flow model: heterList(i, o)

heterList([], []).
heterList([H|T], [HR|R]) :- is_list(H), !,
    predecesor(H, _, HR),
    heterList(T, R).
heterList([H|T], [H|R]) :-
    heterList(T, R).
