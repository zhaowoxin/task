#!/usr/bin/guile -s
!#

(define (func_call arg1)
  (lambda ()
    (call/cc 
      (lambda(k)
        (display arg1)
        (newline)
        ;;k
        k
      )
    )
  )
)

(define (func3)
  (lambda (arg1)
    (call/cc 
      (lambda(k)
        (display "Hello world")
        (newline)
        ;;k
      )
    )
    (arg1 arg1)
  )
)

(let ((func2 (func_call '(1 2 3 4 5)))
      ;;(func3 '(begin (display "func3 executed!") (newline)))
     )
  ((func2) (func2))
  ;;((func2) (func3))
  ;;(eval func3 (interaction-environment))
  (newline)
)
