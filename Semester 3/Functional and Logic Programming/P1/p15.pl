% remove_occurences(L:list, E:number, R:list)
% remove_occurences(i, i, o)
remove_occurences([], _, []).
remove_occurences([H|T], E, R) :- H =:= E,
    remove_occurences(T, E, R).
remove_occurences([H|T], E, [H|R]) :- H =\= E,
    remove_occurences(T, E, R).

% list_to_set(L:list, R:list)
% list_to_set(i, o)

list_to_set([], []).
list_to_set([H|T], [H|R]) :- 
    remove_occurences(T, H, R1),
    list_to_set(R1, R).

% decompose(L:list, R:list)
% decompose(i, o)
decompose([], [0, 0, [], []]).
decompose([H|T], [H1f, H2, [H|H3], H4]) :-
    H mod 2 =:= 0,
    decompose(T, [H1, H2, H3, H4]),
	H1f is H1 + 1.
decompose([H|T], [H1, H2f, H3, [H|H4]]) :-
    H mod 2 =:= 1,
    decompose(T, [H1, H2, H3, H4]),
	H2f is H2 + 1.