%my_append(L:list, E:number, R:list)
%flow_model: (i,i,o)
my_append([], E, [E]).
my_append([H|T], E, [H|R]):-
    my_append(T,E,R).

%inv_list(L:list, R:list)
%flow_model: (i,o)
inv_list([], []).
inv_list([H|T], R):-
    inv_list(T,RI),
    my_append(RI, H, R).

%product(L:list, E:number, C:number, R:list)
%flow_model: product(i,i,i,o)
product([], _, 0, []).
product([], _, C, [C]):-
    C =\= 0.
product([H|T], E, C, [HR|R]):-
    HR is (H * E + C) mod 10,
    NC is (H * E +C - HR) / 10,
    product(T,E,NC,R).

%product_list(L:list, E:number, R:list)
%flow_model: (i,i,o)
product_list(L, E, R):-
    inv_list(L, LI),
    product(LI, E, 0, RP),
    inv_list(RP, R).

%maxim_number(A:number, B:number, R:number)
%flow_model: (i,i,o)
maxim_number(A, B, A):-
    A>=B.
maxim_number(A, B, B):-
    A < B.

%maxim_list(L:list, R:number)
%flow_model: (i,o)
maxim_list([H], H).
maxim_list([H|T], R):-
    maxim_list(T, RM),
    maxim_number(H, RM, R).

%replace_pos(L:list, E:number, Pos:number, R:list)
%flow_model: (i,i,i,o)
replace_pos([], _, _, []).
replace_pos([H|T], E, Pos, [Pos|R]):-
    H =:= ,
    NPos is Pos + 1,
    replace_pos(T,E,Npos, R).
replace_pos([H|T], E, Pos, R):-
    H =\= E,
    NPos is Pos+1,
    replace_pos(T, E, NPos, R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([H|T], [HR|R]):-
    is_list(H),
    !,
    maxim_list(H, RM),
    replace_pos(H, RM, 1, HR),
    heterList(T, R).
heterList([H|T], [H|R]):-
    heterList(T,R).