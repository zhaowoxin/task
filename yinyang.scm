#!/usr/bin/guile -s
!#

#!
(let* ((yin ((lambda (foo) (display "@") foo) (call/cc (lambda (bar) bar))))
              (yang ((lambda (foo) (display "*") foo) (call/cc (lambda (bar) bar)))))
    (yin yang))
!#

(define bar (lambda (bar) bar))
(define foox (lambda (foo) (display "@") foo))
(define fooy (lambda (foo) (display "*") foo))
;;((foox bar) (fooy bar))
;;(newline)
;;((call/cc bar) (foox bar))
;;((call/cc bar) (foox (call/cc bar)))
;;(newline)
;;((foox (call/cc bar)) (foox (call/cc bar)))
((foox (call/cc bar)) (fooy (call/cc bar)))
