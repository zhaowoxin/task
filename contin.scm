#!/usr/bin/guile -s
!#

(define (func_call arg1)
  (display "hello ")
  (lambda ()
    (call/cc 
      (lambda(k)
        (display arg1)
        (newline)
        ;;(k (cons arg1 '(1 2 3)))
        ;;(cons arg1 '(1 2 3))
        ;;(display (cons arg1 '(1 2 3)))
        k
        ;;(display "Can execute Here?")
        ;;(newline)
      )
    )
  )
)

(begin
  (let ((func2 (func_call '(1 2 3 4 5))))
    ;;(display (func2))
    ;;((func2) (func2))
    ((func2) (func2))
    (display " world")
    (newline)
  )
)
