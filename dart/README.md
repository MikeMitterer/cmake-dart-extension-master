# Dart Native-Library sample
> Some test around building native extensions for Dart

I started this project because of a very old and outdated documentation 
on the according site: https://www.dartlang.org/articles/dart-vm/native-extensions

You can find the native-part here on GH
   - https://github.com/MikeMitterer/cmake-dart-extension-master
      
## Description
Two ways of testing this lib:

Command line:
- dart bin/random.dart

RPC Server:

- dart bin/rpc.dart

RPC-API:

- http://localhost:8080/api/random/0.1/systemRand
- http://localhost:8080/api/random/0.1/systemRand/5
- http://localhost:8080/api/random/0.1/systemRand/seed/555
- http://localhost:8080/api/random/0.1/noScopeSystemRand 

