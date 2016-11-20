#!/usr/local/bin/dart

library random;

import "package:random/native/random.dart";

void main() {
  print("systemRand:        ${systemRand()}");
  print("noScopeSystemRand: ${noScopeSystemRand()}");
  print("systemSrand:       ${systemSrand(100)}");

  final RandomArray array = new RandomArray();
  array.randomArray(20,10).then((final List<int> values) {
    values.forEach((final int value) => print("V $value"));
  });
}
