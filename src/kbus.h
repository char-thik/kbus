#pragma once

#include <stdint.h>

class kbus {
public:
  void feed(uint8_t data);
  uint8_t done();
  uint8_t geterror();
  uint8_t getaddr();
  uint8_t getrw();
  uint8_t getmode();
  uint8_t getsize();
  uint8_t getframe(uint8_t data);
};