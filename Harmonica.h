#ifndef Harmonica_h
#define Harmonica_h
#include "Arduino.h"
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h> // stock servo library


#define G2 1
#define C3 2
#define D3 3
#define E3 4
#define F3 5
#define G3 6
#define A3 7
#define B3 8
#define C4 9
#define D4 10
#define E4 11
#define F4 12
#define G4 13
#define A4 14
#define B4 15
#define C5 16
#define D5 17
#define E5 18
#define F5 19
#define G5 20
#define A5 21
#define B5 22
#define C6 23
#define D6 24
#define E6 25
#define F6 26
#define G6 27
#define A6 28
#define B6 29


#define F_HAR 0
#define G_HAR 1
#define C_HAR 2




class Harmonica {
  private:
    byte *Av_Notes;
    int id;
    Servo servo;
    byte initPos = 0;
    unsigned long noteTimer;
    int stepBetween_tones = -63;
    int arraySize;
    boolean isPlaying = false;
    int openValve;
    int closeValve = 90;
    int limitPin;
    byte C_HarNotes[12] ={

      G2,C3,E3,G3,C4,E4,G4,C5,E5,G5,C6,E6
     
    };
    byte F_HarNotes[12] ={

     F3,A3,C3,F4,A4,C4,F5,A5,C5,F6,A6,C6

    };
    byte G_HarNotes[12] ={

     G3,B3,D3,G4,B4,D4,G5,B5,D5,G6,B6,D6

    };

    int note;
    int tempo;
    int lastNote = 0;
    int dir;
    int noteDistance;
    int currentPos;
    int targetPos;
    int stepsCount;
    int speed_ = 350;

    
  public:
    const static int harmonicaNumber = 3;  
    AccelStepper *stepper; //Pointer to stepper 
    
    Harmonica();
    ~Harmonica();
    
    void create_Harmonica(int _id, 
                          int stepPin, 
                          int dirPin, 
                          int servoPin, 
                          int _limitPin);
      
    void stepper_setup();
    void servo_setup();
    void moveTo_zero();
    void set_note_time();
    int get_Array_pos();
    void play();
    boolean check_if_finished();
    void moveStepper_to_pos();
    void servoValve(boolean valveState);
    void goTo_initPos();
    boolean update_();
    boolean can_I_PlayIt(int note);
    void setMusic(int _note, int _tempo);
    boolean move_();
    boolean isMoving_();
};

#endif
