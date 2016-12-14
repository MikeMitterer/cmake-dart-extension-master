# ┌──────────────────────────────────────────────────────────────────┐
# │  Basis für CMAKE                                                 │
# │                                                                  │
# │  Extension Settings                                              │
# │    Useful Vars: http://www.cmake.org/Wiki/CMake_Useful_Variables │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.6)

# ENV ist im .bashrc definiert
#   ( cmake-configs on GH: https://github.com/MikeMitterer/cmake)
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

project(sample_extension)

# Output bin, c++11 usw
include(Config)

# Only necessary if this module has QT-Siblings
set(CMAKE_AUTOMOC OFF)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Dart (Make sure you have '-std=c++11' for CMAKE_CXX_FLAGS       │
# └──────────────────────────────────────────────────────────────────┘

include(configDart)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} ${dart_CXX_ARCHITECTURE_FLAGS} \
        -Wl,-undefined,dynamic_lookup -I${dart_SDK}"
)
# SET(CMAKE_SHARED_LINKER_FLAGS    "-Wl,-undefined,dynamic_lookup")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source file                                                     │
# └──────────────────────────────────────────────────────────────────┘

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SOURCE_FILES ${SOURCE_FILES}
    src/dartInterface.cpp
    src/SystemRand.cpp
    )

# ┌──────────────────────────────────────────────────────────────────┐
# │  Library (entry points)                                          │
# └──────────────────────────────────────────────────────────────────┘


add_library (${PROJECT_NAME} SHARED
    ${SOURCE_FILES}
    )

target_include_directories(${PROJECT_NAME} PUBLIC ${dart_SDK})

message(STATUS "ParentDir:             " ${PARENT_DIR})

add_custom_target(DartLib ALL
        COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${PROJECT_NAME}>"
        "${dart_TARGET}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"

        COMMENT "Copying LIB to ${dart_TARGET}"
)
