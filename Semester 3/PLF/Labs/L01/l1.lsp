; 8.
; a) Write a function to return the difference of two sets.
; b) Write a function to reverse a list with its all sublists, on all levels.
; c) Write a function to return the list of the first elements of all list elements of a given list with an odd 
; number of elements at superficial level. Example: (1 2 (3 (4 5) (6 7)) 8 (9 10 11)) => (1 3 9).
; d) Write a function to return the sum of all numerical atoms in a list at superficial level.

; 1.a)

; contains(l1, l2, ..., ln, e): false, if n == 0
;                             : true, if l1 == e
;                             : contains(l2,...,ln, e), otherwise

(defun contains(l e)
  (cond
    ((null l) nil)
    ((equal (car l) e) t)
    (t (contains (cdr l) e))
  )
)

; setsDifference(l1, l2,..,ln, p1,p2,...,pm): [], if n == 0
;                                           : setsDifference(l2,...,ln,p1,...pm), if contains(p1,..,pm, l1)
;                                           : [l1] U setsDifference(l2,...,ln,p1,...,pm), otherwise

(defun setsDifference(l1 l2)
        (cond
                ((null l1) nil)
                ((contains l2 (car l1)) (setsDifference (cdr l1) l2))
                (t (cons (car l1) (setsDifference (cdr l1) l2))) 
          
        )
)

(write (setsDifference `(1 2 3 4) `(3)))

; 1.b)
; concat(l1,...,ln, p1,...,pm): [l1,...,ln], m = 0
;                             : [p1,...,pm], n = 0
;                             : [l1] U concat(l2,...,ln, p1,...,pm), otherwise

(defun concat(l1 l2)
  (cond
    ((null l1) l2)
    ((null l2) l1)
    (t (cons (car l1) (concat (cdr l1) l2)))
  )
)

; reverseList(l1, l2,...,ln): [], n == 0
;                           : reverseList(l2,...,ln) U [l1], otherwise

(defun reverseList(l)
  (cond
    ((null l) nil)
    ((LISTP (car l)) 
      (concat (reverseList (cdr l)) (cons (reverseList (car l)) nil))
    )
    (t (concat (reverseList (cdr l)) (cons (car l) nil)))
  )
)

(write (reverseList `(1 2 3 (4 5 (6 7)))))

; 1.c)
; countElements(l1, ..., ln): 0, if n == 0
;                           : 1 + countElements(l2, ..., ln), otherwise

(defun countElements(l)
  (cond
    ((null l) 0)
    (t (+ 1 (countElements (cdr l))))
  )
)

; getFirstElems(l1,...,ln): nil, if n == 0
;                         : [l1[0]] U getFirstElems(l2,...,ln) if listp(l1) and len(l1) % 2 = 1
;                         : getFirstElems(l2,...,ln), otherwise

(defun getFirstElems(l)
  (cond
    ((null l) nil)
    ((and (LISTP (car l)) (EQUAL (mod (countElements (car l)) 2) 1)) (cons (caar l) (getFirstElems (cdr l))))
    (t (getFirstElems (cdr l)))
  )
)

(defun main(l)
  (cond
    (t (getFirstElems (cons l l)))
  )
)

(write (main `( 1 2 ( 3 ( 4 5 ) ( 6 7 ) ) 8 ( 9 10 11 ) ) ) )

; 1.d)
; sumOfAtoms(l1,...,ln): 0, if n == 0
;                      : l1 + sumOfAtoms(l2,...,ln), if l1 is number
;                      : sumOfAtoms(l2, ...,ln), otherwise

(defun sumOfAtoms(l)
  (cond
    ((null l) 0)
    ((numberp (car l)) (+ (car l) (sumOfAtoms (cdr l))))
    (t (sumOfAtoms (cdr l)))
  )
)

(write (sumOfAtoms `(2 5 (3 5) 7) ))