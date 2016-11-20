//
// Created by Mike Mitterer on 20.11.16.
//

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <dart_api.h>
#include <dart_native_api.h>
#include <array>
#include <vector>

#include "utils.h"

void wrappedRandomArray(Dart_Port dest_port_id, Dart_CObject* message);
std::vector<uint8_t> randomArray(int32_t seed, int32_t length) ;

/**
 * DartCode:
 *  int systemRand() native "SystemRand";
 */
void SystemRand(Dart_NativeArguments arguments) {
    Dart_EnterScope();
    std::cout << "SystemRand.." << std::endl;

    Dart_Handle result = HandleError(Dart_NewInteger(rand()));
    Dart_SetReturnValue(arguments, result);
    Dart_ExitScope();
}

/**
 * DartCode:
 *   bool systemSrand(int seed) native "SystemSrand";
 */
void SystemSrand(Dart_NativeArguments arguments) {
    Dart_EnterScope();
    bool success = false;

    Dart_Handle seed_object = HandleError(Dart_GetNativeArgument(arguments, 0));
    if (Dart_IsInteger(seed_object)) {

        bool fits;
        HandleError(Dart_IntegerFitsIntoInt64(seed_object, &fits));
        if (fits) {
            int64_t seed;
            HandleError(Dart_IntegerToInt64(seed_object, &seed));
            srand(static_cast<unsigned>(seed));
            success = true;
        }

    }
    Dart_SetReturnValue(arguments, HandleError(Dart_NewBoolean(success)));
    Dart_ExitScope();
}

/**
 * DartCode:
 *  SendPort _newServicePort() native "RandomArray_ServicePort";
 */
void randomArrayServicePort(Dart_NativeArguments arguments) {
    Dart_EnterScope();
    Dart_SetReturnValue(arguments, Dart_Null());
    Dart_Port service_port = Dart_NewNativePort("RandomArrayService", wrappedRandomArray, true);

    if (service_port != ILLEGAL_PORT) {
        Dart_Handle send_port = HandleError(Dart_NewSendPort(service_port));
        Dart_SetReturnValue(arguments, send_port);
    }

    Dart_ExitScope();
}

void wrappedRandomArray(Dart_Port dest_port_id, Dart_CObject* message) {
    Dart_Port reply_port_id = ILLEGAL_PORT;

    if (message->type == Dart_CObject_kArray && 3 == message->value.as_array.length) {

        // Use .as_array and .as_int32 to access the data in the Dart_CObject.
        Dart_CObject* param0 = message->value.as_array.values[0];
        Dart_CObject* param1 = message->value.as_array.values[1];
        Dart_CObject* param2 = message->value.as_array.values[2];

            if (param0->type == Dart_CObject_kInt32 &&
                param1->type == Dart_CObject_kInt32 &&
                param2->type == Dart_CObject_kSendPort) {

                int32_t seed = param0->value.as_int32;
                int32_t length = param1->value.as_int32;
                reply_port_id = param2->value.as_send_port.id;

                // It is OK that result is destroyed when function exits.
                // Dart_PostCObject has copied its data.
                std::vector<uint8_t> values = randomArray(seed, length);

                Dart_CObject result;

                result.type = Dart_CObject_kTypedData;
                result.value.as_typed_data.type = Dart_TypedData_kUint8;
                result.value.as_typed_data.values = values.data();
                result.value.as_typed_data.length = length;

                Dart_PostCObject(reply_port_id, &result);
                return;
            }


    }

    Dart_CObject result;
    result.type = Dart_CObject_kNull;
    Dart_PostCObject(reply_port_id, &result);
}

std::vector<uint8_t> randomArray(int32_t seed, int32_t length) {
    if(length <= 0 || length > 10000000) {
        throw std::runtime_error("Size for randomArray must be > 0 and < 10000000 but was "
            + std::to_string(length));
    }

    std::vector<uint8_t> values;
    srand(static_cast<unsigned int>(seed));
    for (int i = 0; i < length; i++) {
        values.push_back(static_cast<uint8_t>(rand() % 256));
    }

    return values;
}
