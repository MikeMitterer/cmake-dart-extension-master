# cmake-dart-extension-master
A quick and simple example for using CMAKE to build Dart native extension.

It is essentially for my own usage, but I'd be happy if it is useful to someone else.
I am open to improvement and contributions.

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
    ls * | entr ./qtCmdline -p
```
Every time "qtCmdline" changes "entr" calls `qtCmdline -q` - nice for testing!
     
