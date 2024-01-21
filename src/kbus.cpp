#include "kbus.h"
#include "checksum8.h"

#define HEADER1 0x20
#define HEADER2 0x40

uint8_t error = 1;
uint8_t frame[255] = { 0 };
uint8_t done_flag;
uint8_t error_flag;

void kbus::feed(uint8_t data) {
  error = 0B1;
  static uint8_t frame_length = 0;
  static uint8_t frame_index = 0;
  if (frame_index == 0 && data != HEADER1) {
    frame_index = 0;
    error |= 0B10;
    return;
  }
  if (frame_index == 1 && data == HEADER1) {
    frame_index = 1;
    error |= 0B100;
    return;
  }
  if (frame_index == 1 && data != HEADER2) {
    frame_index = 0;
    error |= 0B1000;
    return;
  }
  if (frame_index == 4) {//size index
    frame_length = data + 6;
  }

  frame[frame_index++] = data;


  if (frame_length > 0) {
    if (frame_index > frame_length) {
      uint16_t sum = (frame[frame_length - 1] << 8) | frame[frame_length];
      if (checksum8(frame, frame_length - 2) == sum) {
        error = 0;
      } else {
        error |= 0B10000;
      }
      frame_length = 0;
      frame_index = 0;
    }
  } else if (frame_index > 4) {
    frame_index = 0;
    frame_length = 0;
  }
}
uint8_t kbus::done() {
  done_flag = 0;
  if (!error) {
    done_flag = 1;
    error = 0B1;
  }
  return done_flag;
}
uint8_t kbus::geterror() {
  error_flag = error;
  error = 0B1;
  return error_flag;
}
uint8_t kbus::getaddr() {
  return (frame[2] >> 0x01);
}
uint8_t kbus::getrw() {
  return (frame[2] & 0x01);
}
uint8_t kbus::getmode() {
  return frame[3];
}
uint8_t kbus::getsize() {
  return frame[4];
}
uint8_t kbus::getframe(uint8_t data) {
  return frame[data];
}