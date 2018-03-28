;; Auto-generated. Do not edit!


(when (boundp 'vicon_xb::viconXbSrv)
  (if (not (find-package "VICON_XB"))
    (make-package "VICON_XB"))
  (shadow 'viconXbSrv (find-package "VICON_XB")))
(unless (find-package "VICON_XB::VICONXBSRV")
  (make-package "VICON_XB::VICONXBSRV"))
(unless (find-package "VICON_XB::VICONXBSRVREQUEST")
  (make-package "VICON_XB::VICONXBSRVREQUEST"))
(unless (find-package "VICON_XB::VICONXBSRVRESPONSE")
  (make-package "VICON_XB::VICONXBSRVRESPONSE"))

(in-package "ROS")





(defclass vicon_xb::viconXbSrvRequest
  :super ros::object
  :slots (_block _logfile_idx ))

(defmethod vicon_xb::viconXbSrvRequest
  (:init
   (&key
    ((:block __block) nil)
    ((:logfile_idx __logfile_idx) 0)
    )
   (send-super :init)
   (setq _block __block)
   (setq _logfile_idx (round __logfile_idx))
   self)
  (:block
   (&optional __block)
   (if __block (setq _block __block)) _block)
  (:logfile_idx
   (&optional __logfile_idx)
   (if __logfile_idx (setq _logfile_idx __logfile_idx)) _logfile_idx)
  (:serialization-length
   ()
   (+
    ;; bool _block
    1
    ;; int32 _logfile_idx
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _block
       (if _block (write-byte -1 s) (write-byte 0 s))
     ;; int32 _logfile_idx
       (write-long _logfile_idx s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _block
     (setq _block (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int32 _logfile_idx
     (setq _logfile_idx (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass vicon_xb::viconXbSrvResponse
  :super ros::object
  :slots (_result ))

(defmethod vicon_xb::viconXbSrvResponse
  (:init
   (&key
    ((:result __result) 0)
    )
   (send-super :init)
   (setq _result (round __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; uint8 _result
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _result
       (write-byte _result s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _result
     (setq _result (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass vicon_xb::viconXbSrv
  :super ros::object
  :slots ())

(setf (get vicon_xb::viconXbSrv :md5sum-) "690ec01b63ec02305afae8d102907248")
(setf (get vicon_xb::viconXbSrv :datatype-) "vicon_xb/viconXbSrv")
(setf (get vicon_xb::viconXbSrv :request) vicon_xb::viconXbSrvRequest)
(setf (get vicon_xb::viconXbSrv :response) vicon_xb::viconXbSrvResponse)

(defmethod vicon_xb::viconXbSrvRequest
  (:response () (instance vicon_xb::viconXbSrvResponse :init)))

(setf (get vicon_xb::viconXbSrvRequest :md5sum-) "690ec01b63ec02305afae8d102907248")
(setf (get vicon_xb::viconXbSrvRequest :datatype-) "vicon_xb/viconXbSrvRequest")
(setf (get vicon_xb::viconXbSrvRequest :definition-)
      "bool block
int32 logfile_idx
---
uint8 result

")

(setf (get vicon_xb::viconXbSrvResponse :md5sum-) "690ec01b63ec02305afae8d102907248")
(setf (get vicon_xb::viconXbSrvResponse :datatype-) "vicon_xb/viconXbSrvResponse")
(setf (get vicon_xb::viconXbSrvResponse :definition-)
      "bool block
int32 logfile_idx
---
uint8 result

")



(provide :vicon_xb/viconXbSrv "690ec01b63ec02305afae8d102907248")


