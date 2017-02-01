# - Top level CMakeLists.txt for rabbitmq_tutorials example program

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(bxrabbitmq_tutorials)

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
find_package(BxRabbitMQ 0.1 REQUIRED CONFIG)
message (STATUS "BxRabbitMQ_INCLUDE_DIRS ='${BxRabbitMQ_INCLUDE_DIRS}'")
message (STATUS "BxRabbitMQ_LIBRARIES    ='${BxRabbitMQ_LIBRARIES}'")

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

add_definitions     (${BxRabbitMQ_DEFINITIONS})
include_directories (${PROJECT_SOURCE_DIR} ${BxRabbitMQ_INCLUDE_DIRS})
link_libraries      (${BxRabbitMQ_LIBRARIES})

add_executable (t1_send                t1_send.cxx)
add_executable (t1_receive             t1_receive.cxx)
add_executable (t2_new_task            t2_new_task.cxx)
add_executable (t2_worker              t2_worker.cxx)
add_executable (t3_emit_log            t3_emit_log.cxx)
add_executable (t3_receive_logs        t3_receive_logs.cxx)
add_executable (t4_emit_log_direct     t4_emit_log_direct.cxx)
add_executable (t4_receive_logs_direct t4_receive_logs_direct.cxx)
add_executable (t5_emit_log_topic      t5_emit_log_topic.cxx)
add_executable (t5_receive_logs_topic  t5_receive_logs_topic.cxx)
add_executable (t6_rpc_client          t6_rpc_client.cxx)
add_executable (t6_rpc_server          t6_rpc_server.cxx)

#target_link_libraries (t1_send                ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t1_receive             ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t2_new_task            ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t2_worker              ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t3_emit_log            ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t3_receive_logs        ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t4_emit_log_direct     ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t4_receive_logs_direct ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t5_emit_log_topic      ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t5_receive_logs_topic  ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t6_rpc_client          ${BxRabbitMQ_LIBRARIES})
#target_link_libraries (t6_rpc_server          ${BxRabbitMQ_LIBRARIES})

install ( FILES
    ${PROJECT_BINARY_DIR}/t1_send
    ${PROJECT_BINARY_DIR}/t1_receive
    ${PROJECT_BINARY_DIR}/t2_new_task
    ${PROJECT_BINARY_DIR}/t2_worker
    ${PROJECT_BINARY_DIR}/t3_emit_log
    ${PROJECT_BINARY_DIR}/t3_receive_logs
    ${PROJECT_BINARY_DIR}/t4_emit_log_direct
    ${PROJECT_BINARY_DIR}/t4_receive_logs_direct
    ${PROJECT_BINARY_DIR}/t5_emit_log_topic
    ${PROJECT_BINARY_DIR}/t5_receive_logs_topic
    ${PROJECT_BINARY_DIR}/t6_rpc_client
    ${PROJECT_BINARY_DIR}/t6_rpc_server
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
  )

# end of CMakeLists.txt
