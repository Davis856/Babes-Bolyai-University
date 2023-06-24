%even(N:number)
%flow_model: (i)
even(N):-
    N mod 2 =:= 0.

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

%consecutive(L:list, C:list, AUX: list, R:list)
%flow_model: (i,i,i,o)
consecutive([], C, AUX, C):-
    my_length(C, RC),
    my_length(AUX, RAUX),
    RC >= RAUX.
consecutive([], C, AUX, AUX):-
    my_length(C, RC),
    my_length(AUX, RAUX),
    RC < RAUX.
consecutive([H|T], C, AUX, R):-
    even(H),
    my_append(AUX, H, RA),
    consecutive(T, C, RA, R).
consecutive([_|T], C, AUX, R):-
    my_length(C, RC),
    my_length(AUX, RAUX),
    RAUX >= RC,
    consecutive(T, AUX, [], R).
consecutive([_|T], C, AUX, R) :-
    my_length(C, RC),
    my_length(AUX, RAUX),
    RAUX < RC,
    consecutive(T, C, [], R).

%heterList(L:list, R:list)
%flow_model: (i,o)
heterList([], []).
heterList([H|T], [HR|R]):-
    is_list(H),
    !,
    consecutive(H,[],[],HR),
    heterList(T,R).
heterList([H|T], [H|R]):-
    heterList(T,R).
