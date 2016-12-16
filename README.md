# cmake-dart-extension-master
A quick and simple example for using CMAKE to build Dart native extension.

It is essentially for my own usage, but I'd be happy if it is useful to someone else.
I am open to improvement and contributions.

## Prepare your machine to build the LIB

This project uses "Config" and "configDart" CMake-File for configuration. You can 
find these file as usual on [GitHub](https://github.com/MikeMitterer/cmake)

```cmake
    cmake_minimum_required(VERSION 3.6)
    
    # ENV is defined in .bashrc
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
    #...
```

## Prerequisites 
   - cmake
   - clang (I'm using clang 8 on Mac and 3.8 on Linux)
   - Dart

## What to do next
   - Go to [https://github.com/MikeMitterer/cmake-dart-extension-master](https://github.com/MikeMitterer/cmake-dart-extension-master)  
   Clone the repo
      
   - Go to [https://github.com/MikeMitterer/cmake](https://github.com/MikeMitterer/cmake)  
   Clone the repo (You need Config.cmake, configDart.cmake and FindSpdlog.cmake)
             
   - Add the cmake-folder to your CMAKE_MODULE_PATH
   Something like this:
   
      
        export DEVCPP="/Volumes/Daten/DevLocal/DevCPP"
        export CMAKE_MODULE_PATH="${DEVCPP}/cmake"
   
   - cd to "cmake-dart-extension-master"  
   We add dependencies to spdlog. If you want to know why I use this approach - check
   out this website [Dependency management for C++ with CMake and Git](https://foonathan.github.io/blog/2016/07/07/cmake-dependency-handling.html)
   
     - mkdir .dependencies
   
     - cd .dependencies
     git submodule add https://github.com/gabime/spdlog
   
     - cd back to cmake-dart-extensions-master
     git submodule update --init -- .dependencies/spdlog
    
   
   - mkdir "build" (If it does not already exist)   
   If it exists - `rm -f build && mkdir build && cd build && cmake .. && make`   
   
   **This should build the native lib on your system and copy it to _dart/lib/native_ ** 

### Why spdlog
I am just curios how it plays together with Dart + native extensions...          
    
    
### Hint
Install [entr](http://entrproject.org/)  

cd to "bin" and enter:
```bash
    ls * | entr ./dartMaster -p
```
Every time "dartMaster" changes "entr" calls `dartMaster -q` - nice for testing!
     
