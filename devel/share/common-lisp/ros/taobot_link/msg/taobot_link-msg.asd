
(cl:in-package :asdf)

(defsystem "taobot_link-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Odom" :depends-on ("_package_Odom"))
    (:file "_package_Odom" :depends-on ("_package"))
    (:file "Taobot" :depends-on ("_package_Taobot"))
    (:file "_package_Taobot" :depends-on ("_package"))
  ))