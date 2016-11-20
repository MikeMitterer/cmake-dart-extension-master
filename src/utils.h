//
// Created by Mike Mitterer on 20.11.16.
//

#ifndef _HELLO_DART_UTILS_H_
#define _HELLO_DART_UTILS_H_

Dart_Handle HandleError(Dart_Handle handle);
Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope);

#endif //_HELLO_DART_UTILS_H_
