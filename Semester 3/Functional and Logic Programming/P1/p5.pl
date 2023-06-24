%remove_occurences(L:list, E:elem, R:list)
%flow_model: (i,i,o)
remove_occurences([], _, []).
remove_occurences([H|T], E, R):-
    H =:= E,
    remove_occurences(T,E,R).
remove_occurences([H|T], E, [H|R]):-
    H =\= E,
    remove_occurences(T,E,R).
    
%union(A:list, B:list, R:list)
%flow_model: (i,i,o)
union([],[],[]).
union([H|T], B, [H|R]):-
    remove_occurences([H|T], H, R1),
    remove_occurences(B, H, R2),
    union(R1, R2, R).
union([], B, R) :-
      union(B, [], R).

% sets(L:list, K:number, R:list)
% sets(i, i, o)

sets(_, 0, []) :- !.
sets([H|T], K, [H|R]) :-
    K1 is K - 1,
    sets(T, K1, R).
sets([_|T], K, R) :-
    sets(T, K, R).

% gen_sets(L:list, R:list)
% gen_sets(i, o)

gen_sets([], []).
gen_sets(L, R) :- findall(RS, sets(L, 2, RS), R).