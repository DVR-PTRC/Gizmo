// Includes
#include "Harmonica.h"
#include "Finger.h"


Harmonica harmonica[3];
Finger finger[4];

// Global Variables
int arraySize = 10;
int harmonica_Music [52][2]  = {
 
  {D4,  2000},
  {G4,  2000},
  {G4,  2000},
  {A4,  2000},
  {G4,  2000},
  {F4,  2000},
  {E4,  2000},
  {E4,  2000},
  
  {E4,  2000},
  {A4,  2000},
  {A4,  2000},
  {B4,  2000},
  {A4,  2000},
  {G4,  2000},
  {F4,  2000},
  {D4,  2000},

  {D4,  2000},
  {B4,  2000},
  {B4,  2000},
  {C4,  2000},
  {B4,  2000},
  {A4,  2000},
  {G4,  2000},
  {E4,  2000},

  {D4,  2000},
  {D4,  2000},
  {E4,  2000},
  {A4,  2000},
  {F4,  2000},
  {G4,  2000},

  {D4,  2000},
  {G4,  2000},
  {G4,  2000},
  {G4,  2000},
  {F4,  2000},
  {F4,  2000},
  {G4,  2000},
  {F4,  2000},
  {E4,  2000},
  {D4,  2000},
  
  {A4,  2000},
  {B4,  2000},
  {A4,  2000},
  {G4,  2000},
  {D4,  2000},
  {D4,  2000},
  {D4,  2000},
  {D4,  2000},
  {E4,  2000},
  {A4,  2000},
  {F4,  2000},
  {G4,  2000},
          
};

int drums0_Music[10][2];
int drums1_Music[10][2];
int drums2_Music[10][2];
int drums3_Music[10][2];


int HarMusic_Pos = 0;
int curr_harmonica;
int next_harmonica;

int currentNote;
int currentTempo;
int previousNote;
int nextNote;


void setup() {
  Serial.begin(115200);
  Serial.println("STARTING ARMONICA MUSIC PROGRAM");
  Serial.println(" ");
  

  // Create harmonicas

  harmonica[0].create_Harmonica(F_HAR, 2, 28, 10, 24);
  harmonica[1].create_Harmonica(G_HAR, 3, 29, 11, 25);
  harmonica[2].create_Harmonica(C_HAR, 4, 30, 12, 26);

  testArray_music();
  
  finger[0].create_Finger(0,9,A0,arraySize,drums0_Music);
  finger[1].create_Finger(1,6,A1,arraySize,drums1_Music);
  finger[2].create_Finger(2,5,A2,arraySize,drums2_Music);
  finger[3].create_Finger(3,3,A3,arraySize,drums3_Music);

  // Move Harmonicas to initial position
  
  musicSetup();
  harmonica[curr_harmonica].play();
}

void loop() {
 
  playFingers();
  playHarmonicas();
    
 
}
