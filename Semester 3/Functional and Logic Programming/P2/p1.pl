%my_length(L:list, C:number, R:number)
%flow_model: (i,i,o)
my_length([], C, C).
my_length([H|T], C, R):-
    NC is C+1,
    my_length(T, NC, R).

%merge_sort(L:list, R:list)
%flow_model: (i,o)
merge_sort([], []).
merge_sort([E], [E]).
merge_sort(L, R):-
    split(L, Left, Right),
    merge_sort(Left, RL),
    merge_sort(Right, RR),
    my_merge(RL, RR, R).

%split(L:list, LC:list, Left:list, Right:list)
%flow_model: (i,i,o,o)
split(L, LC, LC, L):-
    my_length(L, 0, RL),
    my_length(LC, 0, RLC),
    Diff is RLC - RL,
    abs(Diff, AUX),
    AUX =< 1.
split([H|T], LC, Left, Right):-
    my_append(LC, H, RA),
    split(T, RA, Left, Right).

%split(L:list, Left:list, Right:list)
%flow_model: (i,o,o)
split(L, Left, Right):-
    split(L, [], Left, Right).

%my_append(L:list, E:number, R:list)
%flow_model: (i,i,o)
my_append([], E, [E]).
my_append([H|T], E, [H|R]):-
    my_append(T,E,R).


%my_merge(L:list, R:list, R:list)
%flow_model: (i,i,o)
my_merge(L, [], L).
my_merge([], R, R).
my_merge([HL|TL], [HR|TR], [HL|R]):-
    HL =< HR,
    my_merge(TL, [HR|TR], R).
my_merge([HL|TL], [HR|TR], [HR|R]):-
    HL > HR,
    my_merge([HL|TL], TR, R).

%remove_doubles(L:list, R:list)
%flow_model: (i,o)
remove_doubles([],[]).
remove_doubles([E], [E]).
remove_doubles([H1, H2|T], [H1|R]):-
    H1 =\= H2,
    remove_doubles([H2|T], R).
remove_doubles([H1, H2|T], R):-
    H1 =:= H2,
    remove_doubles([H2|T], R).

%sort_list(L:list, R:list)
%flow_model: (i,o)
sort_list(L, R):-
    merge_sort(L, RS),
    remove_doubles(RS, R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([H|T], [HR|R]):-
    is_list(H),
    !,
    sort_list(H, HR),
    heterList(T, R).
heterList([H|T], [H|R]):-
    heterList(T,R).