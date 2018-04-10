
(cl:in-package :asdf)

(defsystem "vicon_xb-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "viconXbSrv" :depends-on ("_package_viconXbSrv"))
    (:file "_package_viconXbSrv" :depends-on ("_package"))
  ))