#ifndef Finger_h
#define Finger_h
#include "Arduino.h"
#include <Servo.h> // stock servo library

class Finger {
  private:
    int knockSensor;
    int Piezo_threshold;
    int piezoReading = 0;
    int bounce_delay = 0;
    int readingDelay = 200;
    Servo servo;
    byte servoPin;
    int initPos;
    int nextBeat;
    unsigned long beatTimer;
    int arrayPos = 0;
    boolean isMoving_to_piezo = false;
    int upPos;
    int downPos;
    byte id;
    int arraySize;
    
    int (*tempo)[2]; // Much ninja, so wow

  public:
    Finger();
    ~Finger();
    void create_Finger(byte _id, byte _servoPin, byte _piezoPin,int _arraySize, int (*_tempo)[2]);
    void servo_setup();
    boolean isKnocking();
    void moveFinger();
    void update_();

    
};

#endif
