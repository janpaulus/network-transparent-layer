cmake_minimum_required(VERSION 2.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
rosbuild_init()

#Build Type
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE on)
SET(CMAKE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")
SET(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib) #static libraries
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin) #executables
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib) #dynamic libraries (plugins)

rosbuild_find_ros_package(zmq)

MESSAGE(STATUS "zmq_PACKAGE_PATH= ${zmq_PACKAGE_PATH}")
FIND_PACKAGE(zmq REQUIRED)
MESSAGE(STATUS "ZMQ_LIBRARY_DIR= ${ZMQ_LIBRARY_DIR}")

#SET(DOXYFILE_LATEX "NO")
#SET(DOXYFILE_OUTPUT_DIR ${CMAKE_HOME_DIRECTORY}/doc)
#include(UseDoxygen)


#FIND_PACKAGE(SDL REQUIRED)

#SET(UNICAP_LIB_DIRS ${unicap_LIBRARY_DIRS})
#SET(ZMQ_LIB_DIRS ${zmq_LIBRARY_DIRS})
#SET(SDL_LIB_DIRS ${SDL_LIBRARY_DIRS})

#SET(SOURCES_1 test/test.cpp)
#SET(SOURCES_2 test/testCameraZMQ.c)

#LDFLAGS=`pkg-config --libs libzmq libunicap sdl`
#CFLAGS=`pkg-config --cflags libzmq libunicap sdl` -g -Wall
#CC = gcc

link_libraries(	
  zmq
)

INCLUDE_DIRECTORIES(
  ${CMAKE_HOME_DIRECTORY}/include
  ${ZMQ_INCLUDE_DIR}
)

LINK_DIRECTORIES(
  ${CMAKE_HOME_DIRECTORY}/lib
  ${ZMQ_LIBRARY_DIR}
)



ADD_EXECUTABLE(testpub  src/testPublisher.cpp)

ADD_EXECUTABLE(testsub src/testSubscriber.cpp)

ADD_EXECUTABLE(testclient  src/testClient.cpp)

ADD_EXECUTABLE(testserver src/testServer.cpp)

ADD_EXECUTABLE(simplebroker src/simpleBroker.cpp)

ADD_LIBRARY(zmq_ntl
src/zmq_ntl.cpp
src/YamlConfig.cpp 
)

target_link_libraries(zmq_ntl yaml-cpp)

target_link_libraries(testsub zmq_ntl)

target_link_libraries(testpub zmq_ntl)


target_link_libraries(testclient zmq_ntl)

target_link_libraries(testserver zmq_ntl)





