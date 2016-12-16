# Dart Native-Library sample
> Some test around building native extensions for Dart

I started this project because of a very old and outdated documentation 
on the according site: https://www.dartlang.org/articles/dart-vm/native-extensions

You can find the native-part here on GH
   - [CPP-Master](https://github.com/MikeMitterer/cmake-dart-extension-master)
   
## Original Dart Documentation    
Because it is so outdated [2012](https://www.dartlang.org/articles/dart-vm/native-extensions) I try
to collect some useful information's on [CPP-Master](https://github.com/MikeMitterer/cmake-dart-extension-master)

If you have some tips, tricks or other useful information's please go to 
[CPP-Master](https://github.com/MikeMitterer/cmake-dart-extension-master), file an issue report
or add something to the [Wiki](https://github.com/MikeMitterer/cmake-dart-extension-master/wiki)! - **Thanks!**   
   
## Description
Two ways of testing this lib:

Command line:
- dart bin/random.dart


    pub global install <package> - does not work 

It produces "[Cannot load native extensions over http: or https:](https://github.com/dart-lang/sdk/issues/28137)"


RPC Server:

- dart bin/rpc.dart

RPC-API:

- http://localhost:8080/api/random/0.1/systemRand
- http://localhost:8080/api/random/0.1/systemRand/5
- http://localhost:8080/api/random/0.1/systemRand/seed/555
- http://localhost:8080/api/random/0.1/noScopeSystemRand 

## Project structure
I'm using this approach - the C++-Project is the root project and Dart as a side(or sub)-project

cmake does the heavy lifting and copies the native lib to the right place.
 
cmake-dart-extension-master:
 
    ├── CMakeLists.txt
    ├── README.md
    ├── dart
    │   ├── LICENSE
    │   ├── README.md
    │   ├── bin
    │   │   ├── random.dart
    │   │   └── rpc.dart
    │   ├── dart.iml
    │   ├── lib
    │   │   ├── native
    │   │   │   ├── libsample_extension.dylib
    │   │   │   ├── libsample_extension.so
    │   │   │   └── random.dart
    │   │   ├── rpcapi.dart
    │   │   └── src
    │   ├── pubspec.lock
    │   └── pubspec.yaml
    ├── include
    │   └── SampleProject.h
    ├── lib
    │   ├── libsample_extension.dylib
    │   └── mac
    │       ├── libsample_extension.dylib
    │       └── libsample_extension.so
    ├── src
    │   ├── NewCppClass.cpp
    │   ├── NewCppClass.h
    │   ├── SampleProject.cpp
    │   ├── SystemRand.cpp
    │   ├── SystemRand.h
    │   ├── dartInterface.cpp
    │   ├── dartInterface.h
    │   └── utils.h
    └── tools
        └── install-compiler.sh

### Conclusion so far (12 2016)
It's possible to write native extensions for Dart but you have to be a masochist to do this.  
