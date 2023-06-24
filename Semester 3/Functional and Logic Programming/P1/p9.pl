%insert_value_in_list_on_position(L:list, E:elem, P:pos, R:list)
%flow_model: (i,i,i,o)
insert_value_in_list_on_position(L, E, 0, [E|L]):- !.
insert_value_in_list_on_position([H|T], E, P, [H|R]):-
    P1 is P-1,
    insert_value_in_list_on_position(T, E, P1, R).

%gcd(A:number, B:number, R:number)
%flow_model: (i,i,o)
gcd(A, 0, A):- !.
gcd(0, B, B):- !.
gcd(A, B, R):-
    A>=B,
    A1 is A mod B,
    gcd(A1, B, R),
    !.
gcd(A, B, R):-
    A<B,
    B1 is B mod A,
    gcd(A, B1, R),
    !.

gcd_list([H], H).
gcd_list([H|T], R):-
    gcd_list(T, R1),
    gcd(R1, H, R).