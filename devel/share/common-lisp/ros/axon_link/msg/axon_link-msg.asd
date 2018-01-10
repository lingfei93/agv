
(cl:in-package :asdf)

(defsystem "axon_link-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Taobot" :depends-on ("_package_Taobot"))
    (:file "_package_Taobot" :depends-on ("_package"))
  ))