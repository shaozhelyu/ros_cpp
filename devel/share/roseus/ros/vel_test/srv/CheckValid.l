;; Auto-generated. Do not edit!


(when (boundp 'vel_test::CheckValid)
  (if (not (find-package "VEL_TEST"))
    (make-package "VEL_TEST"))
  (shadow 'CheckValid (find-package "VEL_TEST")))
(unless (find-package "VEL_TEST::CHECKVALID")
  (make-package "VEL_TEST::CHECKVALID"))
(unless (find-package "VEL_TEST::CHECKVALIDREQUEST")
  (make-package "VEL_TEST::CHECKVALIDREQUEST"))
(unless (find-package "VEL_TEST::CHECKVALIDRESPONSE")
  (make-package "VEL_TEST::CHECKVALIDRESPONSE"))

(in-package "ROS")





(defclass vel_test::CheckValidRequest
  :super ros::object
  :slots (_x _y ))

(defmethod vel_test::CheckValidRequest
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass vel_test::CheckValidResponse
  :super ros::object
  :slots (_status ))

(defmethod vel_test::CheckValidResponse
  (:init
   (&key
    ((:status __status) 0)
    )
   (send-super :init)
   (setq _status (round __status))
   self)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:serialization-length
   ()
   (+
    ;; int8 _status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _status
       (write-byte _status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _status
     (setq _status (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _status 127) (setq _status (- _status 256)))
   ;;
   self)
  )

(defclass vel_test::CheckValid
  :super ros::object
  :slots ())

(setf (get vel_test::CheckValid :md5sum-) "ffe373b808a90218f6a495ef5089335a")
(setf (get vel_test::CheckValid :datatype-) "vel_test/CheckValid")
(setf (get vel_test::CheckValid :request) vel_test::CheckValidRequest)
(setf (get vel_test::CheckValid :response) vel_test::CheckValidResponse)

(defmethod vel_test::CheckValidRequest
  (:response () (instance vel_test::CheckValidResponse :init)))

(setf (get vel_test::CheckValidRequest :md5sum-) "ffe373b808a90218f6a495ef5089335a")
(setf (get vel_test::CheckValidRequest :datatype-) "vel_test/CheckValidRequest")
(setf (get vel_test::CheckValidRequest :definition-)
      "float32 x
float32 y
---
int8 status
")

(setf (get vel_test::CheckValidResponse :md5sum-) "ffe373b808a90218f6a495ef5089335a")
(setf (get vel_test::CheckValidResponse :datatype-) "vel_test/CheckValidResponse")
(setf (get vel_test::CheckValidResponse :definition-)
      "float32 x
float32 y
---
int8 status
")



(provide :vel_test/CheckValid "ffe373b808a90218f6a495ef5089335a")


