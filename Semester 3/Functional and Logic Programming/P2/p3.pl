%my_merge(L:list, R:list, R:list)
%flow_model: (i,i,o)
my_merge(L, [], L).
my_merge([], R, R).
my_merge([HL|TL], [HR|TR], [HL|R]):-
    HL < HR,
    my_merge(TL, [HR|TR], R).
my_merge([HL|TL], [HR|TR], [HR|R]):-
    HL > HR,
    my_merge([HL|TL], TR, R).
my_merge([HL|TL], [HR|TR], R):-
    HL = HR,
    my_merge([HL|TL], TR, R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([H|T], R):-
    is_list(H),
    !,
    heterList(T, RH),
    my_merge(H, RH, R).
heterList([_|T], R):-
    heterList(T, R).