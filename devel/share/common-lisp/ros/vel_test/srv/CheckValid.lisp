; Auto-generated. Do not edit!


(cl:in-package vel_test-srv)


;//! \htmlinclude CheckValid-request.msg.html

(cl:defclass <CheckValid-request> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0))
)

(cl:defclass CheckValid-request (<CheckValid-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CheckValid-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CheckValid-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vel_test-srv:<CheckValid-request> is deprecated: use vel_test-srv:CheckValid-request instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <CheckValid-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vel_test-srv:x-val is deprecated.  Use vel_test-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <CheckValid-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vel_test-srv:y-val is deprecated.  Use vel_test-srv:y instead.")
  (y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CheckValid-request>) ostream)
  "Serializes a message object of type '<CheckValid-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CheckValid-request>) istream)
  "Deserializes a message object of type '<CheckValid-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CheckValid-request>)))
  "Returns string type for a service object of type '<CheckValid-request>"
  "vel_test/CheckValidRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CheckValid-request)))
  "Returns string type for a service object of type 'CheckValid-request"
  "vel_test/CheckValidRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CheckValid-request>)))
  "Returns md5sum for a message object of type '<CheckValid-request>"
  "ffe373b808a90218f6a495ef5089335a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CheckValid-request)))
  "Returns md5sum for a message object of type 'CheckValid-request"
  "ffe373b808a90218f6a495ef5089335a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CheckValid-request>)))
  "Returns full string definition for message of type '<CheckValid-request>"
  (cl:format cl:nil "float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CheckValid-request)))
  "Returns full string definition for message of type 'CheckValid-request"
  (cl:format cl:nil "float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CheckValid-request>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CheckValid-request>))
  "Converts a ROS message object to a list"
  (cl:list 'CheckValid-request
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
))
;//! \htmlinclude CheckValid-response.msg.html

(cl:defclass <CheckValid-response> (roslisp-msg-protocol:ros-message)
  ((status
    :reader status
    :initarg :status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass CheckValid-response (<CheckValid-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CheckValid-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CheckValid-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vel_test-srv:<CheckValid-response> is deprecated: use vel_test-srv:CheckValid-response instead.")))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <CheckValid-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vel_test-srv:status-val is deprecated.  Use vel_test-srv:status instead.")
  (status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CheckValid-response>) ostream)
  "Serializes a message object of type '<CheckValid-response>"
  (cl:let* ((signed (cl:slot-value msg 'status)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CheckValid-response>) istream)
  "Deserializes a message object of type '<CheckValid-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'status) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CheckValid-response>)))
  "Returns string type for a service object of type '<CheckValid-response>"
  "vel_test/CheckValidResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CheckValid-response)))
  "Returns string type for a service object of type 'CheckValid-response"
  "vel_test/CheckValidResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CheckValid-response>)))
  "Returns md5sum for a message object of type '<CheckValid-response>"
  "ffe373b808a90218f6a495ef5089335a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CheckValid-response)))
  "Returns md5sum for a message object of type 'CheckValid-response"
  "ffe373b808a90218f6a495ef5089335a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CheckValid-response>)))
  "Returns full string definition for message of type '<CheckValid-response>"
  (cl:format cl:nil "int8 status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CheckValid-response)))
  "Returns full string definition for message of type 'CheckValid-response"
  (cl:format cl:nil "int8 status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CheckValid-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CheckValid-response>))
  "Converts a ROS message object to a list"
  (cl:list 'CheckValid-response
    (cl:cons ':status (status msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'CheckValid)))
  'CheckValid-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'CheckValid)))
  'CheckValid-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CheckValid)))
  "Returns string type for a service object of type '<CheckValid>"
  "vel_test/CheckValid")