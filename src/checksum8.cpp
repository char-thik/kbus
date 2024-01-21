#include "checksum8.h"

uint16_t checksum8(uint8_t data[], uint8_t size) {
  uint16_t checksum = 0;
  uint8_t i = 0;
  for (i = 0;; i++) {
    checksum = data[i] + checksum;
    if (i == size) {
      break;
    }
  }
  return checksum;
}