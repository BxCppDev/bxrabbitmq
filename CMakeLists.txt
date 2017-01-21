# - Top level CMakeLists.txt for Bayeux/RabbitMQ C++ library

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(bxrabbitmq LANGUAGES CXX)

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

# - Versioning
set(BxRabbitMQ_VERSION_MAJOR 0)
set(BxRabbitMQ_VERSION_MINOR 1)
set(BxRabbitMQ_VERSION_PATCH 0)
set(BxRabbitMQ_VERSION
  "${BxRabbitMQ_VERSION_MAJOR}.${BxRabbitMQ_VERSION_MINOR}.${BxRabbitMQ_VERSION_PATCH}")

#-----------------------------------------------------------------------
# - Standard UNIX Tool install paths, including relative paths for use
# by applications requiring resources
include(GNUInstallDirs)

# - Validate that certain paths are relative, otherwise relocation may fail
foreach(_dir BINDIR LIBDIR INCLUDEDIR DATAROOTDIR)
  if(IS_ABSOLUTE "${CMAKE_INSTALL_${_dir}}")
    message(FATAL_ERROR "Absolute path for CMAKE_INSTALL_${_dir} not allowed")
  endif()
endforeach()

# Add a path for CMake config files
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake)
set(CMAKE_INSTALL_FULL_CMAKEDIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

# Resources directories based on name-version subdirs
set(BXRABBITMQ_TAG "BxRabbitMQ-${BxRabbitMQ_VERSION}")
file(RELATIVE_PATH BXRABBITMQ_BINDIR_TO_RESOURCEDIR "${CMAKE_INSTALL_FULL_BINDIR}" "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${BXRABBITMQ_TAG}")
file(RELATIVE_PATH BXRABBITMQ_CMAKEDIR_TO_INCLUDEDIR "${CMAKE_INSTALL_FULL_CMAKEDIR}/${BXRABBITMQ_TAG}"  "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
# message( STATUS "BXRABBITMQ_TAG='${BXRABBITMQ_TAG}'")
# message( STATUS "CMAKE_INSTALL_INCLUDEDIR='${CMAKE_INSTALL_INCLUDEDIR}'")
# message( STATUS "CMAKE_INSTALL_BINDIR='${CMAKE_INSTALL_BINDIR}'")
# message( STATUS "CMAKE_INSTALL_LIBDIR='${CMAKE_INSTALL_LIBDIR}'")
# message( STATUS "CMAKE_INSTALL_CMAKEDIR='${CMAKE_INSTALL_CMAKEDIR}'")
# message( STATUS "CMAKE_INSTALL_DATAROOTDIR='${CMAKE_INSTALL_DATAROOTDIR}'")

option (BXRABBITMQ_WITH_BOOST "Build Bayeux/rabbitmq with Boost support" ON)
mark_as_advanced (BXRABBIT_WITH_BOOST)

set(BxRabbitMQ_HEADERS
  src/rabbitmq/exception.h
  src/rabbitmq/basic_properties.h
  src/rabbitmq/parameters.h
  src/rabbitmq/connection.h
  src/rabbitmq/channel.h
  src/rabbitmq/rabbit_mgr.h
  )

set(BxRabbitMQ_SOURCES
  src/rabbitmq/exception.cc
  src/rabbitmq/basic_properties.cc
  src/rabbitmq/parameters.cc
  src/rabbitmq/connection.cc
  src/rabbitmq/channel.cc
  src/rabbitmq/rabbit_mgr.cc
  )

set(BxRabbitMQ_OTHER_LIBS)

include (FindPkgConfig)
#
pkg_check_modules (RabbitC REQUIRED librabbitmq)
message (STATUS "RabbitC_INCUDE_DIRS      = '${RabbitC_INCLUDE_DIRS}'")
message (STATUS "RabbitC_VERSION          = '${RabbitC_VERSION}'")
message (STATUS "RabbitC_LDFLAGS          = '${RabbitC_LDFLAGS}'")
message (STATUS "RabbitC_LIBDIR           = '${RabbitC_LIBDIR}'")
message (STATUS "RabbitC_LIBRARIES        = '${RabbitC_LIBRARIES}'")
message (STATUS "RabbitC_DIR              = '${RabbitC_LIBDIR}/..'")
#
pkg_check_modules (cURLpp REQUIRED curlpp)
message (STATUS "cURLpp_INCUDE_DIRS       = '${cURLpp_INCLUDE_DIRS}'")
message (STATUS "cURLpp_VERSION           = '${cURLpp_VERSION}'")
message (STATUS "cURLpp_LDFLAGS           = '${cURLpp_LDFLAGS}'")
message (STATUS "cURLpp_LIBDIR            = '${cURLpp_PREFIX}/lib'")
message (STATUS "cURLpp_LIBRARIES         = '${cURLpp_LIBRARIES}'")
message (STATUS "cURLpp_DIR               = '${cURLpp_PREFIX}'")
#
find_package(BxJsontools 0.1 REQUIRED CONFIG) # HINTS )
message (STATUS "BxJsontools_INCLUDE_DIRS = '${BxJsontools_INCLUDE_DIRS}'")
message (STATUS "BxJsontools_DEFINITIONS  = '${BxJsontools_DEFINITIONS}'")
message (STATUS "BxJsontools_LIBRARY      = '${BxJsontools_LIBRARY}'")
message (STATUS "BxJsontools_LIBDIR       = '${BxJsontools_INCLUDE_DIRS}/../lib'")
#
find_package(Boost 1.58.0 REQUIRED date_time)
message( STATUS "Boost found at             '${Boost_INCLUDE_DIRS}'")
message( STATUS "Boost version            = '${Boost_VERSION}'")
set (BXJSONTOOLS_WITH_BOOST ON)

include_directories (SYSTEM
   ${RabbitC_INCLUDE_DIRS}
   ${cURLpp_INCLUDE_DIRS}
   ${BxJsontools_INCLUDE_DIRS}
   ${Boost_INCLUDE_DIRS}
)
list (APPEND BxRabbitMQ_OTHER_LIBS
   ${RabbitC_LDFLAGS}
   ${cURLpp_LIBRARIES}
   ${BxJsontools_LIBRARIES}
   ${Boost_DATE_TIME_LIBRARY}
)
message (STATUS "BxRabbitMQ_OTHER_LIBS='${BxRabbitMQ_OTHER_LIBS}'")

# - Publish headers
configure_file(src/rabbitmq/version.h.in ${PROJECT_BINARY_DIR}/src/rabbitmq/version.h @ONLY)
configure_file(src/rabbitmq/config.h.in  ${PROJECT_BINARY_DIR}/src/rabbitmq/config.h  @ONLY)

# - Utilities
configure_file(src/utilities/bxrabbitmq-query.in ${PROJECT_BINARY_DIR}/src/utilities/bxrabbitmq-query  @ONLY)

set(BxRabbitMQ_PRIVATE_HEADERS
  )

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS -std=c++11)
endif()

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)

