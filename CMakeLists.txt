cmake_minimum_required( VERSION 3.14 )

set( CMAKE_DISABLE_IN_SOURCE_BUILD ON )
set( CMAKE_DISABLE_SOURCE_CHANGES  ON )

project( TreeExample LANGUAGES CXX )

if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}" )
  message( SEND_ERROR "In-source builds are not allowed." )
endif ()

########
### Misc
########
# set( CMAKE_VERBOSE_MAKEFILE ON )
set( CMAKE_COLOR_MAKEFILE ON )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++17 -O0 -DLINUX_TERMINAL" )
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_INSTALL_PREFIX           ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )

#########
### Boost
#########
# message( "Provided BOOSTROOT : " ${BOOSTROOT} )
# set( Boost_NO_SYSTEM_PATHS ON )
find_package( Boost 1.70 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
message( "Found boost : " ${Boost_INCLUDE_DIR} )

########
### Test
########
message( "Configuring example : " ${PROJECT_NAME}Test.out )

#find_package( Boost 1.71.0 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
message( "Located boost libs : " ${Boost_LIBRARIES} )

file( GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
add_executable(
    ${PROJECT_NAME}Test.out
    ${CXX_FILES}
)
target_link_libraries(
    ${PROJECT_NAME}Test.out
LINK_PRIVATE
    ${Boost_LIBRARIES}
)