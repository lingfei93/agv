#Author: Chen Chun-Lin
#For catkin make tool

cmake_minimum_required(VERSION 2.8.3)
project(cereal_port)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES ${PROJECT_NAME}
   CATKIN_DEPENDS roscpp
   #DEPENDS system_lib
)

## Sources
set(cereal_port_SRCS
    src/CerealPort.cpp
    include/cereal_port/CerealPort.h
)

## Declare a C++ library
add_library(${PROJECT_NAME} ${cereal_port_SRCS})

## Include headers
include_directories(include)

## Install headers
install(FILES include/cereal_port/CerealPort.h 
        DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/cereal_port)
