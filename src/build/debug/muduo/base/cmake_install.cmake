# Install script for directory: /home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/radek/Pulpit/proj-inz/engineer/src/build/debug-install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/radek/Pulpit/proj-inz/engineer/src/build/debug/lib/libmuduo_base.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/radek/Pulpit/proj-inz/engineer/src/build/debug/lib/libmuduo_base_cpp11.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/ThreadLocal.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/ThreadLocalSingleton.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/ThreadPool.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/ProcessInfo.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/BlockingQueue.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/FileUtil.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/StringPiece.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/CountDownLatch.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Types.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/TimeZone.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/LogFile.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Logging.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/copyable.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/AsyncLogging.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Timestamp.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Exception.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Mutex.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Singleton.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/LogStream.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Atomic.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/BoundedBlockingQueue.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Date.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Thread.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/CurrentThread.h"
    "/home/radek/Pulpit/proj-inz/engineer/src/muduo/muduo/base/Condition.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/radek/Pulpit/proj-inz/engineer/src/build/debug/muduo/base/tests/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

