(define (isort lst)
    (letrec ( [insert (lambda (x l)
                          (cond [(null? l)         (list x)]
                                [(<= x (car l)) (cons x l)]
                                [else
                                   (cons (car l) (insert x (cdr l)))]
                          ))])
            (cond
                [(null? lst)  ()]
                [else         (insert (car lst) (isort (cdr lst)))]
            )))



(isort '(2 5 9 3 6 10))
(isort '(72.4 74.2 0.9))
