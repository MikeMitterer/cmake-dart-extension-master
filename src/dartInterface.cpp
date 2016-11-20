// Copyright (c) 2012, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <dart_api.h>
#include <dart_native_api.h>
#include "utils.h"
#include "SystemRand.h"

struct FunctionLookup {
    const char *name;
    Dart_NativeFunction function;
};

/**
 * DartCode:
 *  import 'dart-ext:native/sample_extension';
 */
DART_EXPORT Dart_Handle sample_extension_Init(Dart_Handle parent_library) {
    std::cout << "sample_extension_Init" << std::endl;

    if (Dart_IsError(parent_library)) {
        return parent_library;
    }


    Dart_Handle result_code = Dart_SetNativeResolver(parent_library, ResolveName, NULL);
    if (Dart_IsError(result_code)) {
        return result_code;
    }

    return Dart_Null();
}

Dart_Handle HandleError(Dart_Handle handle) {
    if (Dart_IsError(handle)) {
        Dart_PropagateError(handle);
    }
    return handle;
}


FunctionLookup function_list[] = {
        {"SystemRand",              SystemRand},
        {"SystemSrand",             SystemSrand},
        {"RandomArray_ServicePort", randomArrayServicePort},
        {NULL, NULL}};


FunctionLookup no_scope_function_list[] = {
        {"NoScopeSystemRand", SystemRand},
        {NULL, NULL}
};

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool *auto_setup_scope) {
    if (!Dart_IsString(name)) {
        return NULL;
    }
    Dart_NativeFunction result = NULL;
    if (auto_setup_scope == NULL) {
        return NULL;
    }

    Dart_EnterScope();
    const char *cname;
    HandleError(Dart_StringToCString(name, &cname));

    for (int i = 0; function_list[i].name != NULL; ++i) {
        if (strcmp(function_list[i].name, cname) == 0) {
            *auto_setup_scope = true;
            result = function_list[i].function;
            break;
        }
    }

    if (result != NULL) {
        Dart_ExitScope();
        return result;
    }

    for (int i = 0; no_scope_function_list[i].name != NULL; ++i) {
        if (strcmp(no_scope_function_list[i].name, cname) == 0) {
            *auto_setup_scope = false;
            result = no_scope_function_list[i].function;
            break;
        }
    }

    Dart_ExitScope();
    return result;
}
