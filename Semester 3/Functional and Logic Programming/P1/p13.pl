%count_occurences(L:list, E:elem, R:number)
%flow_model: (i,i,o)
count_occurences([], _, 0).
count_occurences([H|T], E, R) :-
    H =:= E,
    count_occurences(T, E, R1),
    R is R1 + 1.
count_occurences([H|T], E, R) :-
    H =\= E,
    count_occurences(T, E, R).

%list_to_set(L:list, R:list)
%flow_model: (i,o)
list_to_set([], []) :-
    !.
list_to_set([H|T], [H|R]) :- 
    count_occurences(T, H, RC),
    RC =:= 0,
    list_to_set(T, R),
    !.
list_to_set([_|T], R) :-
    list_to_set(T, R).

%gcd(A:number, B:number, R:number)
%flow_model: (i,i,o)
gcd(A, 0, A):- !.
gcd(0, B, B):- !.
gcd(A, B, R):-
    A >= B,
    A1 is A mod B,
    gcd(A1, B, R),
    !.
gcd(A, B, R):-
    A < B,
    B1 is B mod A,
    gcd(A, B1, R),
    !.

%gcd_list(L:list, R:list)
%flow_model: (i,o)
gcd_list([H], [H]).
gcd_list([H|T], R):-
    gcd_list(T, R1),
    gcd(R1, H, R).