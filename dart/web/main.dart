import 'dart:html';
import "package:random/random.dart";

void main() {
  final int srand = systemRand();
  querySelector('#RipVanWinkle').text = 'Wake up, sleepy head! - $srand';
}