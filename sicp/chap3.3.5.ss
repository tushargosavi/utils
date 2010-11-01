(define (celsius-farenheit-converter c f)
  (let ((u (make-connector))
	(v (make-connector))
	(w (make-connector))
	(x (make-connector))
	(y (make-connector)))
    (setname! u 'u)
    (setname! v 'v)
    (setname! w 'w)
    (setname! x 'x)
    (setname! y 'y)
    (probe u)
    (probe v)
    (probe w)
    (probe x)
    (probe y)
    (multiplier c w u 'fst-multiplier)
    (multiplier v x u 'snd-multiplier)
    (adder v y f 'adder)
    (constant 9 w)
    (constant 5 x)
    (constant 32 y)
    'ok))

(define (adder a1 a2 sum name)
  (define (process-new-value)
    (cond ((and (has-value? a1) (has-value? a2))
	   (set-value! sum
		       (+ (get-value a1) (get-value a2))
		       me))
	  ((and (has-value? a1) (has-value? sum))
	   (set-value! a2
		       (- (get-value sum) (get-value a1))
		       me))
	  ((and (has-value? a2) (has-value? sum))
	   (set-value! a1
		       (- (get-value sum) (get-value a2))
		       me))))

  (define (process-forget-value)
    (forget-value! sum me)
    (forget-value! a1 me)
    (forget-value! a2 me)
    (process-new-value))

  (define (me request)
    (cond ((eq? request 'I-have-a-value)
	   (process-new-value))
	  ((eq? request 'I-lost-my-value)
	   (process-forget-value))
	  ((eq? request 'name)
	   name)
	  (else
	   (error "Unknown request --ADDER" request))))
  (connect a1 me)
  (connect a2 me)
  (connect sum me)
  me)
	   

(define (inform-about-value c)
  (c 'I-have-a-value))
(define (inform-about-no-value c)
  (c 'I-lost-my-value))

(define (multiplier m1 m2 product name)
  (define (process-new-value)
    (cond ((or (and (has-value? m1) (= (get-value m1) 0))
	       (and (has-value? m2) (= (get-value m2) 0)))
	   (set-value! product 0 me))
	  ((and (has-value? m1) (has-value? m2))
	   (set-value! product
		       (* (get-value m1) (get-value m2))
		       me))
	  ((and (has-value? m1) (has-value? product))
	   (set-value! m2
		       (/ (get-value product) (get-value m1))
		       me))
	  ((and (has-value? m2) (has-value? product))
	   (set-value! m1
		       (/ (get-value product) (get-value m2))
		       me))))

  (define (process-forget-value)
    (forget-value! product me)
    (forget-value! m1 me)
    (forget-value! m2 me)
    (process-new-value))

  (define (me request)
    (cond ((eq? request 'I-have-a-value)
	   (process-new-value))
	  ((eq? request 'I-lost-my-value)
	   (process-forget-value))
	  ((eq? request 'name)
	   name)
	  (else
	   (error "Unknown request --MULTIPLIER" request))))

  (connect m1 me)
  (connect m2 me)
  (connect product me)
  me)

(define (constant value connector)
  (define (me request)
    (if (eq? request 'name)
	'CONST
	(error "Unknown request --- CONSTANT" req)))
  (connect connector me)
  (set-value! connector value me)
  me)

(define (probe connector)
  (define (print-probe value)
    (display "Probe: ")
    (display (getname connector))
    (display "=")
    (display value)
    (newline))

  (define (process-new-value)
    (print-probe (get-value connector)))

  (define (process-forget-value)
    (print-probe "?"))

  (define (me request)
    (cond ((eq? request 'I-have-a-value)
	   (process-new-value))
	  ((eq? request 'I-lost-my-value)
	   (process-forget-value))
	  ((eq? request 'name)
	   'PROBE)
	  (else
	   (error "Unknown request --PROBE" request))))
  (connect connector me)
  me)

(define (make-connector)
  (let ((wirename 'connector) (value #f) (informant #f) (constraints '()))
    (define (set-my-value newval setter)
      (cond ((not (has-value? me))
	     (set! value newval)
	     (set! informant setter)
	     (for-each-except setter
			      inform-about-value
			      constraints))
	    ((not (= value newval))
	     (error "Contradiction " (list value newval)))
	    (else 'ignored)))

    (define (forget-my-value retractor)
      (if (eq? retractor informant)
	  (begin (set! informant #f)
		 (for-each-except retractor
				  inform-about-no-value
				  constraints))
	  'ignored))
    
    (define (connect new-contraint)
      (display "Connecting wire ")
      (display wirename)
      (display " To ")
      (display (getname new-contraint))
      (newline)
      (if (not (memq new-contraint constraints))
	  (set! constraints
		(cons new-contraint constraints)))
      (if (has-value? me)
	  (inform-about-value new-contraint))
      'done)

    (define (setname! name)
      (set! wirename name))

    (define (me request)
      (cond ((eq? request 'has-value?)
	     (if informant #t #f))
	    ((eq? request 'get-value) value)
	    ((eq? request 'set-value!) set-my-value)
	    ((eq? request 'forget-value!) forget-my-value)
	    ((eq? request 'connect) connect)
	    ((eq? request 'setname) setname!)
	    ((eq? request 'name) wirename)
	    (else (error "Unknow operation on connector"
			 request))))
    me))

(define (for-each-except exception procedure list)
  (define (loop items)
    (cond ((null? items)
	   'done)
	  ((eq? (car items) exception)
	   (loop (cdr items)))
	  (else (procedure (car items))
		(loop (cdr items)))))
  (loop list))

;; (define (for-each-except ex proc list)
;;   (if (null? list)
;;       'done
;;       (begin
;; 	(proc (car list))
;; 	(for-each-except ex proc (cdr list)))))

(define (has-value? connector)
  (connector 'has-value?))
(define (get-value connector)
  (connector 'get-value))
(define (set-value! connector new-value informant)
  ((connector 'set-value!) new-value informant))
(define (forget-value! connector retractor)
  ((connector 'forget-value!) retractor))
(define (connect connector new-contraint)
  ((connector 'connect) new-contraint))
(define (setname! connector name)
  ((connector 'setname) name))
(define (getname obj)
  (obj 'name))

(define C (make-connector))
(define F (make-connector))
(setname! C "Celsius temp")
(setname! F "Fe")
(celsius-farenheit-converter C F)
(probe C)
(probe F)
(set-value! C 25 'user)
(forget-value! C 'user)
(set-value! F 212 'user)