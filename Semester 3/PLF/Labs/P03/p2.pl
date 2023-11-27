coliniare(X,_,X,_,X,_):-!.
coliniare(_,Y,_,Y,_,Y):-!.
coliniare(X1,Y1,X2,Y2,X3,Y3):-
    X1 =\= X2,X2 =\= X3,X1 =\= X3,
    Y1 =\= Y2,Y2 =\= Y3,Y1 =\= Y3,
    P1 is (Y2-Y1)/(X2-X1),
    P2 is (Y3-Y2)/(X3-X2),
    P1 =:= P2.

subset([], []).

subset([H|T], R):-
    subset(T, R1),
    R = [H|R1].

subset([_|T], R):-
    subset(T, R1),
    R = R1.

isOk([[X1, Y1], [X2, Y2], [X3, Y3]]):-
    coliniare(X1, Y1, X2, Y2, X3, Y3),
    !.

isOk([[X1, Y1], [X2, Y2], [X3, Y3] | T]):-
	coliniare(X1, Y1, X2, Y2, X3, Y3),
    isOk([[X2, Y2], [X3, Y3] | T]).

parseList([], []).

parseList([H|T], R):-
    isOk(H),
    !,
    parseList(T, R1),
    R = [H | R1].

parseList([_|T], R):-
    parseList(T, R1),
    R = R1.

getAllOkaySets(L, R):-
    findall(R1, subset(L, R1), R2),
    parseList(R2, R).
    