#
# - Find VampirTrace
#
# This module finds the VampirTrace include directory and library
#
# It sets the following variables:
#  VAMPIRTRACE_FOUND       - Set to false, or undefined, if VampirTrace isn't found.
#  VAMPIRTRACE_INCLUDE_DIR - The VampirTrace include directory.
#  VAMPIRTRACE_LIBRARIES   - The VampirTrace libraries to link against.
#  VAMPIRTRACE_VT_LIBRARY  - The vt libraries to link against.
#  VAMPIRTRACE_OTF_LIBRARY - The otf library to link against.
#  VAMPIRTRACE_CXX         - The full path command for vtcxx
#  VAMPIRTRACE_CC          - The full path command for vtcc
#  VAMPIRTRACE_F90         - The full path command for vtf90
	
	
# 1.a) It may be the case the path hints are given in environment, so check for
#      those hints first

# If VAMPIRTRACE_ROOT or VT_ROOT is defined in the environment, use it.
if ( NOT VAMPIRTRACE_ROOT AND NOT $ENV{VAMPIRTRACE_ROOT} STREQUAL "" )
  set( VAMPIRTRACE_ROOT $ENV{VAMPIRTRACE_ROOT} )
endif ( NOT VAMPIRTRACE_ROOT AND NOT $ENV{VAMPIRTRACE_ROOT} STREQUAL "" )

if ( NOT VAMPIRTRACE_ROOT AND NOT $ENV{VT_ROOT} STREQUAL "" )
  set( VAMPIRTRACE_ROOT $ENV{VT_ROOT} )
endif ( NOT VAMPIRTRACE_ROOT AND NOT $ENV{VT_ROOT} STREQUAL "" )

# If VAMPIRTRACE_INCLUDEDIR or VT_INC is defined in the environment, use it.
if ( NOT VAMPIRTRACE_INCLUDEDIR AND NOT $ENV{VAMPIRTRACE_INCLUDEDIR} STREQUAL "" )
  set( VAMPIRTRACE_INCLUDEDIR $ENV{VAMPIRTRACE_INCLUDEDIR} )
endif ( NOT VAMPIRTRACE_INCLUDEDIR AND NOT $ENV{VAMPIRTRACE_INCLUDEDIR} STREQUAL "" )

if ( NOT VAMPIRTRACE_INCLUDEDIR AND NOT $ENV{VT_INC} STREQUAL "" )
  set( VAMPIRTRACE_INCLUDEDIR $ENV{VT_INC} )
endif ( NOT VAMPIRTRACE_INCLUDEDIR AND NOT $ENV{VT_INC} STREQUAL "" )

# If VAMPIRTRACE_LIBRARYDIR was defined in the environment, use it.
if( NOT VAMPIRTRACE_LIBRARYDIR AND NOT $ENV{VAMPIRTRACE_LIBRARYDIR} STREQUAL "" )
  set( VAMPIRTRACE_LIBRARYDIR $ENV{VAMPIRTRACE_LIBRARYDIR} )
endif( NOT VAMPIRTRACE_LIBRARYDIR AND NOT $ENV{VAMPIRTRACE_LIBRARYDIR} STREQUAL "" )

if( NOT VAMPIRTRACE_LIBRARYDIR AND NOT $ENV{VT_LIB} STREQUAL "" )
  set( VAMPIRTRACE_LIBRARYDIR $ENV{VT_LIB} )
endif( NOT VAMPIRTRACE_LIBRARYDIR AND NOT $ENV{VT_LIB} STREQUAL "" )

if( VAMPIRTRACE_ROOT )
    set(VAMPIRTRACE_ENVVAR_INCLUDE_SEARCH_DIRS ${VAMPIRTRACE_ROOT}/include )
    set(VAMPIRTRACE_ENVVAR_LIBRARY_SEARCH_DIRS ${VAMPIRTRACE_ROOT}/lib )
endif( VAMPIRTRACE_ROOT )

if( VAMPIRTRACE_INCLUDEDIR )
  file(TO_CMAKE_PATH ${VAMPIRTRACE_INCLUDEDIR} VAMPIRTRACE_INCLUDEDIR)
  SET(VAMPIRTRACE_ENVVAR_INCLUDE_SEARCH_DIRS
    ${VAMPIRTRACE_INCLUDEDIR} )
endif( VAMPIRTRACE_INCLUDEDIR )

if( VAMPIRTRACE_LIBRARYDIR )
  file(TO_CMAKE_PATH ${VAMPIRTRACE_LIBRARYDIR} VAMPIRTRACE_LIBRARYDIR)
  SET(VAMPIRTRACE_ENVVAR_LIBRARY_SEARCH_DIRS
    ${VAMPIRTRACE_LIBRARYDIR} )
endif( VAMPIRTRACE_LIBRARYDIR )


