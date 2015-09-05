# cmake-dart-extension-master
A quick and simple example for using CMAKE to build Dart native extension.

It is essentially for my own usage, but I'd be happy if it is useful to someone else.
I am open to improvement and contributions.

## Prepare your machine to build the LIB
## Mac
```bash
    brew install cmake
    
    # Compiler should be already on your system!
    # If not:
        # brew install gcc
        # or install XCode
        
    # For testing!
    brew install qt5
```

## Linux (Tested Linux Mint 17.2)
```bash
    apt-get update
    
    # Install g++ compiler (5.x) 
    # More on: http://www.techerina.com/2015/04/installing-upgrading-gcc-in-ubuntu-linuxmint-machine.html
    # Or check out the script in "tools"

    add-apt-repository ppa:ubuntu-toolchain-r/test
    apt-get update
    cd tools
    chmod 700 install-compiler.sh
    ./install-compiler.sh
    
    # Install cmake 3.x
    add-apt-repository ppa:george-edison55/cmake-3.x
    apt-get update
    apt-get install cmake
                    
    # For testing!
    apt-get install qt5-default
```

### Usage

```bash

    # Create build directory
    mkdir build
    
    # CD into the build dir
    cd build
    
    # Now generate all the necessary file and build your lib 
    cmake .. && make
    
    # Test your lib with Dart
    cd ..
    cd dart
    dart bin/random.dart
    
```
#### Clean rebuild

```bash

    cd build
    rm -rf * && cmake .. && make
```     
    
    
### hint
Install [entr](http://entrproject.org/)  

cd to "bin" and enter:
```bash
    ls * | entr ./dartMaster -p
```
Every time "dartMaster" changes "entr" calls `dartMaster -q` - nice for testing!
     
