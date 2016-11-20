library lib.random;

import 'dart:async';
import 'dart:isolate';
import 'dart-ext:sample_extension';

// The simplest way to call native code: top-level functions.
int systemRand() native "SystemRand";

int noScopeSystemRand() native "NoScopeSystemRand";

bool systemSrand(int seed) native "SystemSrand";

// A class caches the native port used to call an asynchronous extension.
class RandomArray {
    static SendPort _port;

    Future<List<int> > randomArray(int seed, int length) {
        var completer = new Completer();
        var replyPort = new RawReceivePort();
        var args = new List(3);

        args[0] = seed;
        args[1] = length;
        args[2] = replyPort.sendPort;

        _servicePort.send(args);
        replyPort.handler = (result) {
            replyPort.close();
            if (result != null) {
                completer.complete(result);
            } else {
                completer.completeError(new Exception("Random array creation failed"));
            }
        };
        return completer.future;
    }

    SendPort get _servicePort {
        if (_port == null) {
            _port = _newServicePort();
        }
        return _port;
    }

    SendPort _newServicePort() native "RandomArray_ServicePort";
}