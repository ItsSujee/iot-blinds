/*
  Motor.h - Library for driving encoded motor with L2898N.
  Created by Sujeethan Vignwswaran, January 19, 2021.
  Released into the public domain.
*/
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  static Motor * _instance;
  static void isr();
  void countPulse();
  public:
    Motor(int ppm);
    void setPosition(byte percent);
  private:
    int _ppm;
    const byte _IN1 = 26;
    const byte _IN2 = 27;
    const byte _EN1 = 14;
    const byte _ENC1 = 18;
    const byte _ENC2 = 19;
    volatile int target;
    volatile int _pulse = 0;
    volatile byte _state = 0;
    void motorForward();
    void motorReverse();
    void motorStop();
};

#endif
