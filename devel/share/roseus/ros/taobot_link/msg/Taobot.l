;; Auto-generated. Do not edit!


(when (boundp 'taobot_link::Taobot)
  (if (not (find-package "TAOBOT_LINK"))
    (make-package "TAOBOT_LINK"))
  (shadow 'Taobot (find-package "TAOBOT_LINK")))
(unless (find-package "TAOBOT_LINK::TAOBOT")
  (make-package "TAOBOT_LINK::TAOBOT"))

(in-package "ROS")
;;//! \htmlinclude Taobot.msg.html


(defclass taobot_link::Taobot
  :super ros::object
  :slots (_motorA_encoder _motorA_dir _motorB_encoder _motorB_dir _motorC_encoder _motorC_dir _voltage ))

(defmethod taobot_link::Taobot
  (:init
   (&key
    ((:motorA_encoder __motorA_encoder) 0)
    ((:motorA_dir __motorA_dir) 0)
    ((:motorB_encoder __motorB_encoder) 0)
    ((:motorB_dir __motorB_dir) 0)
    ((:motorC_encoder __motorC_encoder) 0)
    ((:motorC_dir __motorC_dir) 0)
    ((:voltage __voltage) 0)
    )
   (send-super :init)
   (setq _motorA_encoder (round __motorA_encoder))
   (setq _motorA_dir (round __motorA_dir))
   (setq _motorB_encoder (round __motorB_encoder))
   (setq _motorB_dir (round __motorB_dir))
   (setq _motorC_encoder (round __motorC_encoder))
   (setq _motorC_dir (round __motorC_dir))
   (setq _voltage (round __voltage))
   self)
  (:motorA_encoder
   (&optional __motorA_encoder)
   (if __motorA_encoder (setq _motorA_encoder __motorA_encoder)) _motorA_encoder)
  (:motorA_dir
   (&optional __motorA_dir)
   (if __motorA_dir (setq _motorA_dir __motorA_dir)) _motorA_dir)
  (:motorB_encoder
   (&optional __motorB_encoder)
   (if __motorB_encoder (setq _motorB_encoder __motorB_encoder)) _motorB_encoder)
  (:motorB_dir
   (&optional __motorB_dir)
   (if __motorB_dir (setq _motorB_dir __motorB_dir)) _motorB_dir)
  (:motorC_encoder
   (&optional __motorC_encoder)
   (if __motorC_encoder (setq _motorC_encoder __motorC_encoder)) _motorC_encoder)
  (:motorC_dir
   (&optional __motorC_dir)
   (if __motorC_dir (setq _motorC_dir __motorC_dir)) _motorC_dir)
  (:voltage
   (&optional __voltage)
   (if __voltage (setq _voltage __voltage)) _voltage)
  (:serialization-length
   ()
   (+
    ;; uint8 _motorA_encoder
    1
    ;; uint8 _motorA_dir
    1
    ;; uint8 _motorB_encoder
    1
    ;; uint8 _motorB_dir
    1
    ;; uint8 _motorC_encoder
    1
    ;; uint8 _motorC_dir
    1
    ;; uint8 _voltage
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _motorA_encoder
       (write-byte _motorA_encoder s)
     ;; uint8 _motorA_dir
       (write-byte _motorA_dir s)
     ;; uint8 _motorB_encoder
       (write-byte _motorB_encoder s)
     ;; uint8 _motorB_dir
       (write-byte _motorB_dir s)
     ;; uint8 _motorC_encoder
       (write-byte _motorC_encoder s)
     ;; uint8 _motorC_dir
       (write-byte _motorC_dir s)
     ;; uint8 _voltage
       (write-byte _voltage s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _motorA_encoder
     (setq _motorA_encoder (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _motorA_dir
     (setq _motorA_dir (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _motorB_encoder
     (setq _motorB_encoder (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _motorB_dir
     (setq _motorB_dir (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _motorC_encoder
     (setq _motorC_encoder (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _motorC_dir
     (setq _motorC_dir (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _voltage
     (setq _voltage (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get taobot_link::Taobot :md5sum-) "7d650a23fc1ea1941c14405910e8d823")
(setf (get taobot_link::Taobot :datatype-) "taobot_link/Taobot")
(setf (get taobot_link::Taobot :definition-)
      "uint8 motorA_encoder
uint8 motorA_dir
uint8 motorB_encoder
uint8 motorB_dir
uint8 motorC_encoder
uint8 motorC_dir
uint8 voltage

")



(provide :taobot_link/Taobot "7d650a23fc1ea1941c14405910e8d823")


