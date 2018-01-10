; Auto-generated. Do not edit!


(cl:in-package axon_link-msg)


;//! \htmlinclude Taobot.msg.html

(cl:defclass <Taobot> (roslisp-msg-protocol:ros-message)
  ((motorA_encoder
    :reader motorA_encoder
    :initarg :motorA_encoder
    :type cl:fixnum
    :initform 0)
   (motorA_dir
    :reader motorA_dir
    :initarg :motorA_dir
    :type cl:fixnum
    :initform 0)
   (motorB_encoder
    :reader motorB_encoder
    :initarg :motorB_encoder
    :type cl:fixnum
    :initform 0)
   (motorB_dir
    :reader motorB_dir
    :initarg :motorB_dir
    :type cl:fixnum
    :initform 0)
   (motorC_encoder
    :reader motorC_encoder
    :initarg :motorC_encoder
    :type cl:fixnum
    :initform 0)
   (motorC_dir
    :reader motorC_dir
    :initarg :motorC_dir
    :type cl:fixnum
    :initform 0)
   (voltage
    :reader voltage
    :initarg :voltage
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Taobot (<Taobot>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Taobot>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Taobot)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name axon_link-msg:<Taobot> is deprecated: use axon_link-msg:Taobot instead.")))

(cl:ensure-generic-function 'motorA_encoder-val :lambda-list '(m))
(cl:defmethod motorA_encoder-val ((m <Taobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader axon_link-msg:motorA_encoder-val is deprecated.  Use axon_link-msg:motorA_encoder instead.")
  (motorA_encoder m))

(cl:ensure-generic-function 'motorA_dir-val :lambda-list '(m))
(cl:defmethod motorA_dir-val ((m <Taobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader axon_link-msg:motorA_dir-val is deprecated.  Use axon_link-msg:motorA_dir instead.")
  (motorA_dir m))

(cl:ensure-generic-function 'motorB_encoder-val :lambda-list '(m))
(cl:defmethod motorB_encoder-val ((m <Taobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader axon_link-msg:motorB_encoder-val is deprecated.  Use axon_link-msg:motorB_encoder instead.")
  (motorB_encoder m))

(cl:ensure-generic-function 'motorB_dir-val :lambda-list '(m))
(cl:defmethod motorB_dir-val ((m <Taobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader axon_link-msg:motorB_dir-val is deprecated.  Use axon_link-msg:motorB_dir instead.")
  (motorB_dir m))

(cl:ensure-generic-function 'motorC_encoder-val :lambda-list '(m))
(cl:defmethod motorC_encoder-val ((m <Taobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader axon_link-msg:motorC_encoder-val is deprecated.  Use axon_link-msg:motorC_encoder instead.")
  (motorC_encoder m))

(cl:ensure-generic-function 'motorC_dir-val :lambda-list '(m))
(cl:defmethod motorC_dir-val ((m <Taobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader axon_link-msg:motorC_dir-val is deprecated.  Use axon_link-msg:motorC_dir instead.")
  (motorC_dir m))

(cl:ensure-generic-function 'voltage-val :lambda-list '(m))
(cl:defmethod voltage-val ((m <Taobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader axon_link-msg:voltage-val is deprecated.  Use axon_link-msg:voltage instead.")
  (voltage m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Taobot>) ostream)
  "Serializes a message object of type '<Taobot>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorA_encoder)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorA_dir)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorB_encoder)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorB_dir)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorC_encoder)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorC_dir)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'voltage)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Taobot>) istream)
  "Deserializes a message object of type '<Taobot>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorA_encoder)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorA_dir)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorB_encoder)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorB_dir)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorC_encoder)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motorC_dir)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'voltage)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Taobot>)))
  "Returns string type for a message object of type '<Taobot>"
  "axon_link/Taobot")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Taobot)))
  "Returns string type for a message object of type 'Taobot"
  "axon_link/Taobot")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Taobot>)))
  "Returns md5sum for a message object of type '<Taobot>"
  "7d650a23fc1ea1941c14405910e8d823")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Taobot)))
  "Returns md5sum for a message object of type 'Taobot"
  "7d650a23fc1ea1941c14405910e8d823")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Taobot>)))
  "Returns full string definition for message of type '<Taobot>"
  (cl:format cl:nil "uint8 motorA_encoder~%uint8 motorA_dir~%uint8 motorB_encoder~%uint8 motorB_dir~%uint8 motorC_encoder~%uint8 motorC_dir~%uint8 voltage~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Taobot)))
  "Returns full string definition for message of type 'Taobot"
  (cl:format cl:nil "uint8 motorA_encoder~%uint8 motorA_dir~%uint8 motorB_encoder~%uint8 motorB_dir~%uint8 motorC_encoder~%uint8 motorC_dir~%uint8 voltage~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Taobot>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Taobot>))
  "Converts a ROS message object to a list"
  (cl:list 'Taobot
    (cl:cons ':motorA_encoder (motorA_encoder msg))
    (cl:cons ':motorA_dir (motorA_dir msg))
    (cl:cons ':motorB_encoder (motorB_encoder msg))
    (cl:cons ':motorB_dir (motorB_dir msg))
    (cl:cons ':motorC_encoder (motorC_encoder msg))
    (cl:cons ':motorC_dir (motorC_dir msg))
    (cl:cons ':voltage (voltage msg))
))
