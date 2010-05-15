(define (square x) (* x x))
(define (sqrt1 x) (sqrt-guess 1 x))
(define (sqrt-guess guess x)
  (if (good-enough? guess x)
      guess
      (sqrt-guess (improve guess x) x)))
(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 0.0001))
(define (improve guess x)
  (average guess (/ x guess)))
(define (average x y) (/ (+ x y) 2))

(define (factorial x)
  (if (= x 1)
      1
      (* x (factorial (- x 1)))))
(define (fact1 x) (fact-iter 1 x))
(define (fact-iter prod x)
  (if (= x 1)
      prod
      (fact-iter (* prod x) (- x 1))))

(define (A x y)
  (cond ((= y 0) 0)
        ((= x  0) (* 2 y))
        ((= y 1) 2)
        (else (A (- x 1)
                 (A x (- y 1))))))

(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1)) (fib (- n 2))))))

(define (fib1 n) (fib-iter 0 1 n))
(define (fib-iter a b count)
  (if (= count 0)
      a
      (fib-iter b (+ a b) (- count 1))))

(define (count-change amount)
  (cc amount 5))
(define (cc amount kind-of-coins)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (= kind-of-coins 0)) 0)
        (else (+ (cc amount (- kind-of-coins 1))
                 (cc (- amount (value kind-of-coins)) kind-of-coins)))))
(define (value type)
  (cond ((= type 1) 1)
        ((= type 2) 5)
        ((= type 3) 10)
        ((= type 4) 25)
        ((= type 5) 50)))

(define (func1 n)
  (if (< n 3)
      n
      (+ (func1 (- n 1))
         (* 2 (func1 (- n 2)))
         (* 3 (func1 (- n 3))))))

               
(define (func2 n)
  (func-iter 4 0 1 2 n))
  
 (define (func-iter sum a b c n)
   (cond ((= n 0) a)     
         ((= n 1) b)
         ((= n 2) c)
         (else (func-iter (+ c (* 2 b) (* 3 a)) b c sum (- n 1)))))
  
         
         
(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a) (sum term (next a) next b))))

(define (sum-of-integers a b)
  (define (id x) x)
  (define (succ x) (+ x 1))
  (sum id a succ b))

(define (zero-search func neg pos)
  (define (close-enough? x y)
    (< (abs (- x y)) 0.0001))
  (let ((midpoint (/ (+ neg pos) 2)))
    (if (close-enough? neg pos)
	midpoint
	(let ((test-value (func midpoint)))
	  (cond ((positive? test-value) (zero-search func neg midpoint))
		((negative? test-value) (zero-search func midpoint pos))
		(else midpoint))))))

(define (half-interval-method func a b)
  (let ((a-value (func a))
	(b-value (func b)))
    (cond ((and (negative? a-value) (positive? b-value))
	   (zero-search func a b))
	   ((and (negative? b-value) (positive? a-value))
	   (zero-search func b a))
	   (else 
	    (error "Values are not of opposite sign")))))

	   
(define (fix-point func guess)
  (define (close-enough? x y)
    (< (abs (- x y)) 0.00001))
  (define (try guess)
    (let ((next (func guess)))
      (if (close-enough? guess next)
	  next
	  (try next))))
  (try guess))


; CHAP 2
(define (make-interval a b) (cons a b))
(define (lower-bound x) (if (> (car x) (cdr x)) (cdr x) (car x)))
(define (upper-bound x) (if (> (car x) (cdr x)) (car x) (cdr x)))
(define (add-interval x y)
  (make-interval 
   (+ (lower-bound x) (lower-bound y))
   (+ (upper-bound x) (upper-bound y))))

(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
	(p2 (* (lower-bound x) (upper-bound y)))
	(p3 (* (upper-bound x) (lower-bound y)))
	(p4 (* (upper-bound x) (lower-bound y))))
    (make-interval (min p1 p2 p3 p4) (max p1 p2 p3 p4))))

(define (div-interval x y)
  (if (and (< (lower-bound y) 0) (> (upper-bound y) 0))
      (error "Division by interval spanig zero")
      (mult-interval x 
		     (make-interval (/ 1.0 (upper-bound y))
				    (/ 1.0 (lower-bound y))))))

