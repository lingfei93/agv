;; Auto-generated. Do not edit!


(when (boundp 'axon_link::Taobot)
  (if (not (find-package "AXON_LINK"))
    (make-package "AXON_LINK"))
  (shadow 'Taobot (find-package "AXON_LINK")))
(unless (find-package "AXON_LINK::TAOBOT")
  (make-package "AXON_LINK::TAOBOT"))

(in-package "ROS")
;;//! \htmlinclude Taobot.msg.html


(defclass axon_link::Taobot
  :super ros::object
  :slots (_motorA_encoder _motorA_dir _motorB_encoder _motorB_dir _motorC_encoder _motorC_dir _voltage ))

(defmethod axon_link::Taobot
  (:init
   (&key
    ((:motorA_encoder __motorA_encoder) 0)
    ((:motorA_dir __motorA_dir) 0)
    ((:motorB_encoder __motorB_encoder) 0)
    ((:motorB_dir __motorB_dir) 0)
    ((:motorC_encoder __motorC_encoder) 0)
    ((:motorC_dir __motorC_dir) 0)
    ((:voltage __voltage) 0.0)
    )
   (send-super :init)
   (setq _motorA_encoder (round __motorA_encoder))
   (setq _motorA_dir (round __motorA_dir))
   (setq _motorB_encoder (round __motorB_encoder))
   (setq _motorB_dir (round __motorB_dir))
   (setq _motorC_encoder (round __motorC_encoder))
   (setq _motorC_dir (round __motorC_dir))
   (setq _voltage (float __voltage))
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
    ;; float32 _voltage
    4
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
     ;; float32 _voltage
       (sys::poke _voltage (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
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
   ;; float32 _voltage
     (setq _voltage (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get axon_link::Taobot :md5sum-) "8683fead56235780b4aa5f54f5f7b789")
(setf (get axon_link::Taobot :datatype-) "axon_link/Taobot")
(setf (get axon_link::Taobot :definition-)
      "uint8 motorA_encoder
uint8 motorA_dir
uint8 motorB_encoder
uint8 motorB_dir
uint8 motorC_encoder
uint8 motorC_dir
float32 voltage

")



(provide :axon_link/Taobot "8683fead56235780b4aa5f54f5f7b789")


