/*
  Motor.cpp - Library for driving encoded motor with L2898N.
  Created by Sujeethan Vignwswaran, January 19, 2021.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int ppm)
{
    pinMode(_IN1, OUTPUT);
    pinMode(_IN2, OUTPUT);
    pinMode(_EN1, OUTPUT);
    pinMode(_ENC1, INPUT_PULLUP);
    pinMode(_ENC2, INPUT_PULLUP);
    ledcSetup(0, 30000, 8);
    ledcAttachPin(_EN1, 0);
    ledcWrite(0, 255);
    attachInterrupt(digitalPinToInterrupt(_ENC2), isr, RISING);
    _instance = this;
    motorStop();
    _ppm = ppm;
}

void Motor::isr()
{
    _instance->countPulse();
}

Motor * Motor::_instance;

void Motor::countPulse()
{
    _pulse++;
}

void Motor::motorForward()
{
	digitalWrite(_IN1, HIGH);
 	digitalWrite(_IN2, LOW);
}

void Motor::motorReverse()
{
	digitalWrite(_IN1, LOW);
  	digitalWrite(_IN2, HIGH);
}

void Motor::motorStop()
{
	digitalWrite(_IN1, LOW);
  	digitalWrite(_IN2, LOW);
}

void Motor::setPosition(byte percent)
{
    int _target = map(abs(_state-percent), 0, 100, 0, _ppm);
    if (_state < percent) {
      while (_pulse <= _target) {
        motorForward();
      }
    } else if (_state > percent) {
      while (_pulse <= _target) {
        motorReverse();
      }
    } else {
      motorStop();
    }
    _pulse = 0;
    motorStop();
    _state = percent;
}
