// Copyright (c) 2014, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

library rpcapi;
import 'dart:async';
import "dart:math" as Math;

import 'package:rpc/rpc.dart';
import "package:random/random.dart";

class RndResponse {
    int result;
    RndResponse();
}

class ToyResourceResponse {
    String result;

    ToyResourceResponse();
}

class NestedResponse {
    String nestedResult;

    NestedResponse();
}

class ToyMapResponse {
    String result;
    Map<String, NestedResponse> mapResult;

    ToyMapResponse();
}

class ToyRequest {
    @ApiProperty(required: true)
    String name;

    @ApiProperty(defaultValue: 1000)
    int age;
}

class ToyAgeRequest {
    @ApiProperty(defaultValue: 1000)
    int age;
}

@ApiClass(version: '0.1')
class Random {

    Random();

    @ApiMethod(path: 'noop')
    VoidMessage noop() {
        return null;
    }

    @ApiMethod(path: 'systemRand')
    RndResponse getSystemRand() { return new RndResponse()..result = systemRand(); }

    @ApiMethod(path: 'noScopeSystemRand')
    RndResponse getNoScopeSystemRand() { return new RndResponse()..result = noScopeSystemRand(); }

    @ApiMethod(path: 'systemRand/seed/{seed}')
    RndResponse helloNameAge(int seed) {
        systemSrand(seed);
        return new RndResponse()..result = systemRand();
    }

    @ApiMethod(path: 'systemRand/{elements}')
    Future<List<RndResponse>> getArray(int elements) async {
        final RandomArray array = new RandomArray();
        int seed = new DateTime.now().millisecondsSinceEpoch;

        seed = seed - 1441559000000;
        elements = Math.min(Math.max(1,elements),999);

        final List<int> values = await array.randomArray(seed,elements); // DateTime.now().millisecondsSinceEpoch

        final List<RndResponse> response = new List<RndResponse>();

        values.forEach((final int value) {
            final RndResponse result = new RndResponse()..result = value;
            response.add(result);
        });

        return response;
    }


}
