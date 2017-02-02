# - Top level CMakeLists.txt for rabbit_management example program

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(bxrabbit_management)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(STATUS "${PROJECT_NAME} requires an out-of-source build.")
  message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
  message(STATUS "  CMakeCache.txt")
  message(STATUS "  CMakeFiles")
  message(STATUS "Once these files are removed, create a separate directory")
  message(STATUS "and run CMake from there, pointing it to:")
  message(STATUS "  ${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "in-source build detected")
endif()

# -- RPATH settings --
# From: https://cmake.org/Wiki/CMake_RPATH_handling
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_FULL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
endif()

# BxRabbitMQ
message (STATUS "[info] Finding package BxRabbitMQ with 'manager' component...")
find_package(BxRabbitMQ 0.1 REQUIRED CONFIG COMPONENTS manager)
message (STATUS "BxRabbitMQ_INCLUDE_DIRS      ='${BxRabbitMQ_INCLUDE_DIRS}'")
message (STATUS "BxRabbitMQ_LIBRARIES         ='${BxRabbitMQ_LIBRARIES}'")
message (STATUS "BxRabbitMQ_MANAGER_LIBRARIES ='${BxRabbitMQ_MANAGER_LIBRARIES}'")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_definitions     (${BxRabbitMQ_DEFINITIONS})
include_directories (${PROJECT_SOURCE_DIR} ${BxRabbitMQ_INCLUDE_DIRS})
link_libraries      (${BxRabbitMQ_LIBRARIES} ${BxRabbitMQ_MANAGER_LIBRARIES})

add_executable (ex1 ex1.cxx)

install ( FILES
    ${PROJECT_BINARY_DIR}/ex1
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
  )

# end of CMakeLists.txt
