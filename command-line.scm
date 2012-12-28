#! /usr/bin/guile -s
!#
(define cmm (command-line))
(display "应用程序名称：")
(display (car cmm))  
(newline)
(define args (cdr cmm))
(define long (length args))
(define loop (lambda (count len obj)
               (if (<= count len)
                 (begin
                   (display "参数 ")
                   (display count)
                   (display " 是：")
                   (display (list-ref obj (- count 1)))
                   (newline)
                   (set! count (+ count 1))
                   (loop count len obj)))))
(loop 1 long args)
