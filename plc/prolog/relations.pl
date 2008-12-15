father(A,B) :- parent(A,B),male(A).

mother(A,B) :- parent(A,B),female(A).

son(A,B) :- parent(B,A),male(A).

daughter(A,B) :- parent(B,A),female(A).

sibling(A,B) :- parent(P,A),parent(P,B), A \= B.

brother(A,B) :- sibling(A,B),male(A).

sister(A,B) :- sibling(A,B),female(A).

husband(A,B) :- male(A),female(B),parent(A,C),parent(B,C).

wife(A,B) :- female(A),male(B),parent(A,C),parent(B,C).

spouse(A,B) :- husband(A,B).
spouse(A,B) :- wife(A,B).

%motherinlaw(A,B)

%fatherinlaw(A,B)

%aunt(A,B)

%uncle(A,B)

%nephew(A,B)

%niece(A,B)

%cousin(A,B)

%ancestor(A,B)

