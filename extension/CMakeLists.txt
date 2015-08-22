# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.2)
project(sample_extension)

if(NOT DEFINED LIBRARY_OUTPUT_DIRECTORY)
    set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
endif()
message( "Library ouput path: ${LIBRARY_OUTPUT_DIRECTORY}")

# Set the output directory for library
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY} )

# Add this lib to the projects SEARCH-Path for LIBs
list(APPEND CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LIB ${PROJECT_NAME})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Dart                                                            │
# └──────────────────────────────────────────────────────────────────┘

# Get path to Dart's SDK.
if ($ENV{DART_SDK})
    set(DART_SDK $ENV{DART_SDK})

else ($ENV{DART_SDK})
    # Get full path to the Dart executable.
    execute_process(COMMAND which dart OUTPUT_VARIABLE DART_EXEC OUTPUT_STRIP_TRAILING_WHITESPACE)

    if (NOT DART_EXEC)
        message(FATAL_ERROR "Error: Unable to find dart executable!")
    endif (NOT DART_EXEC)

    # Expand symlinks.
    get_filename_component(DART_EXEC ${DART_EXEC} REALPATH)

    get_filename_component(DART_SDK ${DART_EXEC}/../.. ABSOLUTE)

    if (NOT DART_SDK)
        message(FATAL_ERROR "Error: Unable to find dart-sdk!!!")
    endif (NOT DART_SDK)

endif ($ENV{DART_SDK})

set( DART_INCLUDE "${DART_SDK}/include")

message(STATUS "DART_SDK:            " ${DART_SDK})
message(STATUS "DART_INCLUDE:        " ${DART_INCLUDE})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Dart II (SystemInfo)                                            │
# └──────────────────────────────────────────────────────────────────┘

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE(STATUS "64 bits compiler detected" )
    SET( EX_PLATFORM 64 )
    SET( EX_PLATFORM_NAME "x64" )
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE(STATUS "32 bits compiler detected" )
    SET( EX_PLATFORM 32 )
    SET( EX_PLATFORM_NAME "x86" )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

message(STATUS "System name:           " ${CMAKE_SYSTEM_NAME})
message(STATUS "Platform:              " ${EX_PLATFORM})
message(STATUS "Platform Name:         " ${EX_PLATFORM_NAME})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

    if (${EX_PLATFORM} EQUAL "32")

        set(CXX_ARCHITECTURE_FLAGS "-arch i386")

    elseif (${EX_PLATFORM} EQUAL "64")

        set(CXX_ARCHITECTURE_FLAGS "-arch x86_64")

    endif (${EX_PLATFORM} EQUAL "32")

else (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    if (${EX_PLATFORM} EQUAL "32")

        set(CXX_ARCHITECTURE_FLAGS "-m32")

    elseif (${EX_PLATFORM} EQUAL "64")

        set(CXX_ARCHITECTURE_FLAGS "-m64")

    endif (${EX_PLATFORM} EQUAL "32")

endif (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

message(STATUS "Architectural Flags:   " ${CXX_ARCHITECTURE_FLAGS})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source file                                                     │
# └──────────────────────────────────────────────────────────────────┘

file(GLOB_RECURSE source src/*.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Library (entry points)                                          │
# └──────────────────────────────────────────────────────────────────┘

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -arch x86_64 -Wl,-undefined,dynamic_lookup -I${DART_SDK}")
SET(CMAKE_SHARED_LINKER_FLAGS    "-Wl,-undefined,dynamic_lookup")

add_library (${LIB} SHARED ${source}
        src/NewCppClass.cpp src/NewCppClass.h
        src/dartInterface.cpp src/dartInterface.h)

target_include_directories(${LIB} PUBLIC ${DART_SDK})

set( TARGET_DIR "${CMAKE_HOME_DIRECTORY}/dart/lib/native")
add_custom_command(TARGET ${LIB} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${LIB}>" "${TARGET_DIR}/$<TARGET_FILE_NAME:${LIB}>"
        COMMENT "Copying LIB to ${TARGET_DIR}"
)
