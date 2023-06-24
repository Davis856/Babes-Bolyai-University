%contains(L: list, E: elem)
%flow_model: (i,i)
contains([V|_], V) :- !.
contains([_|T], E) :- contains(T, E).

%intersection(A:list, B:list, R:list)
%flow_model: (i,i,o)
intersection([], _, []).
intersection([H|T], B, [H|R]):-
    contains(B, H),
    intersection(T,B,R),
    !.
intersection([_|T], B, R) :- intersection(T, B, R).

% new_list(M:number, N:number, R:list)
% new_list(i, i, o)
 
new_list(N, N, [N]).
new_list(M, N, [M|R]) :- 
    New_m is M + 1,
    new_list(New_m, N, R).