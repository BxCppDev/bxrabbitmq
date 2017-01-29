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
find_package(BxRabbitMQ 0.1 REQUIRED CONFIG) # HINTS )
message (STATUS "BxRabbitMQ_INCLUDE_DIRS ='${BxRabbitMQ_INCLUDE_DIRS}'")
message (STATUS "BxRabbitMQ_LIBRARIES    ='${BxRabbitMQ_LIBRARIES}'")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_definitions     (${BxRabbitMQ_DEFINITIONS})
include_directories (${PROJECT_SOURCE_DIR} ${BxRabbitMQ_INCLUDE_DIRS})
link_libraries      (${BxRabbitMQ_LIBRARIES})

add_executable (t1_send                t1_send.cxx)
target_link_libraries (t1_send ${BxRabbitMQ_LIBRARIES})

# add_executable (t1_receive             t1_receive.cxx)
# add_executable (t2_new_task            t2_new_task.cxx)
# add_executable (t2_worker              t2_worker.cxx)
# add_executable (t3_emit_log            t3_emit_log.cxx)
# add_executable (t3_receive_logs        t3_receive_logs.cxx)
# add_executable (t4_emit_log_direct     t4_emit_log_direct.cxx)
# add_executable (t4_receive_logs_direct t4_receive_logs_direct.cxx)
# add_executable (t5_emit_log_topic      t5_emit_log_topic.cxx)
# add_executable (t5_receive_logs_topic  t5_receive_logs_topic.cxx)
# add_executable (t6_rpc_client          t6_rpc_client.cxx)
# add_executable (t6_rpc_server          t6_rpc_server.cxx)


install ( FILES
    ${PROJECT_BINARY_DIR}/t1_send
    # ${PROJECT_BINARY_DIR}/t1_receive
    # ${PROJECT_BINARY_DIR}/t2_new_task
    # ${PROJECT_BINARY_DIR}/t2_worker
    # ${PROJECT_BINARY_DIR}/t3_emit_log
    # ${PROJECT_BINARY_DIR}/t3_receive_logs
    # ${PROJECT_BINARY_DIR}/t4_emit_log_direct
    # ${PROJECT_BINARY_DIR}/t4_receive_logs_direct
    # ${PROJECT_BINARY_DIR}/t5_emit_log_topic
    # ${PROJECT_BINARY_DIR}/t5_receive_logs_topic
    # ${PROJECT_BINARY_DIR}/t6_rpc_client
    # ${PROJECT_BINARY_DIR}/t6_rpc_server
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
  )

# end of CMakeLists.txt
