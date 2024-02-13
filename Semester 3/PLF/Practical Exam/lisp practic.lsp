; problem 1:  map as walk 
; double the numerical values in a list at any level 
; test:  
; > (double '(1 2 a (3 4) b c))  
; (2 4 A (6 8) B C) 


; problem 2: workers 
; given a list of length n of sublists representing work items and a list of length n of functions representing workers obtain the list of results of performing the work 
; by each worker on their corresponding work item 
; test: 
; > (work '(+ * -) '((2 3) (1 2) (7 5 1))) 
; (5 2 1) 

; problem 1 solution:
(defun double1(l)
  (cond
    ((null l) nil)
    ((numberp l) (* 2 l))
    ((atom l) l)
    (t (mapcar #'double1 l))
  )
)

(write (mapcar #'(lambda (l) 
                  (
                    cond
                      ((null l) nil)
                      ((numberp l) (* 2 l))
                      ((atom l) l)
              
                  ) 
                )
'(1 2 a (3 4) b c)))

; problem 2 solution:
(defun work(l1 l2)
  (mapcar #'apply  l1 l2)
)

(write (work '(+ * -) '((2 3) (1 2) (7 5 1) (3 4))))