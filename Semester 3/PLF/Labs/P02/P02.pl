% successor(l1, l2, ..., ln, carry, isFirst) = 
%       [l1 + 1], if n == 1 and l1 < 9
%       [0], n == 1, if l1 == 9 and isFirst == 0
%       [1, 0], n == 1, if l1 == 9 and isFirst == 1
%       [l1 + carry] U successor(l2,...,ln, carry, 0), if l1 < 9
%       [l1] U successor(l2,...,ln, carry, 0), if l1 == 9 and carry == 0
%       [0] U successor(l2,...,ln, carry, 0), if l1 == 9 and carry == 1
%       [l1 + carry] U successor(l2,...,ln, carry, 0) if l1 < 9 and isFirst == 1
%       [l1] U successor(l2,...,ln, carry, 0) if l1 == 9 and carry == 0 and isFirst == 0
%       [1, 0] U successor(l2,...,ln, carry, 0) if l1 == 9 and carry == 1 and isFirst == 1


%base case
successor([H], R, C, _):- H < 9, D is H + 1, C is 0, R = [D].
successor([H], R, C, 0):- H =:= 9, C is 1, R = [0].
successor([H], R, C, 1):- H =:= 9, C is 0, R = [1, 0].

% inner digits
successor([H|T], R, C, 0):- H < 9, successor(T, R1, C1, 0), D is H + C1, C is 0, R = [D|R1].
successor([H|T], R, C, 0):- H =:= 9, successor(T, R1, C1, 0), C1 =:= 0, C is 0, R = [H|R1].
successor([H|T], R, C, 0):- H =:= 9, successor(T, R1, C1, 0), C1 =:= 1, C is 1, R = [0|R1].

% left most digit
successor([H|T], R, _, 1):- H < 9, successor(T, R1, C1, 0), D is H + C1, R = [D|R1].
successor([H|T], R, _, 1):- H =:= 9, successor(T, R1, C1, 0), C1 =:= 0, R = [H|R1].
successor([H|T], R, _, 1):- H =:= 9, successor(T, R1, C1, 0), C1 =:= 1, R = [1,0|R1].

successorWrapper(N, R) :- successor(N, R, _, 1).

% subListSuccessor(l1, l2, ..., ln) = [] if n == 0
%									= successorWrapper(l1) U subListSuccessor(l2, ..., ln) if l1 is list
%									= [l1] U subListSuccessor(l2, ..., ln) otherwise

subListSuccessor([], []).
subListSuccessor([H|T], R):- is_list(H), successorWrapper(H, R1), !, subListSuccessor(T, R2), R = [R1|R2].
subListSuccessor([H|T], R):- subListSuccessor(T, R1), R = [H|R1].
