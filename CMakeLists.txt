cmake_minimum_required( VERSION 3.14 )

### Disable in-source build
set( CMAKE_DISABLE_IN_SOURCE_BUILD ON )
set( CMAKE_DISABLE_SOURCE_CHANGES  ON )
if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}" )
  message( SEND_ERROR "In-source builds are not allowed." )
endif ()

project( TreeExample LANGUAGES CXX )

########
### Misc
########
set( CMAKE_VERBOSE_MAKEFILE ON )
set( CMAKE_COLOR_MAKEFILE ON )
set( CMAKE_CXX_STANDARD 17 )
if(!WIN32)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++17 -O0 -DLINUX_TERMINAL" )
else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17" )
endif()
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_INSTALL_PREFIX           ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )

#########
### Boost
#########
# set( Boost_NO_SYSTEM_PATHS ON )
set( Boost_DETAILED_FAILURE_MSG ON )
set( Boost_DEBUG ON )
set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )

if( WIN32 )
    set( BOOST_ROOT         "c:/Boost" )
    set( BOOST_LIBRARYDIR   "c:/Boost/lib" )
    set( BOOST_INCLUDEDIR   "c:/Boost/include" )
endif( WIN32 )

find_package( Boost 1.70 
COMPONENTS 
    program_options 
    date_time 
REQUIRED )

if (Boost_FOUND)
    message( "Boost headers : " ${Boost_INCLUDE_DIR} )
    message( "Boost libs : " ${Boost_LIBRARIES} )
    include_directories( ${Boost_INCLUDE_DIR} )
    add_definitions( "-DHAS_BOOST" )
else()
    message( "!!! Boost didn't found !!!" )
endif()

########
### Test
########
if(WIN32)
    set( EXECUTABLE_NAME ${PROJECT_NAME}Test )
    message( "Configuring example : ${EXECUTABLE_NAME}" )
else()
    set( EXECUTABLE_NAME ${PROJECT_NAME}Test.out )
    message( "Configuring example : ${EXECUTABLE_NAME}" )
endif()

include_directories( ${Boost_INCLUDE_DIR} )
file( GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
add_executable(
    ${EXECUTABLE_NAME}
    ${CXX_FILES}
)
target_link_libraries(
    ${EXECUTABLE_NAME}
LINK_PRIVATE
    ${Boost_LIBRARIES}
)
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 17)