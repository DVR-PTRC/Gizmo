#include "Harmonica.h"

Harmonica::Harmonica() {
  stepper = NULL;
} // CLass Constructor

Harmonica::~Harmonica() { // Class Destructor
  delete stepper;
}

void Harmonica::create_Harmonica(int _id,
                                 int stepPin,
                                 int dirPin,
                                 int servoPin,
                                 int _limitPin)

{
  id = _id;
  Serial.print("Harmonica ");
  Serial.println(id);
  if (stepper != NULL)
    delete stepper;
  limitPin = _limitPin;
  pinMode(limitPin, INPUT);
  stepper = new AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
  servo.attach(servoPin);
  servo.write(90);

  switch (id) {
    case C_HAR:
      Av_Notes = C_HarNotes;
      //Serial.println("C");
      break;
    case F_HAR:
      Av_Notes = F_HarNotes;
      //Serial.println("F");
      break;
    case G_HAR:
      Av_Notes = G_HarNotes;
      //Serial.println("G");
      break;
  }
  stepper_setup();
  moveTo_zero();


  servo_setup();
  Serial.println("__________________________________");
  Serial.println(" ");
}

void Harmonica::stepper_setup() { // configure stepper
  stepper->setMaxSpeed(1000.0);
  Serial.print("Stepper Number ");
  Serial.print(id);
  delay(150);
  Serial.println("        Ready");
}

void Harmonica::servo_setup() { // configure servo
  servo.write(closeValve);
  Serial.print("Servo Number ");
  Serial.print(id);
  switch (id) {
    case C_HAR:
      openValve = 133;
      break;
    case F_HAR:
      openValve = 52;
      break;
    case G_HAR:
      openValve = 38;
      break;
  }
  delay(150);
  Serial.println("          Ready");
}

void Harmonica::moveTo_zero() {
  delay(100);

  stepper->setSpeed(speed_);
  Serial.print("Moving to zero ");
  delay(100);
  while (digitalRead(limitPin) == 0) {

    stepper->runSpeed();
  }

  Serial.println("         Ready");
  currentPos = 0;
  targetPos = 0;
}



void Harmonica::play() {

  Serial.println("play()");
  servoValve(true);
  isPlaying = true;
  noteTimer = millis() + tempo; // Current Time to start counting
  /*Serial.print("Harmonica Number ");
    Serial.print(id);
    Serial.print("Now Playing on array pos: ");
    Serial.println(arrayPos);*/
}

boolean Harmonica::check_if_finished() {
  //Serial.println("check_if_finished()");
  if (millis() >= noteTimer && isPlaying) {
    servoValve(false);
    isPlaying = false;
    Serial.print("Harmonica Number ");
    Serial.print(id);
    Serial.println(" Stop Playing");
    Serial.println("__________________________________");
    return true;
  }
  return false;
}

void Harmonica::moveStepper_to_pos() {
  Serial.println("moveStepper_to_pos()");
  Serial.print("LASTNOTE: ");
  Serial.println(lastNote);
  Serial.print("NOTE: ");
  Serial.println(note);


  targetPos = noteDistance * stepBetween_tones + currentPos;


  if (targetPos > currentPos) {

    dir = 1;

  }
  else {

    dir = -1;

  }

  Serial.print("currentPos: ");
  Serial.println(currentPos);
  Serial.print("targetPos: ");
  Serial.println(targetPos);
  Serial.print("dir: ");
  Serial.println(dir);

  stepper->setSpeed(speed_ * dir);

}

void Harmonica::servoValve(boolean valveState) {
  Serial.println("servoValve()");



  if (valveState) {
    servo.write(openValve);

    Serial.print("Harmonica Number ");
    Serial.println(id);
    Serial.println("Start playing");
    Serial.println("Open airflow");
  }
  else {
    servo.write(closeValve);
    Serial.print("Harmonica Number ");
    Serial.print(id);
    Serial.println(" Close airflow");
  }
}

boolean Harmonica::update_() {
  return stepper->runSpeed();
}

boolean Harmonica::can_I_PlayIt(int _note) {

  Serial.println("can_I_PlayIt()");

  for (int i = 0; i < 12; i++) {

    if (_note == Av_Notes[i]) {

      return true;
    }
  }
  return false;
}

void Harmonica::setMusic(int _note, int _tempo) {
  Serial.println("setMusic()");



  for (int i = 0; i < 12; i++) {
    if (_note == Av_Notes[i]) {
      noteDistance = i - note;
      note = i;
    }
  }

  Serial.print("Note: ");
  Serial.println(note);
  Serial.print("Tempo: ");
  Serial.println(_tempo);
  tempo = _tempo;
}


boolean Harmonica::move_() {

  if (currentPos == targetPos) {

    return false;

  }

  if (stepper->runSpeed()) {

    currentPos += dir;
    return true;
  }

  return false;

}

boolean Harmonica::isMoving_() {

  if (currentPos != targetPos) {

    return true;

  }

  return false;

}

