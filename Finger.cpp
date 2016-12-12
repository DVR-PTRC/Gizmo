#include "Finger.h"

Finger::Finger() {} // CLass Constructor
Finger::~Finger() {} // Class Destructor

void Finger::create_Finger(byte _id, byte _servoPin, byte _piezoPin,int _arraySize, int (*_tempo)[2]){

  id = _id;
  servoPin = _servoPin;
  _arraySize = arraySize,
  tempo = _tempo;
  knockSensor = _piezoPin;
  servo_setup();
  
}

void Finger::servo_setup() { // configure servo

  servo.attach(servoPin);
  
  switch (id) {
    case 0:    
      Piezo_threshold = 200;
      //Serial.println("C");
      initPos = 50;
      upPos = 50;
      downPos = 140;
      break;
    case 1:    
      Piezo_threshold = 200;
      initPos = 50;
      upPos = 50;
      downPos = 140;
      //Serial.println("F");
      break;
    case 2: 
     Piezo_threshold = 200;
      //Serial.println("G"); 
      initPos = 120;
      upPos = 120;
      downPos = 50; 
      break;
    case 3: 
      Piezo_threshold = 200;
       initPos = 70;
      upPos = 70;
      downPos = 140;
      //Serial.println("G");  
      break;
  }
  servo.write(initPos);
  delay(100);
  beatTimer = millis() + tempo[arrayPos][0];
  
  

}

boolean Finger::isKnocking() { // Read piezo sensor

  piezoReading = analogRead(knockSensor);


  
  if (piezoReading >= Piezo_threshold && bounce_delay == 0) {
    bounce_delay = readingDelay;
    Serial.print(id);
    return true;
  }

  else if (bounce_delay > 0) {
    bounce_delay--;
  }
  return false;
}

void Finger::update_() {
  
 
  if (isMoving_to_piezo) {
    if (isKnocking()) {
     servo.write(upPos); // Move finger Up
     isMoving_to_piezo = false;
      arrayPos++;
      if(arrayPos >= arraySize){
        arrayPos = 0;
        }
      beatTimer = millis() + tempo[arrayPos][0];     
    }
  }

   else if (millis() >= beatTimer) {
     servo.write(downPos); // Move finger Down
     isMoving_to_piezo = true;
     beatTimer += tempo[arrayPos][0];
  }
}



