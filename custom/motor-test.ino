#include <Motor.h>

int x = 0;
Motor motor(24510);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting test...");
}

void loop() {
  if (Serial.available() > 0) {
    x = Serial.parseInt();
    motor.setPosition(x);
  }
  yield();
}
