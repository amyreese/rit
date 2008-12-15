(define base 0)

(define (iota n) 
    (cond ((equal? n base) (list n))
           (else (append (iota (- n 1)) (list n)))))

(iota 5)
(iota 1)
(iota 10)
(define base 1)
(iota 5)
(iota 1)
(iota 10)
