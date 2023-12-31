%abs(X: int, Y: int)
%flow model: (i, i), (o, i), (i, 0)
%X - number
%Y - absolute value of a number, result
abs(X,X):-
    X >= 0,
    !.

abs(X, Y):-
    X < 0,
    Y is -X.

%gcd(X: int, Y: int, Z: int)
%flow model: (i, i, o) or (i, i, i)
%X - first number
%Y - second number
%Z - result
gcd(0,X,X).
gcd(X,0,X).
gcd(X,X,X).
gcd(X,Y,Z):-
    Y>X,
    Y1 is Y-X,
    gcd(X,Y1,Z).
gcd(X,Y,Z):-
    Y<X,
    X1 is X-Y
    gcd(X1,Y,Z).

%lcm(X: int, Y: int, Z:int)
%flow model:(i,i,o) or (i,i,i)
%X - first number
%Y - second number
%Z - result

lcm(0,_,0).
lcm(_,0,0).
lcm(X,Y,Z):-
    abs(X*Y,P),
    gcd(X,Y,D),
    Z is P/D.

%lcm_list(L:list, R:int)
%flow model: (i,0) or (i,i)
%L - list for lcm
%R - the result

lcm_list([E], E).
lcm_list([H|T], R):-
    lcm_list(T, R1),
    lcm(H,R1,R).

%problem 1.b

%pow2(X: int, R: int)
%flow model:(i,o) or (i,i)
%X - the number to be checked
%Y - result(0 only if X is a power of two)
pow2(X, R):-
    X>0,
    R is X /\ (X-1).

%add_after(List: list, Position:int, V: int, Result: list)
%flow model:(i,i,i,o),(i,i,o,i),(i,i,i,i),(o,i,i,i),(o,i,o,i)
%List - initial list
%Position - the current pos
%V - the elem to be added
%Result - the final list
add_after([],_,_,[]).
add_after([H1|T1], Position, V, [H1|[V|T2]]):-
    pow2(Position, R),
    R =:= 0,
    Position1 is Position + 1,
    add_after(T1, Position1, V, T2).
add_after([H1|T1], Position, V, [H1|T2]):-
    pow2(Position, R),
    R =\= 0,
    Position1 is Position + 1,
    add_after(T1, Position1, V, T2).

add_after(List, V, Result):- add_after(List,1,V,Result).