(define (sub-interval x y)
  (let ((p1 (- (lower-bound x) (upper-bound y)))
	(p2 (- (upper-bound x) (lower-bound y))))
    (make-interval p1 p2)))

(define (interval-width x)
  (/ (- (upper-bound x) (lower-bound x)) 2))


(define (make-center-width c w)
  (make-interval (- c w) (+ c w)))
(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))

(define (make-center-percent x p)
  (let ((width (/ (* p x) 100.0)))
    (make-center-width x width)))
(define (percent i)
  (/ (* 100.0 (interval-width i)) (center i)))

(define (list-ref items n)
  (if (= n 0)
      (car items)
      (list-ref (cdr items) (- n 1))))

(define (length items)
  (if (null? items)
      0
      (+ 1 (length (cdr items)))))

(define (length1 items)
  (define (l-iter count items)
    (if (null? items)
	count
	(l-iter (+ count 1) (cdr items))))
  (l-iter 0 items))

(define (append list1 list2)
  (if (null? list1)
      list2
      (cons (car list1) (append (cdr list1) list2))))

(define (last-pair l)
  (if (null? (cdr l))
      (car l)
      (last-pair (cdr l))))

(define (reverse l)
  (if (null? l)
      l
      (append (reverse (cdr l)) (list (car l)))))


(define (cc amount coin-values)
  (cond ((= amount 0) 1)
	((or (< amount 0) (no-more? coin-values)) 0)
	(else
	 (+ (cc amount (except-first-demonination coin-values))
	    (cc (- amount (first-demonination coin-values))
		coin-values)))))

(define (no-more? l) (null? l))
(define (except-first-demonination l) (cdr l))
(define (first-demonination l) (car l))

(define (same-parity . nums)Ã¶Ã
  (let ((parity (remainder (car nums) 2)))
    (define (iter l)
      (cond ((null? l) ())
	    ((= (remainder (car l) 2) parity)
	     (cons (car l) (iter (cdr l))))
	    (else (iter (cdr l)))))
    (cons (car nums) (iter (cdr nums)))))

(define (square-list items)
  (if (null? items)
      ()
      (cons (* (car items) (car items)) (square-list (cdr items)))))

(define (maped-square-list items)
  (map (lambda (x) (* x x)) items))


(define (square-list items)
  (define (iter things answer)
    (if (null? things)
        answer
        (iter (cdr things)
              (cons answer
                    (square (car things))))))
  (iter items ()))

(define (for-each func item)
  (if (null? (cdr item))
      (func (car item))
      ((func (car item)) (for-each func (cdr item)))))


; Hirarchical Structures
(define (count-leaves tree)
  (cond ((null? tree) 0)
	((not (pair? tree)) 1)
	(else
	 (+ (count-leaves (car tree))
	    (count-leaves (cdr tree))))))


(define (deep-reverse l)
  (if (null? l)
      ()
      (append (deep-reverse (cdr l))
	      (if (pair? (car l))
		  (list (reverse (car l)))
		  (list (car l))))))

;; working fine
(define (fringe x)
  (cond ((null? x) ())
	((not (pair? x)) (cons x ()))
	(else (append (fringe (car x)) (fringe (cdr x))))))

;; 
(define (square-tree tree)
  (cond ((null? tree) ())
	((not (pair? tree)) (square tree))
	(else (cons (square-tree (car tree))
		    (square-tree (cdr tree))))))

(define (square-tree1 tree)
  (map (lambda (t)
       (if (pair? t)
	   (square-tree1 t)
	   (square t)))
       tree))

(define (tree-map func tree)
  (cond ((null? tree) ())
	((not (pair? tree)) (func tree))
	(else (cons (tree-map func (car tree))
		    (tree-map func (cdr tree))))))
(define (square-tree2 tree) (tree-map square tree))

(define (filter predicate sequence)
  (cond ((null? sequence) ())
	((predicate (car sequence))
	 (cons (car sequence)
	       (filter predicate (cdr sequence))))
	(else (filter predicate (cdr sequence)))))


(define (accumulate op initial seq)
  (if (null? seq)
      initial
      (op (car seq)
	  (accumulate op initial (cdr seq)))))

	
(define (my-map p seq)
  (accumulate (lambda (x y) (cons (p x) y)) () seq))

(define (my-append seq1 seq2)
  (accumulate cons seq2 seq1))
 
