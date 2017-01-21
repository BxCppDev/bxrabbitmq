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

# BxRabbitMQ
find_package(BxRabbitMQ 0.1 REQUIRED CONFIG) # HINTS )
message (STATUS "BxRabbitMQ_INCLUDE_DIRS ='${BxRabbitMQ_INCLUDE_DIRS}'")
message (STATUS "BxRabbitMQ_LIBRARIES    ='${BxRabbitMQ_LIBRARIES}'")
#

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_definitions     (${BxRabbitMQ_DEFINITIONS})
include_directories (${PROJECT_SOURCE_DIR} ${BxRabbitMQ_INCLUDE_DIRS})
link_libraries      (${BxRabbitMQ_LIBRARIES})

add_executable (ex1 ex1.cxx)

install ( FILES
    ${PROJECT_BINARY_DIR}/ex1
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
  )

# end of CMakeLists.txt
