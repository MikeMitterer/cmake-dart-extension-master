#!/usr/local/bin/dart

library random;

import "package:random/random.dart";

void main() {
  print(systemRand());

  final RandomArray array = new RandomArray();
  array.randomArray(20,10).then((final List<int> values) {
    values.forEach((final int value) => print("V $value"));
  });
}
