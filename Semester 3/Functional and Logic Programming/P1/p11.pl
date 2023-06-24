%substitute_elem(L:list, E1:number, E2: number, R:list)
%flow_model: (i,i,i,o)
substitute_elem([], _, _, []) :- !.
substitute_elem([H|T], E1, E2, [E2|R]) :- H =:= E1,
    substitute_elem(T, E1, E2, R).
substitute_elem([H|T], E1, E2, [H|R]) :- H =\= E1,
    substitute_elem(T, E1, E2, R).

% sublist(L:list, M:number, N:number, POS:number, R:list)
% sublist(i, i, i, o)

sub_list(_, _, N, POS, []) :- POS > N, !.
sub_list([H|T], M, N, POS, [H|R]) :- M =< POS, POS =< N,
    New_pos is POS + 1,
    sub_list(T, M, N, New_pos, R), !.
sub_list([_|T], M, N, POS, R) :-
    New_pos is POS + 1,
    sub_list(T, M, N, New_pos, R).