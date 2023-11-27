% 8.
% a. Write a predicate to determine if a list has even numbers of elements 
% without counting the elements from the list.
% b. Write a predicate to delete first occurrence of the minimum number from a list.

% evenElems(l1, l2,...,ln): true, if n == 0
% 				          : evenElems(l3, l4, ..., ln)
evenElems([]) :- true.
evenElems([_,_|T]):- evenElems(T).


% findMin(l1, l2, ..., ln, M): l1, if n == 1
%							 : min(l1, findMin(l2, ... , ln, M))

findMin([H], M):- M = H.
findMin([H|T], M):- findMin(T, M1),
    				H < M1,
    				M = H.
findMin([H|T], M):- findMin(T, M1),
    				H >= M1,
    				M = M1.


% deleteFirstOccurence(l1, l2,...,ln, e): [], if n == 0
%   									: [l2,...,ln], if l1 == e
%										: [l1] U deleteFirstOccurence(l2,...,ln, e), if l1 != e

deleteFirstOccurence([], R, _):- R = [].
deleteFirstOccurence([H|T], R, E):- H =:= E,
    								R = T.
deleteFirstOccurence([H|T], R, E):- H =\= E,
    								deleteFirstOccurence(T, R1, E),
    								R = [H|R1].

deleteFirstMin(L, R):- findMin(L, E),
    				   deleteFirstOccurence(L, R, E).