;; define lists a and b
(defparameter a-list '((1 0 -2 3)
                       (5 -1 1 0)
                       (3 0 -2 1)
                       (0 3 1 2)))

(defparameter b-list '(7.5
                       1
                       6.5
                       -1.5))

(defun lu-decomp (A)
  (let* ((n (length A))
         (A (make-array `(,n ,n) :element-type 'float :initial-contents A))
         (L (make-array `(,n ,n) :initial-element 0))
         (U (make-array `(,n ,n) :initial-element 0)))

    (loop for k from 0 to (- n 1) do
         (loop for i from k to (- n 1) do
              ;; L
              (setf (aref L i k)
                    (- (aref A i k)
                       (loop for m from 0 to (- k 1)
                          sum (* (aref L i m)
                                 (aref U m k)))))
              ;; U
              (setf (aref U k i)
                    (/
                     (- (aref A k i)
                        (loop for m from 0 to (- k 1)
                           sum (* (aref L k m)
                                  (aref U m i))))
                     (aref L k k)))))
    ;; 多値評価
    (values L U)))

(defun solve-matrix (L U b)
  (let* ((n (length b))
         (b (make-array `(,n) :element-type 'float :initial-contents b))
         (x (make-array `(,n) :initial-element 0))
         (y (make-array `(,n) :initial-element 0)))

    ;; 前進代入
    (loop for k from 0 to (- n 1) do
         (setf (aref y k)
               (/
                (- (aref b k)
                   (loop for m from 0 to k
                      sum (* (aref L k m)
                             (aref y m))))
                (aref L k k))))
    
    ;; 後退代入
    (loop for k downfrom (- n 1) to 0 do
         (setf (aref x k)
               (- (aref y k)
                  (loop for m from k to (- n 1)
                     sum (* (aref U k m)
                            (aref x m))))))
    ;; 多値評価
    (values x y)))

;; 分解過程
(lu-decomp a-list)
;; 解x,y (多値受取:multiple-value-call)
(multiple-value-call #'solve-matrix (lu-decomp a-list) b-list)
