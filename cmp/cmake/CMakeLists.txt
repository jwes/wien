project( luagi )

# Required cmake version
cmake_minimum_required( VERSION 2.8.7 )
enable_testing()

set( LIB_NAME ${PROJECT_NAME} )

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Modules" )
set( ROOT "${CMAKE_SOURCE_DIR}/../.." )
set( INC_DIR "${ROOT}/inc" )
set( SRC_DIR "${ROOT}/src" )
set( TST_DIR "${ROOT}/tst")

# add definitions
include( CustomFunctions )
include( DefineCMakeDefaults )
include( DefineCompilerFlags )

# file list
include( ${CMAKE_SOURCE_DIR}/FileLists.cmake )

find_package( Lua52 REQUIRED ) # LUA52_LIBRARIES / LUA52_INCLUDE_DIR
find_package( GIT2 "0.21.0" EXACT REQUIRED ) # GIT2_LIBRARIES / GIT2_INCLUDE_DIRS

########################################################################################################################
# build - make
########################################################################################################################
include_directories( ${INC_DIR} ${GIT2_INCLUDE_DIRS} )

add_library( ${LIB_NAME} SHARED ${SRC_FILES} )
target_link_libraries( ${LIB_NAME} m ${LUA52_LIBRARIES} ${GIT2_LIBRARIES} )

########################################################################################################################
# install - make install
########################################################################################################################
# install( TARGETS ${LIB_NAME} DESTINATION lib )