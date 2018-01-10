# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "axon_link: 1 messages, 0 services")

set(MSG_I_FLAGS "-Iaxon_link:/home/eee/agv/src/axon_link/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(axon_link_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/eee/agv/src/axon_link/msg/Taobot.msg" NAME_WE)
add_custom_target(_axon_link_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "axon_link" "/home/eee/agv/src/axon_link/msg/Taobot.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(axon_link
  "/home/eee/agv/src/axon_link/msg/Taobot.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/axon_link
)

### Generating Services

### Generating Module File
_generate_module_cpp(axon_link
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/axon_link
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(axon_link_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(axon_link_generate_messages axon_link_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eee/agv/src/axon_link/msg/Taobot.msg" NAME_WE)
add_dependencies(axon_link_generate_messages_cpp _axon_link_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(axon_link_gencpp)
add_dependencies(axon_link_gencpp axon_link_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS axon_link_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(axon_link
  "/home/eee/agv/src/axon_link/msg/Taobot.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/axon_link
)

### Generating Services

### Generating Module File
_generate_module_eus(axon_link
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/axon_link
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(axon_link_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(axon_link_generate_messages axon_link_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eee/agv/src/axon_link/msg/Taobot.msg" NAME_WE)
add_dependencies(axon_link_generate_messages_eus _axon_link_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(axon_link_geneus)
add_dependencies(axon_link_geneus axon_link_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS axon_link_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(axon_link
  "/home/eee/agv/src/axon_link/msg/Taobot.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/axon_link
)

### Generating Services

### Generating Module File
_generate_module_lisp(axon_link
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/axon_link
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(axon_link_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(axon_link_generate_messages axon_link_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eee/agv/src/axon_link/msg/Taobot.msg" NAME_WE)
add_dependencies(axon_link_generate_messages_lisp _axon_link_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(axon_link_genlisp)
add_dependencies(axon_link_genlisp axon_link_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS axon_link_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(axon_link
  "/home/eee/agv/src/axon_link/msg/Taobot.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/axon_link
)

### Generating Services

### Generating Module File
_generate_module_nodejs(axon_link
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/axon_link
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(axon_link_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(axon_link_generate_messages axon_link_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eee/agv/src/axon_link/msg/Taobot.msg" NAME_WE)
add_dependencies(axon_link_generate_messages_nodejs _axon_link_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(axon_link_gennodejs)
add_dependencies(axon_link_gennodejs axon_link_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS axon_link_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(axon_link
  "/home/eee/agv/src/axon_link/msg/Taobot.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/axon_link
)

### Generating Services

### Generating Module File
_generate_module_py(axon_link
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/axon_link
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(axon_link_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(axon_link_generate_messages axon_link_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eee/agv/src/axon_link/msg/Taobot.msg" NAME_WE)
add_dependencies(axon_link_generate_messages_py _axon_link_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(axon_link_genpy)
add_dependencies(axon_link_genpy axon_link_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS axon_link_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/axon_link)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/axon_link
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(axon_link_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/axon_link)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/axon_link
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(axon_link_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/axon_link)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/axon_link
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(axon_link_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/axon_link)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/axon_link
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(axon_link_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/axon_link)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/axon_link\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/axon_link
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(axon_link_generate_messages_py std_msgs_generate_messages_py)
endif()
