% para_main(i, o)
para_main(N, R):-N1 is N * 2, para(N1, 0, R).

% para(N, C) = 
%  = [], N == 0, C == 0
%  = '(' U para(N - 1, C + 1), N > 0, C < N
%  = ')' U para(N - 1, C - 1), N > 0, C > 0

% para(i, i, o)
para(0, 0, []).
para(N, C, ['('|T]):- N > 0, C < N,
    N1 is N - 1, C1 is C + 1, para(N1, C1, T).
para(N, C, [')'|T]):- N > 0, C > 0,
    N1 is N - 1, C1 is C - 1, para(N1, C1, T).