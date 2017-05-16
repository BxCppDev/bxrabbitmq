# - Top level CMakeLists.txt for Bayeux/RabbitMQ C++ library

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
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

# - Load Custom Modules
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

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
    message(FATAL_ERROR "[fatal] Absolute path for CMAKE_INSTALL_${_dir} not allowed")
  endif()
endforeach()

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

# Add a path for CMake config files
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake)
set(CMAKE_INSTALL_FULL_CMAKEDIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

# Resources directories based on name-version subdirs
set(BXRABBITMQ_TAG "BxRabbitMQ-${BxRabbitMQ_VERSION}")
file(RELATIVE_PATH BXRABBITMQ_BINDIR_TO_RESOURCEDIR
  "${CMAKE_INSTALL_FULL_BINDIR}"
  "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${BXRABBITMQ_TAG}"
  )
file(RELATIVE_PATH BXRABBITMQ_CMAKEDIR_TO_INCLUDEDIR
  "${CMAKE_INSTALL_FULL_CMAKEDIR}/${BXRABBITMQ_TAG}"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
  )

# - Option: RabbitMQ server management implies cURLpp and BxJsontools:
option(BXRABBITMQ_WITH_MANAGER "Build RabbitMQ server management code" OFF)
set(BxRabbitMQ_WITH_MANAGER 0)
if (BXRABBITMQ_WITH_MANAGER)
  set(BxRabbitMQ_WITH_MANAGER 1)
endif()

set(BxRabbitMQ_HEADERS
  src/rabbitmq/exception.h
  src/rabbitmq/basic_properties.h
  src/rabbitmq/parameters.h
  src/rabbitmq/connection.h
  src/rabbitmq/channel.h
  )

set(BxRabbitMQ_SOURCES
  src/rabbitmq/exception.cc
  src/rabbitmq/basic_properties.cc
  src/rabbitmq/parameters.cc
  src/rabbitmq/connection.cc
  src/rabbitmq/channel.cc
  )

set(BxRabbitMQ_MANAGER_HEADERS
  src/rabbitmq/rabbit_mgr.h
  src/rabbitmq/management.h
  )

set(BxRabbitMQ_MANAGER_SOURCES
  src/rabbitmq/rabbit_mgr.cc
  src/rabbitmq/management.cc
  )

set(BxRabbitMQ_OTHER_LIBS)

message (STATUS "[info] Finding package Boost...")
set(BXRABBITMQ_MIN_BOOST_VERSION 1.58)
set(Boost_NO_BOOST_CMAKE ON)
find_package (Boost ${BXRABBITMQ_MIN_BOOST_VERSION} REQUIRED)
message( STATUS "[info] Boost version      = '${Boost_VERSION}'")
message( STATUS "[info] Boost found at '${Boost_INCLUDE_DIRS}'")
message (STATUS "[info] Boost_INCLUDE_DIRS = '${Boost_INCLUDE_DIRS}'")
message( STATUS "[info] Boost_LIBRARIES    = '${Boost_LIBRARIES}'")
message( STATUS "[info] Boost_MAJOR_VERSION = '${Boost_MAJOR_VERSION}'")
message( STATUS "[info] Boost_MINOR_VERSION = '${Boost_MINOR_VERSION}'")
message( STATUS "[info] Boost_SUBMINOR_VERSION = '${Boost_SUBMINOR_VERSION}'")
set(BxRabbitMQ_BOOST_VERSION
  "${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
get_filename_component(Boost_DIR ${Boost_INCLUDE_DIRS} DIRECTORY)
message( STATUS "[info] BxRabbitMQ_BOOST_VERSION = '${BxRabbitMQ_BOOST_VERSION}'")

include (FindPkgConfig)

if (BXRABBITMQ_WITH_MANAGER)
  message (STATUS "[info] Checking pkg-module curlpp...")
  pkg_check_modules (cURLpp REQUIRED curlpp)
  message (STATUS "[info] cURLpp_INCLUDE_DIRS      = '${cURLpp_INCLUDE_DIRS}'")
  message (STATUS "[info] cURLpp_VERSION           = '${cURLpp_VERSION}'")
  message (STATUS "[info] cURLpp_LDFLAGS           = '${cURLpp_LDFLAGS}'")
  message (STATUS "[info] cURLpp_LIBDIR            = '${cURLpp_PREFIX}/lib'")
  message (STATUS "[info] cURLpp_LIBRARIES         = '${cURLpp_LIBRARIES}'")
  message (STATUS "[info] cURLpp_DIR               = '${cURLpp_PREFIX}'")
  find_path(CURLPP_INCLUDE_DIR
    NAMES "curlpp/cURLpp.hpp"
    PATHS ${cURLpp_INCLUDE_DIRS}
    )
  message (STATUS "[info] CURLPP_INCLUDE_DIR = '${CURLPP_INCLUDE_DIR}'")
  set(CURLPP_LIBRARY_NAME "libcurlpp${CMAKE_SHARED_LIBRARY_SUFFIX}")
  message (STATUS "[info] CURLPP_LIBRARY_NAME = '${CURLPP_LIBRARY_NAME}'")
  set(CURLPP_LIBRARY_PATH "${cURLpp_PREFIX}/lib")
  message (STATUS "[info] CURLPP_LIBRARY_PATH = '${CURLPP_LIBRARY_PATH}'")
  find_library(CURLPP_LIBRARY
    NAMES ${CURLPP_LIBRARY_NAME}
    PATHS ${CURLPP_LIBRARY_PATH}
    )
  message (STATUS "[info] CURLPP_LIBRARY = '${CURLPP_LIBRARY}'")
  message (STATUS "[info] Finding package BxJsontools...")
  find_package (BxJsontools 0.1 REQUIRED CONFIG)
  message (STATUS "[info] BxJsontools_VERSION      = '${BxJsontools_VERSION}'")
  message (STATUS "[info] BxJsontools_INCLUDE_DIRS = '${BxJsontools_INCLUDE_DIRS}'")
  message (STATUS "[info] BxJsontools_DEFINITIONS  = '${BxJsontools_DEFINITIONS}'")
  message (STATUS "[info] BxJsontools_LIBRARY      = '${BxJsontools_LIBRARY}'")
  message (STATUS "[info] BxJsontools_LIBRARIES    = '${BxJsontools_LIBRARIES}'")
  message (STATUS "[info] BxJsontools_LIBDIR       = '${BxJsontools_INCLUDE_DIRS}/../lib'")
  message (STATUS "[info] BxJsontools_DIR          = '${BxJsontools_DIR}'")
endif(BXRABBITMQ_WITH_MANAGER)

message (STATUS "[info] Checking pkg-module librabbitmq...")
pkg_check_modules (RabbitC REQUIRED librabbitmq)
message (STATUS "[info] RabbitC_INCLUDE_DIRS     = '${RabbitC_INCLUDE_DIRS}'")
message (STATUS "[info] RabbitC_VERSION          = '${RabbitC_VERSION}'")
message (STATUS "[info] RabbitC_LDFLAGS          = '${RabbitC_LDFLAGS}'")
message (STATUS "[info] RabbitC_LIBDIR           = '${RabbitC_LIBDIR}'")
message (STATUS "[info] RabbitC_LIBRARIES        = '${RabbitC_LIBRARIES}'")
message (STATUS "[info] RabbitC_DIR              = '${RabbitC_LIBDIR}/..'")
find_path(RABBITC_INCLUDE_DIR
  NAMES "amqp.h"
  PATHS ${RabbitC_INCLUDE_DIRS}
  )
message (STATUS "[info] RABBITC_INCLUDE_DIR = '${RABBITC_INCLUDE_DIR}'")
set(RABBITC_LIBRARY_NAME "librabbitmq${CMAKE_SHARED_LIBRARY_SUFFIX}")
message (STATUS "[info] RABBITC_LIBRARY_NAME = '${RABBITC_LIBRARY_NAME}'")
set(RABBITC_LIBRARY_PATH "${RabbitC_LIBDIR}")
message (STATUS "[info] RABBITC_LIBRARY_PATH = '${RABBITC_LIBRARY_PATH}'")
find_library(RABBITC_LIBRARY
  NAMES ${RABBITC_LIBRARY_NAME}
  PATHS ${RABBITC_LIBRARY_PATH}
  )
message (STATUS "[info] RABBITC_LIBRARY = '${RABBITC_LIBRARY}'")

include_directories (SYSTEM
  ${RABBITC_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  )
list (APPEND BxRabbitMQ_OTHER_LIBS
  ${RABBITC_LIBRARY}
  )

if (BXRABBITMQ_WITH_MANAGER)
  include_directories (SYSTEM
    ${CURLPP_INCLUDE_DIR}
    ${BxJsontools_INCLUDE_DIRS}
    )
  list (APPEND BxRabbitMQ_OTHER_LIBS
    ${CURLPP_LIBRARY}
    ${BxJsontools_LIBRARIES}
    )
endif(BXRABBITMQ_WITH_MANAGER)

message (STATUS "[info] BxRabbitMQ_OTHER_LIBS='${BxRabbitMQ_OTHER_LIBS}'")

# - Publish headers
configure_file (src/rabbitmq/version.h.in ${PROJECT_BINARY_DIR}/src/rabbitmq/version.h @ONLY)
configure_file (src/rabbitmq/config.h.in  ${PROJECT_BINARY_DIR}/src/rabbitmq/config.h  @ONLY)

# - Utilities
configure_file (src/utilities/bxrabbitmq-query.in ${PROJECT_BINARY_DIR}/src/utilities/bxrabbitmq-query  @ONLY)

if (CMAKE_COMPILER_IS_GNUCXX)
  set (CMAKE_CXX_FLAGS -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCXX)

include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_BINARY_DIR}/src)

add_library (Bayeux_rabbitmq SHARED
  ${BxRabbitMQ_HEADERS}
  ${BxRabbitMQ_SOURCES}
  )

target_link_libraries (Bayeux_rabbitmq ${BxRabbitMQ_OTHER_LIBS})

# - Set RPATH as needed
set_target_properties (Bayeux_rabbitmq PROPERTIES INSTALL_RPATH_USE_LINK_PATH 1)

install ( FILES
  ${BxRabbitMQ_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/rabbitmq
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install ( FILES
  ${PROJECT_BINARY_DIR}/src/rabbitmq/version.h
  ${PROJECT_BINARY_DIR}/src/rabbitmq/config.h
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/rabbitmq
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install ( FILES
  ${PROJECT_BINARY_DIR}/libBayeux_rabbitmq${CMAKE_SHARED_LIBRARY_SUFFIX}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install ( FILES
  ${PROJECT_BINARY_DIR}/src/utilities/bxrabbitmq-query
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install ( DIRECTORY
  ${PROJECT_SOURCE_DIR}/examples/tutorials
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXRABBITMQ_TAG}/examples
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  REGEX tools EXCLUDE REGEX _install.d EXCLUDE REGEX _build.d EXCLUDE
  )

install ( FILES
  ${PROJECT_SOURCE_DIR}/LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXRABBITMQ_TAG}
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install ( DIRECTORY
  ${PROJECT_SOURCE_DIR}/licensing
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXRABBITMQ_TAG}
  FILE_PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

option (BXRABBITMQ_ENABLE_TESTING "Build unit testing system for Bayeux/rabbitmq" ON)
if (BXRABBITMQ_ENABLE_TESTING)
  enable_testing ()
endif (BXRABBITMQ_ENABLE_TESTING)

set (BxRabbitMQ_TESTS
  src/rabbitmq/testing/test_rabbitmq_0.cxx
  )

if (BXRABBITMQ_WITH_MANAGER)

  list (APPEND BxRabbitMQ_TESTS
    src/rabbitmq/testing/test_rabbitmq_mgr_0.cxx
    )

  add_library (Bayeux_rabbitmq_manager SHARED
    ${BxRabbitMQ_MANAGER_HEADERS}
    ${BxRabbitMQ_MANAGER_SOURCES}
    )

  target_link_libraries (Bayeux_rabbitmq_manager
    ${CURLPP_LIBRARY}
    ${BxJsontools_LIBRARIES}
    )

  # - Set RPATH as needed
  set_target_properties (Bayeux_rabbitmq_manager PROPERTIES INSTALL_RPATH_USE_LINK_PATH 1)

  install ( FILES
    ${BxRabbitMQ_MANAGER_HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/rabbitmq
    PERMISSIONS OWNER_READ OWNER_WRITE
    GROUP_READ
    WORLD_READ
    )

  install ( FILES
    ${PROJECT_BINARY_DIR}/libBayeux_rabbitmq_manager${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
    )

  install ( DIRECTORY
    ${PROJECT_SOURCE_DIR}/examples/management
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXRABBITMQ_TAG}/examples
    FILE_PERMISSIONS OWNER_READ
    GROUP_READ
    WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
    REGEX tools EXCLUDE REGEX _install.d EXCLUDE REGEX _build.d EXCLUDE
    )

endif (BXRABBITMQ_WITH_MANAGER)

if (RABBITMQ_ENABLE_TESTING)
  foreach (_testsource ${BxRabbitMQ_TESTS})
    set (_bxrabbitmq_TEST_ENVIRONMENT
      # "BXRABBITMQ_RESOURCE_FILES_DIR=${PROJECT_SOURCE_DIR}/resources"
      )
    get_filename_component(_testname "${_testsource}" NAME_WE)
    set(_testname "bxrabbitmq-${_testname}")
    set(_test_files
      src/rabbitmq/testing/test.h
      src/rabbitmq/testing/test.cc
      )
    if (BXRABBITMQ_WITH_MANAGER)
      list (APPEND _test_files
	src/rabbitmq/testing/test_mgr.h
	src/rabbitmq/testing/test_mgr.cc
	)
    endif (BXRABBITMQ_WITH_MANAGER)
    add_executable(${_testname} ${_testsource} ${_test_files})
    target_link_libraries(${_testname} Bayeux_rabbitmq ${BxRabbitMQ_OTHER_LIBS})
    if (BXRABBITMQ_WITH_MANAGER)
      target_link_libraries(${_testname} Bayeux_rabbitmq_manager)
    endif (BXRABBITMQ_WITH_MANAGER)

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
  endforeach ()
endif (RABBITMQ_ENABLE_TESTING)

#-----------------------------------------------------------------------
# Install targets and resources
#
install(TARGETS Bayeux_rabbitmq
  EXPORT  BxRabbitMQTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

if (BXRABBITMQ_WITH_MANAGER)
  install (TARGETS Bayeux_rabbitmq_manager
    EXPORT  BxRabbitMQTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif (BXRABBITMQ_WITH_MANAGER)

#-----------------------------------------------------------------------
# Configure/Install support files
# Done here so that external package variables are visible
#
# - Targets
export(TARGETS Bayeux_rabbitmq
  FILE ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}/BxRabbitMQTargets.cmake
  )

if (BXRABBITMQ_WITH_MANAGER)
  export(TARGETS Bayeux_rabbitmq_manager
    FILE ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXRABBITMQ_TAG}/BxRabbitMQTargets.cmake
    )
endif (BXRABBITMQ_WITH_MANAGER)

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