(define (my-length seq)
  (accumulate (lambda (x y) (+ 1 y)) 0 seq)) 

;; evaluate an polynomial
;; SICP Exercise 2.34
(define (horner-eval x seq)
  (accumulate (lambda (this-coeff higher-terms)
		(+ this-coeff (* x higher-terms)))
	      0
	      seq))

;; not working
(define (count-leaves tree)
  (accumulate (lambda (x y) (append x y))
	      ()
	      (map list tree)))

;; car list also can be implement by using map in scheme
;; (car (map list seq))
(define (carlist seq)
  (if (null? seq)
      ()
      (cons (car (car seq)) (carlist (cdr seq)))))
 
;; cdr list also cab ne implemented using map function
;; (cdr (map list seq))
(define (cdrlist seq)
  (if (null? seq)
      ()
      (cons (cdr (car seq)) (cdrlist (cdr seq)))))

; Exersice 2.35, working :)
(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      ()
      (cons (accumulate op init (carlist seqs))
	    (accumulate-n op init (cdrlist seqs)))))

;; zip-with is not required on scheme because 
;; map can work with two lists and a operator
;; which works as a zip-with function in haskell.
(define (zip-with op v w)
  (if (null? v)
      ()
      (cons (op (car v) (car w)) (zip-with op (cdr v) (cdr w)))))

(define (list-elem lst n)
  (if (= n 0)
      (car lst)
      (list-elem (cdr lst) (- n 1))))


; Matrix operation , Exersice 2.37
(define (dot-product v w)
  (accumulate + 0 (zip-with * v w)))

(define (mat-vector m v)
  (map (lambda (x) (dot-product v x))
       m))

(define (transpose mat)
  (accumulate-n cons () mat))

(define (mat-mult m n)
  (let ((cols (transpose n)))
    (map (lambda (x) (mat-vector cols x)) m)))


;; SICP exercise 2.38. Woking :)
(define (fold-left op initial seq)
  (define (iter result rest)
    (if (null? rest)
	result
	(iter (op result (car rest))
	      (cdr rest))))
  (iter initial seq))

;; SIPC excercise 2.39
(define (foldr-reverse seq)
  (fold-right (lambda (x y) (append y (list x)))
	      () seq))

(define (foldl-reverse seq)
  (fold-left (lambda (x y) (cons y x))
	     ()
	     seq))

;; next section of prime number can be written in haskell like
;;  filter (\(a,b) -> ([] == [k | k <- [2 .. (div (a+b) 2)], (mod (a+b) k) == 0])) [ (i,j) | i <- [1..100], j <- [1..i]]
;; for 100 numbers.
;; Next section Nested Mappings.

(define (enumarate-interval start end)
  (if  (> start end)
      ()
      (cons start (enumarate-interval (+ 1 start) end))))

(define (makeabc n)
  (accumulate append
	      ()
	      (map (lambda (i)
		     (map (lambda (j) (list i j))
			  (enumarate-interval 1 (- i 1))))
		     (enumarate-interval 1 n))))

(define (flatmap proc seq)
  (accumulate append () (map proc seq)))

(define (prime-sum? pair)
  (prime? (+ (car pair) (cdr pair))))

(define (make-pair-sum pair)
  (list (car pair) (cdr pair) (+ (car pair) (cdr pair))))

(define (prime-sum-pairs n)
  (map make-pair-sum
       (filter prime-sum?
	       (makeabc n))))


(define (permutations s)
  (if (null? s)
      (list ())
      (flatmap (lambda (x)
		 (map (lambda (p) (cons x p))
		      (permutations (remove x s))))
	       s)))

(define (remove x seq)
  (filter (lambda (e) (not (= x e))) seq))

;; Exercise 2.40
(define (uniq-pairs n)
  (flatmap (lambda (i)
	     (map (lambda (j) (list i j))
		  (enumarate-interval 1 (- i 1))))
	   (enumarate-interval 1 n)))


;; Exercise 2.41
(define (uniq-triple n)
  (flatmap (lambda (i)
	     (map (lambda (j)
		    (map (lambda (k) (list i j k))
			 (enumarate-interval 1 (- j 1))))
		    (enumarate-interval 1 (- i 1))))
	     (enumarate-interval 1 n)))
