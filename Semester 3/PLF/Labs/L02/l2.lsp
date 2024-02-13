; 8. Return the list of nodes of a tree of type (2) accessed inorder.

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

; tree = (head (subtree1) (subtree2))

; inorder(l1, ..., ln): [], n == 0
;                     : inorder(l2) U [l1] U inorder(l3), else

(defun inorder(l)
  (cond
    ((null l) nil)
    (t (concat (concat (inorder (cadr l)) (cons (car l) nil)) (inorder (caddr l))))
  )
)

(write 
  (inorder `(A (B) (C (D) (E))) 
  )
)