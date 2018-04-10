;; Auto-generated. Do not edit!


(when (boundp 'taobot_link::Odom)
  (if (not (find-package "TAOBOT_LINK"))
    (make-package "TAOBOT_LINK"))
  (shadow 'Odom (find-package "TAOBOT_LINK")))
(unless (find-package "TAOBOT_LINK::ODOM")
  (make-package "TAOBOT_LINK::ODOM"))

(in-package "ROS")
;;//! \htmlinclude Odom.msg.html


(defclass taobot_link::Odom
  :super ros::object
  :slots (_x_pos _y_pos _theta ))

(defmethod taobot_link::Odom
  (:init
   (&key
    ((:x_pos __x_pos) 0.0)
    ((:y_pos __y_pos) 0.0)
    ((:theta __theta) 0.0)
    )
   (send-super :init)
   (setq _x_pos (float __x_pos))
   (setq _y_pos (float __y_pos))
   (setq _theta (float __theta))
   self)
  (:x_pos
   (&optional __x_pos)
   (if __x_pos (setq _x_pos __x_pos)) _x_pos)
  (:y_pos
   (&optional __y_pos)
   (if __y_pos (setq _y_pos __y_pos)) _y_pos)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:serialization-length
   ()
   (+
    ;; float32 _x_pos
    4
    ;; float32 _y_pos
    4
    ;; float32 _theta
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x_pos
       (sys::poke _x_pos (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y_pos
       (sys::poke _y_pos (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x_pos
     (setq _x_pos (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y_pos
     (setq _y_pos (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _theta
     (setq _theta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get taobot_link::Odom :md5sum-) "e9518dd7f72bb88584af16172a7ace5f")
(setf (get taobot_link::Odom :datatype-) "taobot_link/Odom")
(setf (get taobot_link::Odom :definition-)
      "float32 x_pos
float32 y_pos
float32 theta

")



(provide :taobot_link/Odom "e9518dd7f72bb88584af16172a7ace5f")