# 1.b) Lets try also invoking PkgConfig to get hints

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    # this will set 
    # PKG_CONFIG_LIBVT_LIBRARY_DIRS
    # PKG_CONFIG_LIBVT_INCLUDE_DIRS
    pkg_check_modules(PKG_CONFIG_LIBVT QUIET libvt)
endif(PKG_CONFIG_FOUND)

# 1.c) Lets try to get command line tool an execute it

# search command line tools
find_program(VAMPIRTRACE_CXX vtcxx)
find_program(VAMPIRTRACE_CC vtcc)
find_program(VAMPIRTRACE_F90 vtf90)

# run vtcxx and try to extract include hints
execute_process(COMMAND ${VAMPIRTRACE_CXX} "-vt:showme_compile" RESULT_VARIABLE VAMPIRTRACE_COMMAND_SHOWME_COMPILE_RES OUTPUT_VARIABLE VAMPIRTRACE_COMMAND_SHOWME_COMPILE_OUTPUT)

if(NOT VAMPIRTRACE_COMMAND_SHOWME_COMPILE_RES)
    string(REGEX MATCHALL "[-][I]([^ ;\n])+" VAMPIRTRACE_COMMAND_INCLUDE_SEARCH_DIRS "${VAMPIRTRACE_COMMAND_SHOWME_COMPILE_OUTPUT}")
    string(REGEX REPLACE "-I" "" VAMPIRTRACE_COMMAND_INCLUDE_SEARCH_DIRS "${VAMPIRTRACE_COMMAND_INCLUDE_SEARCH_DIRS}")
endif(NOT VAMPIRTRACE_COMMAND_SHOWME_COMPILE_RES)

# run vtcxx and try to extract include hints
execute_process(COMMAND ${VAMPIRTRACE_CXX} "-vt:showme_link" RESULT_VARIABLE VAMPIRTRACE_COMMAND_SHOWME_LINK_RES OUTPUT_VARIABLE VAMPIRTRACE_COMMAND_SHOWME_LINK_OUTPUT)

if(NOT VAMPIRTRACE_COMMAND_SHOWME_LINK_RES)
    string(REGEX MATCHALL "[-][L]([^ ;\n])+" VAMPIRTRACE_COMMAND_LIBRARY_SEARCH_DIRS "${VAMPIRTRACE_COMMAND_SHOWME_LINK_OUTPUT}")
    string(REGEX REPLACE "-L" "" VAMPIRTRACE_COMMAND_LIBRARY_SEARCH_DIRS "${VAMPIRTRACE_COMMAND_LIBRARY_SEARCH_DIRS}")
endif(NOT VAMPIRTRACE_COMMAND_SHOWME_LINK_RES)

# 2. Now we search for the includes and libraries at the hints

# now find VAMPIRTRACE_INCLUDE_DIR
find_path(VAMPIRTRACE_INCLUDE_DIR 
          NAMES vt_user.h
          HINTS ${VAMPIRTRACE_ENVVAR_INCLUDE_SEARCH_DIRS}
                ${VAMPIRTRACE_COMMAND_INCLUDE_SEARCH_DIRS}
                ${PKG_CONFIG_LIBVT_INCLUDE_DIRS})

# now find VAMPIRTRACE_LIBRARY
find_library(VAMPIRTRACE_OTF_LIBRARY 
             NAMES otf
             HINTS ${VAMPIRTRACE_ENVVAR_LIBRARY_SEARCH_DIRS}
                   ${VAMPIRTRACE_COMMAND_LIBRARY_SEARCH_DIRS}
                   ${PKG_CONFIG_LIBVT_LIBRARY_DIRS})

find_library(VAMPIRTRACE_VT_LIBRARY 
             NAMES vt
             HINTS ${VAMPIRTRACE_ENVVAR_LIBRARY_SEARCH_DIRS}
                   ${VAMPIRTRACE_COMMAND_LIBRARY_SEARCH_DIRS}
                   ${PKG_CONFIG_LIBVT_LIBRARY_DIRS})

if (VAMPIRTRACE_VT_LIBRARY AND VAMPIRTRACE_OTF_LIBRARY)
    set( VAMPIRTRACE_LIBRARIES ${VAMPIRTRACE_VT_LIBRARY} ${VAMPIRTRACE_OTF_LIBRARY} )
endif()

# 3. set the variables
# handle the QUIETLY and REQUIRED arguments and set VAMPIRTRACE_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(VAMPIRTRACE  DEFAULT_MSG  VAMPIRTRACE_OTF_LIBRARY VAMPIRTRACE_VT_LIBRARY VAMPIRTRACE_INCLUDE_DIR VAMPIRTRACE_CXX VAMPIRTRACE_CC VAMPIRTRACE_F90)

mark_as_advanced(VAMPIRTRACE_INCLUDE_DIR VAMPIRTRACE_OTF_LIBRARY VAMPIRTRACE_VT_LIBRARY VAMPIRTRACE_CXX VAMPIRTRACE_CC VAMPIRTRACE_F90)
