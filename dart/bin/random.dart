#!/usr/local/bin/dart

library native_sample;

import 'dart:async';
import "package:native_sample/native/random.dart";

Future main() async {
  print("systemRand:        ${systemRand()}");
  print("noScopeSystemRand: ${noScopeSystemRand()}");
  print("systemSrand:       ${systemSrand(100)}");

  final RandomArray array = new RandomArray();
  final List<int> values = await array.randomArray(20,10);

  values.forEach((final int value) => print("V $value"));
}
