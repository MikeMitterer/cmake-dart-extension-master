#!/usr/local/bin/dart

library random;

import "package:random/native/random.dart";

void main() async {
  print("systemRand:        ${systemRand()}");
  print("noScopeSystemRand: ${noScopeSystemRand()}");
  print("systemSrand:       ${systemSrand(100)}");

  final RandomArray array = new RandomArray();
  final List<int> values = await array.randomArray(20,10);

  values.forEach((final int value) => print("V $value"));
}
