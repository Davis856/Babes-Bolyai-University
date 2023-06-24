%even_list(L:list)
%flow_model: (i)
even_list([]).
even_list([_, _|T]) :- even_list(T).

%min_numbers(A:number, B:number, R:number)
%flow_model(i, i, o)
min_numbers(A, B, A):-
    A =< B.
min_numbers(A, B, B):-
    A > B.

%minim_list(L:list, R:list)
%flow_model: (i, o)
minim_list([H], [H]).
minim_list([H|T], R):-
    minim_list(T, R1),
    min_numbers(H, R1, R).

%delete_first_occurence(L:list, E: elem, R:list)
%flow_model: (i, i, o)
delete_first_occurence([H|T], H, T) :- !.
delete_first_occurence([H|T], M, [H|R]) :- delete_first_occurence(T, M, R).

% delete_first_min(L:list, R:list)
% delete_first_min(i, o)

delete_first_min(L, R) :-
    minim_list(L, RM),
    delete_first_occurence(L, RM, R).