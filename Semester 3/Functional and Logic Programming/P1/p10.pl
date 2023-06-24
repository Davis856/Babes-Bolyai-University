%valley(L:list, F:number)
%flow_model: (i, i)
valley([_], 0).
valley([H1, H2|T], F):-
    H1 < H2,
    valley([H2|T], 0),
    !.
valley([H1, H2|T], F):-
    H1 > H2,
    valley([H2|T], 1),
    !.

%alternative_sum(L:list, R:number)
%flow_model(i, o)
alternative_sum([], 0).
alternative_sum([H], H).
alternative_sum([H1, H2|T], R):-
    alternative_sum(T, R1),
    R is H1 - H2 + R1.