add_library(Bayeux_rabbitmq SHARED
  ${BxRabbitMQ_HEADERS}
  ${BxRabbitMQ_SOURCES}
  )

target_link_libraries (Bayeux_rabbitmq ${BxRabbitMQ_OTHER_LIBS})

install( FILES
  ${BxRabbitMQ_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/rabbitmq
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install( FILES
  ${PROJECT_BINARY_DIR}/src/rabbitmq/version.h
  ${PROJECT_BINARY_DIR}/src/rabbitmq/config.h
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/rabbitmq
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install( FILES
  ${PROJECT_BINARY_DIR}/libBayeux_rabbitmq${CMAKE_SHARED_LIBRARY_SUFFIX}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( FILES
  ${PROJECT_BINARY_DIR}/src/utilities/bxrabbitmq-query
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( DIRECTORY
  ${PROJECT_SOURCE_DIR}/examples
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXRABBITMQ_TAG}
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( FILES
  ${PROJECT_SOURCE_DIR}/LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXRABBITMQ_TAG}
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
)

install( DIRECTORY
  ${PROJECT_SOURCE_DIR}/licensing
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXRABBITMQ_TAG}
  FILE_PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

option(RABBITMQ_ENABLE_TESTING "Build unit testing system for Bayeux/rabbitmq" ON)
if(RABBITMQ_ENABLE_TESTING)
  enable_testing()
endif()

set(BxRabbitMQ_TESTS
  src/rabbitmq/testing/test_rabbitmq_0.cxx
  )

if(RABBITMQ_ENABLE_TESTING)
  foreach(_testsource ${BxRabbitMQ_TESTS})
    set(_bxrabbitmq_TEST_ENVIRONMENT
      # "BXRABBITMQ_RESOURCE_FILES_DIR=${PROJECT_SOURCE_DIR}/resources"
      )
    get_filename_component(_testname "${_testsource}" NAME_WE)
    set(_testname "bxrabbitmq-${_testname}")
    add_executable(${_testname} ${_testsource}
      src/rabbitmq/testing/test.h
      src/rabbitmq/testing/test.cc
      )
    target_link_libraries(${_testname} Bayeux_rabbitmq ${BxRabbitMQ_OTHER_LIBS})
    # - On Apple, ensure dynamic_lookup of undefined symbols
    if(APPLE)
      set_target_properties(${_testname} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
    endif()
    add_test(NAME ${_testname} COMMAND ${_testname})
    set_property(TEST ${_testname}
      APPEND PROPERTY ENVIRONMENT ${_bxrabbitmq_TEST_ENVIRONMENT}
      )
    # - For now, dump them into the testing output directory
    set_target_properties(${_testname}
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxrabbitmq_tests
      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxrabbitmq_tests
      )
  endforeach()
endif()

#-----------------------------------------------------------------------
# Install targets and resources
#
install(TARGETS Bayeux_rabbitmq
  EXPORT  BxRabbitMQTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

#-----------------------------------------------------------------------
# Configure/Install support files
# Done here so that external package variables are visible
#
# - Targets
export(TARGETS Bayeux_rabbitmq
  FILE ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}/BxRabbitMQTargets.cmake
  )
install(EXPORT BxRabbitMQTargets
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}
  )

# - Versioning (build and install trees)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxRabbitMQConfigVersion.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}/BxRabbitMQConfigVersion.cmake
  @ONLY
  )

# - Config (build and install trees *at present*)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxRabbitMQConfig.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}/BxRabbitMQConfig.cmake
  @ONLY
  )

install(FILES
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}/BxRabbitMQConfigVersion.cmake
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}/BxRabbitMQConfig.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}
  )

# - end of CMakeLists.txt
