# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# │    Useful Vars: http://www.cmake.org/Wiki/CMake_Useful_Variables │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.2)
project(dartMaster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# add_compile_options("-Wall")
# add_compile_options("-Wextra")

# C++14: set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX1Y)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
	message(STATUS "C++14 Compiler")
elseif(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	message(STATUS "C++11 Compiler")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	message(STATUS "OLD! C++11 Compiler")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set( LIBRARY_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib")

# Set the output directory for binaries
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )

# CMakeLists.txt - home
message(STATUS "BASEDir:               ${CMAKE_CURRENT_SOURCE_DIR}" )
message(STATUS "BinDir:                ${CMAKE_BINARY_DIR}" )
message(STATUS "Project-Dir:           ${PROJECT_BINARY_DIR}" )

# Project - home (Path to top of source tree)
message(STATUS "Extension-CMake Home:   ${CMAKE_HOME_DIRECTORY}" )

# ┌──────────────────────────────────────────────────────────────────┐
# │  Main-Config (Architecture,...)                                  │
# └──────────────────────────────────────────────────────────────────┘

# Architecture (32/64 bit)
set(X64 OFF)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(X64 ON)
endif()
message (STATUS "Architecture is 64Bit - ${X64}")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Qt                                                              │
# └──────────────────────────────────────────────────────────────────┘

if (DEFINED ENV{QT5DIR})
   set(CMAKE_PREFIX_PATH $ENV{QT5DIR} ${CMAKE_PREFIX_PATH})
# else ()
#    message (FATAL_ERROR "ERROR: Environment variable QT5DIR is not set. Please locate your Qt folder QT5DIR.")
endif ()


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
#find_package(Qt5Widgets REQUIRED)

message(STATUS "Qt5Core found at:                ${Qt5Core_DIR}")

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Core_INCLUDES})

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

add_subdirectory ( dart/extension )

find_library(DART_LIBRARY
        NAMES sample_extension
        HINTS "${CMAKE_CURRENT_SOURCE_DIR}/dart/extension/lib"
)
get_filename_component(DART_EXTENSION_LIB ${DART_LIBRARY} DIRECTORY)
get_filename_component(DART_EXTENSION ${DART_EXTENSION_LIB} DIRECTORY)

message(STATUS "Found extension at:    ${DART_EXTENSION}")
message(STATUS "Found extension lib:   ${DART_LIBRARY}")

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source file                                                     │
# └──────────────────────────────────────────────────────────────────┘

file(GLOB_RECURSE source src/*.cpp)
include_directories(src)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Applications  (entry points)                                    │ 
# └──────────────────────────────────────────────────────────────────┘

# set default linke options!
set(CMAKE_LINKER_OPTIONS "")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    # using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    # -unresolved-symbols=ignore-in-shared-libs
    # Avoids "Nicht definierter Verweis auf `Dart_GetNativeArgument'" linker error
    set(CMAKE_LINKER_OPTIONS "-Wl,-unresolved-symbols=ignore-in-shared-libs")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_LINKER_OPTIONS}")

add_executable(dartMaster
	app/myApplication.cpp

	${source} src/app/ArgParser.cpp src/app/ArgParser.h
        src/app/test/Name.cpp
        src/app/test/Name.h)

target_link_libraries(dartMaster
        sample_extension
)

# The qt5_use_modules CMake function encapsulates all of
# the set-up required to use a Qt module.
qt5_use_modules(dartMaster Widgets)
