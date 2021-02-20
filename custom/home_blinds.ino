const int ppm = 24510;

const byte IN1 = 26;
const byte IN2 = 27;
const byte EN1 = 14;
const byte ENC1 = 18;
const byte ENC2 = 19;
volatile int pulse = 0;
volatile byte state = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(ENC1, INPUT_PULLUP);
  pinMode(ENC2, INPUT_PULLUP);
  ledcSetup(0, 30000, 8);
  ledcAttachPin(EN1, 0);
  ledcWrite(0, 255);
  attachInterrupt(digitalPinToInterrupt(ENC2), countPulse, RISING);
  motorStop();
  Serial.begin(115200);
}

int x = 0;

void loop() {
  if (Serial.available() > 0) {
    x = Serial.parseInt();
    setPosition(x);
  }
  yield();
}

void countPulse() {
  pulse++;
}

void motorForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void motorReverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void setPosition(byte percent) {
  int target = map(percent, 0, 100, 0, ppm);
  if (state < percent) {
    while (pulse <= target) {
      motorForward();
    }
  } else if (state > percent) {
    while (pulse <= target) {
      motorReverse();
    }
  } else {
    motorStop();
  }
  pulse = 0;
  motorStop();
  state = percent;
}
