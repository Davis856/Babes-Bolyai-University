% my_length(L -list, N - number)
% my_length(i, o)
my_length([], 0).
my_length([_|T], C):- my_length(T, C1),
    C is C1 + 1.

% contains(L:list, E:number)
% contains(i, i)

contains([V|_], V) :- !.
contains([_|T], E) :- contains(T, E).

% remove_occurences(L:list, E:number, R:list)
% remove_occurences(i, i, o)

remove_occurences([], _, []).
remove_occurences([H|T], E, R) :- H =:= E,
    remove_occurences(T, E, R).
remove_occurences([H|T], E, [H|R]) :- H =\= E,
    remove_occurences(T, E, R).


% set_equal(A:list, B:list)
% set_equal(i, i)

set_equal([], []).
set_equal([HA|TA], [HB|TB]) :-
    my_length(TA, CA),
    my_length(TB, CB),
    CA =:= CB,
    contains([HB|TB], HA),
    contains([HA|TA], HB),
    remove_occurences(TB, HA, RA),
    remove_occurences(TA, HB, RB),
    set_equal(RA, RB).

% select_n(L:list, N:number, R:number)
% select_n(i, i, o)

select_n([H|_], 1, H) :- !.
select_n([_|T], N, R) :- 
    New_n is N - 1,
    select_n(T, New_n, R).