%count_occurences(L:list, E: elem, R:list)
%flow_model: (i,i,o)
count_occurences([], _, 0).
count_occurences([H|T], E, R1) :- H =:= E,
    count_occurences(T, E, R),
    R1 is R + 1.
count_occurences([H|T], E, R) :- H =\= E,
    count_occurences(T, E, R).

%test_set(L:list)
%flow_model:(i)
test_set([]).
test_set([H|T]) :- 
    count_occurences([H|T], H, R),
    R =:= 1,
    test_set(T), !.

%remove_k_occurences(L:list, E:number, K:number, R:list)
%flow_model(i,i,i,o)
remove_k_occurences([], _, _, []) :- !.
remove_k_occurences(L, _, 0, L):- !.
remove_k_occurences([H|T], E, K, R):-
    H =:= E,
    K1 is K - 1,
    remove_k_occurences(T, E, K1, R).
remove_k_occurences([H|T], E, K, [H|R]) :- H =\= E,
     remove_k_occurences(T, E, K, R).

% remove_3_occurences(L:list, E:number, R:list)
% remove_3_occurences(i, i, o)

remove_3_occurences(L, E, R) :- remove_k_occurences(L, E, 3, R).