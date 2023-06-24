%remove_occurence(L:list, E:elem, R:list)
%flow_model: (i,i,o)

remove_occurence([], _, []).
remove_occurence([H|T], E, R):-
    H =:= E,
    remove_occurence(T, E, R).

remove_occurence([H|T], E, [H|R]):-
    H =\= E,
    remove_occurence(T, E, R).
    
%count_occurence(L:list, E:elem, R:list)
%flow_model: (i,i,o)
count_occurence([], _, 0).
count_occurence([H|T], E, R) :- H =:= E,
    count_occurence(T, E, R1),
    R is R1 + 1.
count_occurence([H|T], E, R) :- H =\= E,
    count_occurence(T, E, R).

%remove_repetitive(L:list, R:list)
%flow_model: (i,o)
remove_repetitive([], []).
remove_repetitive([H|T], [H|R]):-
    count_occurence([H|T], H, RC),
    RC =:= 1,
    remove_repetitive(T, R).
remove_repetitive([H|T], R) :-
    count_occurence([H|T], H, RC),
    RC =\= 1,
    remove_occurence([H|T], H, RO),
    remove_repetitive(RO, R).
                  
% maxim_number(A:number, B:number, R:number)
% flow_model: (i, i, o)

maxim_number(A, B, A) :- A >= B.
maxim_number(A, B, B) :- A < B.
	
% maxim_list(L:list, R:number)
% flow_model: (i, o)

maxim_list([H], H).
maxim_list([H|T], R) :- 
    maxim_list(T, RM),
    maxim_number(H, RM, R).		

% remove_maxim(L:list, R:list)
% flow_model:(i, o)

remove_maxim(L, R) :-
    maxim_list(L, RM),
    remove_occurence(L, RM, R).