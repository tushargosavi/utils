(define (fib x)
  (cond ((= x 0) 1)
	((= x 1) 2)
	(else (+ (fib (- x 1)) (fib (- x 2))))))

(define (append x y)
  (if (null? x)
      y
      (cons (car x) (append (cdr x) y))))


(define (append! x y)
  (set-cdr! (last-pair x) y)
  x)

(define (last-pair x)
  (if (null? (cdr x))
      x
      (last-pair (cdr x))))


(define (inplace-reverse x)
  (define (loop x y)
    (if (null? x)
	y
	(let ((temp (cdr x)))
	  (set-cdr! x y)
	  (loop temp x))))
  (loop x '()))

(define (count-pairs x)
  (if (not (pair? x))
      0
      (+ (count-pairs (car x))
	 (count-pairs (cdr x))
	 1)))

(define (lookup lst elm)
  (cond ((null? lst) #f)
	((eq? elm (car lst)) #t)
	(else (lookup (cdr lst) elm))))

(define (count-pairs1 x)

  (let ((lst '()))
    (define (count x)
      (cond ((not (pair? x)) 0)
	    ((lookup lst x) 0)
	    (else (begin
		    (cons lst x)
		    (+ (count (car x))
		       (count (cdr x))
		       1)))))
    (count x)))


; queue implementation in scheme
; queue is mentained as a cons , car which is a from pointer
; and cdr is the tail pointer.
(define (make-queue) (cons '() '()))

(define (front-ptr queue) (car queue))
(define (rear-ptr queue) (cdr queue))
(define (set-front-ptr! queue item) (set-car! queue item))
(define (set-rear-ptr! queue item) (set-cdr! queue item))

(define (empty-queue? queue) (null? (front-ptr queue)))

(define (front-queue queue)
  (if (empty-queue? queue)
      (error "Front is called on empty queue")
      (car (front-ptr queue))))

(define (insert-queue! queue item)
  (let ((new-pair (cons item '())))
    (cond ((empty-queue? queue)
	   (set-front-ptr! queue new-pair)
	   (set-rear-ptr! queue new-pair)
	   queue)
	  (else
	   (set-cdr! (rear-ptr queue) new-pair)
	   (set-rear-ptr! queue new-pair)
	   queue))))

(define (delete-queue! queue)
  (cond ((empty-queue? queue)
	 (error "DELETE! called with an empty queue"))
	(else
	 (set-front-ptr! queue (cdr (front-ptr queue)))
	 queue)))

	 
(define (print-queue queue)
  (let ((start-ptr (front-ptr queue)))
    (define (print-element x)
      (if (not (null? x))
	  (begin 
	    (display (car x))
	    (display " ")
	    (print-element (cdr x)))
	  (newline)))
    (print-element start-ptr)))


; Solution to 3.22
(define (make-queue-1)
  (let ((queue (cons '() '())))
    
    (define (front-ptr) (car queue))
    (define (rear-ptr) (cdr queue))
    (define (empty?) (null? (front-ptr)))
    (define (set-front-ptr! item)
      (set-car! queue item))
    (define (set-rear-ptr! item)
      (set-cdr! queue item))
    (define (insert! item)
      (let ((new-item (cons item '())))
	(cond ((empty?)
	       (set-front-ptr! new-item)
	       (set-rear-ptr! new-item))
	      (else
	       (set-cdr! (rear-ptr) new-item)
	       (set-rear-ptr! new-item)))))
    (define (delete!)
      (if (empty?)
	  (error "DELETE from empty list")
	  (set-front-ptr! (cdr (front-ptr)))))
    (define (front)
      (if (empty?)
	  (error "FRONT operation called on empty queue")
	  (car (front-ptr))))
    (define (print)
      (let ((start-ptr (front-ptr)))
	(define (print-list x)
	  (if (not (null? x))
	      (begin
		(display (car x))
		(display " ")
		(print-list (cdr x)))
	      (display "\n")))
	(print-list start-ptr)))


    (define (dispatch m)
      (cond ((eq? m 'insert) insert!)
	    ((eq? m 'delete) delete!)
	    ((eq? m 'empty?) empty?)
	    ((eq? m 'front) front)
	    ((eq? m 'print) print)
	    (else (display queue)
		  (error "Invalid operation on queue"))))

    dispatch))

