; Auto-generated. Do not edit!


(cl:in-package vicon_xb-srv)


;//! \htmlinclude viconXbSrv-request.msg.html

(cl:defclass <viconXbSrv-request> (roslisp-msg-protocol:ros-message)
  ((block
    :reader block
    :initarg :block
    :type cl:boolean
    :initform cl:nil)
   (logfile_idx
    :reader logfile_idx
    :initarg :logfile_idx
    :type cl:integer
    :initform 0))
)

(cl:defclass viconXbSrv-request (<viconXbSrv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <viconXbSrv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'viconXbSrv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vicon_xb-srv:<viconXbSrv-request> is deprecated: use vicon_xb-srv:viconXbSrv-request instead.")))

(cl:ensure-generic-function 'block-val :lambda-list '(m))
(cl:defmethod block-val ((m <viconXbSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vicon_xb-srv:block-val is deprecated.  Use vicon_xb-srv:block instead.")
  (block m))

(cl:ensure-generic-function 'logfile_idx-val :lambda-list '(m))
(cl:defmethod logfile_idx-val ((m <viconXbSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vicon_xb-srv:logfile_idx-val is deprecated.  Use vicon_xb-srv:logfile_idx instead.")
  (logfile_idx m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <viconXbSrv-request>) ostream)
  "Serializes a message object of type '<viconXbSrv-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'block) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'logfile_idx)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <viconXbSrv-request>) istream)
  "Deserializes a message object of type '<viconXbSrv-request>"
    (cl:setf (cl:slot-value msg 'block) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'logfile_idx) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<viconXbSrv-request>)))
  "Returns string type for a service object of type '<viconXbSrv-request>"
  "vicon_xb/viconXbSrvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'viconXbSrv-request)))
  "Returns string type for a service object of type 'viconXbSrv-request"
  "vicon_xb/viconXbSrvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<viconXbSrv-request>)))
  "Returns md5sum for a message object of type '<viconXbSrv-request>"
  "690ec01b63ec02305afae8d102907248")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'viconXbSrv-request)))
  "Returns md5sum for a message object of type 'viconXbSrv-request"
  "690ec01b63ec02305afae8d102907248")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<viconXbSrv-request>)))
  "Returns full string definition for message of type '<viconXbSrv-request>"
  (cl:format cl:nil "bool block~%int32 logfile_idx~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'viconXbSrv-request)))
  "Returns full string definition for message of type 'viconXbSrv-request"
  (cl:format cl:nil "bool block~%int32 logfile_idx~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <viconXbSrv-request>))
  (cl:+ 0
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <viconXbSrv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'viconXbSrv-request
    (cl:cons ':block (block msg))
    (cl:cons ':logfile_idx (logfile_idx msg))
))
;//! \htmlinclude viconXbSrv-response.msg.html

(cl:defclass <viconXbSrv-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:fixnum
    :initform 0))
)

(cl:defclass viconXbSrv-response (<viconXbSrv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <viconXbSrv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'viconXbSrv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vicon_xb-srv:<viconXbSrv-response> is deprecated: use vicon_xb-srv:viconXbSrv-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <viconXbSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vicon_xb-srv:result-val is deprecated.  Use vicon_xb-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <viconXbSrv-response>) ostream)
  "Serializes a message object of type '<viconXbSrv-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <viconXbSrv-response>) istream)
  "Deserializes a message object of type '<viconXbSrv-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<viconXbSrv-response>)))
  "Returns string type for a service object of type '<viconXbSrv-response>"
  "vicon_xb/viconXbSrvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'viconXbSrv-response)))
  "Returns string type for a service object of type 'viconXbSrv-response"
  "vicon_xb/viconXbSrvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<viconXbSrv-response>)))
  "Returns md5sum for a message object of type '<viconXbSrv-response>"
  "690ec01b63ec02305afae8d102907248")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'viconXbSrv-response)))
  "Returns md5sum for a message object of type 'viconXbSrv-response"
  "690ec01b63ec02305afae8d102907248")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<viconXbSrv-response>)))
  "Returns full string definition for message of type '<viconXbSrv-response>"
  (cl:format cl:nil "uint8 result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'viconXbSrv-response)))
  "Returns full string definition for message of type 'viconXbSrv-response"
  (cl:format cl:nil "uint8 result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <viconXbSrv-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <viconXbSrv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'viconXbSrv-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'viconXbSrv)))
  'viconXbSrv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'viconXbSrv)))
  'viconXbSrv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'viconXbSrv)))
  "Returns string type for a service object of type '<viconXbSrv>"
  "vicon_xb/viconXbSrv")