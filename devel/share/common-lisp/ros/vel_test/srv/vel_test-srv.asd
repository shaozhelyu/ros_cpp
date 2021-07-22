
(cl:in-package :asdf)

(defsystem "vel_test-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "CheckValid" :depends-on ("_package_CheckValid"))
    (:file "_package_CheckValid" :depends-on ("_package"))
  ))