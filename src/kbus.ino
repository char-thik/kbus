#include "kbus.h"

// #define PRINT

unsigned long timer;
int bytespersecond, bytespersecond1;
kbus kbus;
void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    bytespersecond++;
    uint8_t temp = Serial.read();
    kbus.feed(temp);
  }
  if (kbus.done()) {
    Serial.print("HEADER : ");
    Serial.print(kbus.getframe(0));
    Serial.write(',');
    Serial.print(kbus.getframe(1));
    Serial.print("   ADDR : ");
    Serial.print(kbus.getaddr());
    Serial.print("   R/W : ");
    Serial.print(kbus.getrw());
    Serial.print("   MODE : ");
    Serial.write(kbus.getmode());
    Serial.print("   SIZE : ");
    Serial.print(kbus.getsize());
    Serial.print("   DATA : ");
    for (int i = 0; i < kbus.getsize(); i++) {
      Serial.write(char(kbus.getframe(i + 5)));
    }
    Serial.print("   CHECKSUM : ");
    uint8_t checksum_l;
    uint8_t checksum_h;
    Serial.print((kbus.getframe(kbus.getframe(4) - 1 + 6) << 8) | kbus.getframe(kbus.getframe(4) + 6));
    Serial.print("   SPEED : ");
    Serial.print(bytespersecond1);
    Serial.print("B/s\n");
  }
  int er=kbus.geterror();
  if (er & 0B10) {
    Serial.print("HEADER 1 error\n");
  }
  if (er & 0B100) {
    Serial.print("HEADER 1 repeat error\n");
  }
  if (er & 0B1000) {
    Serial.print("HEADER 2 error\n");
  }
  if (er & 0B10000) {
    Serial.print("CHECKSUM error\n");
  }
  if (millis() - timer >= 1000) {
    bytespersecond1 = bytespersecond;
    bytespersecond = 0;
    timer = millis();
  }
}
