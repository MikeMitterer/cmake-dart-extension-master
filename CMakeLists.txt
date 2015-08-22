# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 2.8.12)
project(dartMaster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# add_compile_options("-Wall")
# add_compile_options("-Wextra")

# C++14: set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set( LIBRARY_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib")

# Set the output directory for executable
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_HOME_DIRECTORY}/bin )

# ┌──────────────────────────────────────────────────────────────────┐
# │  Main-Config (Architecture,...)                                  │
# └──────────────────────────────────────────────────────────────────┘

# Architecture (32/64 bit)
set(X64 OFF)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(X64 ON)
endif()
message ("Architecture is 64Bit - ${X64}")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Qt                                                              │
# └──────────────────────────────────────────────────────────────────┘

if (DEFINED ENV{QT5DIR})
    set(CMAKE_PREFIX_PATH $ENV{QT5DIR} ${CMAKE_PREFIX_PATH})
else ()
    message (FATAL_ERROR "ERROR: Environment variable QT5DIR is not set. Please locate your Qt folder MY_QT5_DIR.")
endif ()


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
#find_package(Qt5Widgets REQUIRED)


# ┌──────────────────────────────────────────────────────────────────┐
# │  Doxygen                                                         │
# └──────────────────────────────────────────────────────────────────┘

find_package(Doxygen)

if(DOXYGEN_FOUND)

  add_custom_target(doc ${DOXYGEN_EXECUTABLE} WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY} )
  message("Doxygen was found! (${DOXYGEN_EXECUTABLE})")

else(DOXYGEN_FOUND)

  message(STATUS "Doxygen not found - Documentation will not be generated")

endif(DOXYGEN_FOUND)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Extension                                                       │
# └──────────────────────────────────────────────────────────────────┘

add_subdirectory (extension)

find_library(extension_location extension)
message("Found extension at: ${extension_location}")

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source file                                                     │
# └──────────────────────────────────────────────────────────────────┘

file(GLOB_RECURSE source src/*.cpp)
include_directories(src)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Applications  (entry points)                                    │ 
# └──────────────────────────────────────────────────────────────────┘

# FractalCreation
add_executable(dartMaster
	app/myApplication.cpp

	${source} src/app/ArgParser.cpp src/app/ArgParser.h
        src/app/test/Name.cpp
        src/app/test/Name.h)

TARGET_LINK_LIBRARIES(dartMaster sample_extension)

qt5_use_modules(dartMaster Widgets)