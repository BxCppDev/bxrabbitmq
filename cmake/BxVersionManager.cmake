# CMake tools for version management
# Author: F.Mauger
# Date: 2017-09-26
# Copyright 2017 (c) François Mauger, Université de Caen Normandie

function(bx_version_build_version_number prefix_)
  set(${prefix_}_VERSION
    "${${prefix_}_VERSION_MAJOR}.${${prefix_}_VERSION_MINOR}.${${prefix_}_VERSION_PATCH}"
    PARENT_SCOPE)
endfunction()

function(bx_version_extract_patch_from_db major_ minor_ patch_)
  # message(STATUS "[info] bx_version_extract_patch_from_db: Entering...")
  # message(STATUS "[info]   - Major   = ${major_}")
  # message(STATUS "[info]   - Minor   = ${minor_}")
  set(_version_patch 0)
  if (EXISTS ${PROJECT_SOURCE_DIR}/cmake/BxPackageVersions.db)
    file(STRINGS
      ${PROJECT_SOURCE_DIR}/cmake/BxPackageVersions.db
      _bx_package_versions_lines
      REGEX "^([0-9]+)\\.([0-9]+)\\.([0-9+])"
      )
    # message(STATUS "[info]  Lines = ${_bx_package_versions_lines}")
    foreach(line ${_bx_package_versions_lines})
      string(REPLACE "." ";" _version_list ${line})
      # message(STATUS "[info]  Version list = ${_version_list}")
      list(GET _version_list 0 _version_major)
      list(GET _version_list 1 _version_minor)
      list(GET _version_list 2 _version_patch)
      if(${_version_major} EQUAL ${major_})
	if(${_version_minor} EQUAL ${minor_})
	  set(${patch_} ${_version_patch} PARENT_SCOPE)
	  # message(STATUS "[info]  Resolved patch = ${_version_patch}")
	endif()
      endif()
    endforeach()
  else()
    set(${patch_} ${_version_patch} PARENT_SCOPE)
  endif()
  # message(STATUS "[info]   - New patch is set to : $ {${patch_}}")
  # message(STATUS "[info] bx_version_extract_patch_from_db: Exiting.")
endfunction()

macro(bx_version_set prefix_ major_ minor_)
  #message(STATUS "[info] bx_version_set: prefix_  = ${prefix_}")
  #message(STATUS "[info] bx_version_set: major_   = ${major_}")
  #message(STATUS "[info] bx_version_set: minor_   = ${minor_}")
  #message(STATUS "[info] bx_version_set: key  = ${prefix_}_VERSION_MAJOR")
  set(_version_major ${major_})
  set(_version_minor ${minor_})
  set(_version_patch 0)
  set(${prefix_}_VERSION_MAJOR ${_version_major})
  set(${prefix_}_VERSION_MINOR ${_version_minor})
  set(${prefix_}_VERSION_PATCH ${_version_patch})
  # message(STATUS "[info] bx_version_set: Major   = ${${prefix_}_VERSION_MAJOR}")
  # message(STATUS "[info] bx_version_set: Minor   = ${${prefix_}_VERSION_MINOR}")
  # message(STATUS "[info] bx_version_set: Patch   = ${${prefix_}_VERSION_PATCH}")
  bx_version_extract_patch_from_db(
    ${${prefix_}_VERSION_MAJOR}
    ${${prefix_}_VERSION_MINOR}
    ${prefix_}_VERSION_PATCH
    )
  bx_version_build_version_number(${prefix_})
  message(STATUS "[info] bx_version_set: Major   = ${${prefix_}_VERSION_MAJOR}")
  message(STATUS "[info] bx_version_set: Minor   = ${${prefix_}_VERSION_MINOR}")
  message(STATUS "[info] bx_version_set: Patch   = ${${prefix_}_VERSION_PATCH}")
  message(STATUS "[info] bx_version_set: Version = ${${prefix_}_VERSION}")
endmacro()
