#include <Wire.h>
#define MPU 0x68

int16_t rd() {
  int16_t hi = Wire.read();
  int16_t lo = Wire.read();
  return (hi << 8) | lo;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  Wire.beginTransmission(MPU); Wire.write(0x6B); Wire.write(0x00); Wire.endTransmission(true);
  Wire.beginTransmission(MPU); Wire.write(0x1C); Wire.write(0x18); Wire.endTransmission(true);

void loop() {
  Wire.beginTransmission(MPU); Wire.write(0x3B); Wire.endTransmission(false);
  Wire.requestFrom((uint16_t)MPU, (uint8_t)6, true);
  float ax = rd() / 2048.0, ay = rd() / 2048.0, az = rd() / 2048.0;
  float a = sqrt(ax*ax + ay*ay + az*az);
  Serial.printf("ax=%.2f ay=%.2f az=%.2f |a|=%.2f g\n", ax, ay, az, a);
  delay(1000);
}