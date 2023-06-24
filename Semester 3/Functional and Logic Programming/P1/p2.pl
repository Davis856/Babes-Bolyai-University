%remove_occurence(L:list, E:elem, R:list)
%flow_model: (i,i,o)

remove_occurence([], _, []).
remove_occurence([H|T], E, R):-
    H =:= E,
    remove_occurence(T, E, R).

remove_occurence([H|T], E, [H|R]):-
    H =\= E,
    remove_occurence(T, E, R).
    
%count_occurence(L:list, E:elem, R:list)
%flow_model: (i,i,o)
count_occurence([], _, []).
count_occurence([H|T], E, R):-
    H =:= E,
    count_occurence(T, E, R),
    R1 is R+1.
count_occurence([H|T], E, [H|R]):-
    H =\= E,
    count_occurence(T, E, R).

%numberatom(L:list, R:list)
%flow_model: (i,o)
numberatom([], []).
numberatom([H|T], [[H|RC]|R]):-
    count_occurences([H|T], H, RC),
    remove_occurences(T, H, RR),
    numberatom(RR, R).
    