%my_append(L:list, E:number, R:list)
%flow_model: (i,i,o)
my_append([], E, [E]).
my_append([H|T], E, [H|R]):-
    my_append(T,E,R).

%my_length(L:list, R:number)
%flow_model: (i,o)
my_length([], 0).
my_length([_|T], R):-
    my_length(T, RC),
    R is RC+1.

%inv_list(L:list, R:list)
%flow_model: (i,o)
inv_list([], []).
inv_list([H|T], R):-
    inv_list(T,RI),
    my_append(RI, H, R).

%sum_lists(A:list, B:list, R:list)
%flow_model: (i,i,o)
sum_lists(A, [], A).
sum_lists([], B, B).
sum_lists(A, B, R):-
    my_length(A, LA),
    my_length(B, LB),
    LA =< LB,
    !,
    inv_list(A, RA),
    inv_list(B, RB),
    suma(RA, RB, 0, RS),
    inv_list(RS, R).
sum_lists(A, B, R):-
    inv_list(A, RA),
    inv_list(B, RB),
    suma(RB, RA, 0, RS),
    inv_list(RS, R).

%suma(L1:list, L2:list, C:number, R:list)
%flow_model: (i, i, i, o)
suma([], [], 0, []).
suma([], [], 1, [1]).
suma([], [HB|TB], C, [HBC|R]) :-
    HBC is (HB + C) mod 10, 
    HBC - HB - C =:= 0,
    suma([], TB, 0, R).
suma([], [HB|TB], C, [HBC|R]) :-
    HBC is (HB + C) mod 10, 
    HBC - HB - C =\= 0,
    suma([], TB, 1, R).
suma([HA|TA], [HB|TB], C, [HR|R]) :-
    HR is (HA + HB + C) mod 10,
    HR - HA - HB - C =:= 0,
    suma(TA, TB, 0, R).
suma([HA|TA], [HB|TB], C, [HR|R]) :-
    HR is (HA + HB + C) mod 10,
    HR - HA - HB - C =\= 0,
    suma(TA, TB, 1, R).

%succesor(L:list, R:list)
%succesor(i, o)

succesor(L, R):-
    sum_lists([1], L, R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([H|T], [HR|R]):-
    is_list(H),
    !,
    succesor(H, HR),
    heterList(T, R).
heterList([H|T], [H|R]):-
    heterList(T,R).





