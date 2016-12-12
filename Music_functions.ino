void musicSetup() {
  Serial.println("musicSetup()");
  HarMusic_Pos = 0;
  curr_harmonica = -1;
  previousNote = -1;

  curr_harmonica = get_suitable_harmonica();
  harmonica[curr_harmonica].setMusic(currentNote, currentTempo);
  harmonica[curr_harmonica].moveStepper_to_pos();

  while (harmonica[curr_harmonica].isMoving_()) {

    harmonica[curr_harmonica].move_();
  }
  next_harmonica = get_suitable_harmonica();
  harmonica[next_harmonica].setMusic(currentNote, currentTempo);
  harmonica[next_harmonica].moveStepper_to_pos();

  while (harmonica[next_harmonica].isMoving_()) {

    harmonica[next_harmonica].move_();
  }

  Serial.println("End music setup");
  Serial.println("__________________________________");
}

int get_suitable_harmonica() {
  Serial.println("get_suitable_harmonica()");
  int firstCandidate = -1;
  int secondCandidate = -1;
  currentNote = harmonica_Music[HarMusic_Pos][0];
  currentTempo = harmonica_Music[HarMusic_Pos][1];


  // If the current note is equal to the next note, select the same harmonica
  if (currentNote == previousNote) {
    firstCandidate = curr_harmonica;
  }
  else {
    for (int i = 0; i < 3; i++) {
      //Serial.print("currentNote: ");
      //Serial.println(currentNote);
      if (harmonica[i].can_I_PlayIt(currentNote)) {

        if (i == curr_harmonica) {
          secondCandidate = i;
          //Serial.println("ENCONTRO IGUAL");
        }
        else {
          firstCandidate = i;
          //Serial.println("ENCONTRO DISTINTO");
        }
      }
    }
  }

  Serial.print("HarMusic_Pos: ");
  Serial.println(HarMusic_Pos);
  HarMusic_Pos++; // MOST IMPORTANT VARIABLE


  if (HarMusic_Pos >= arraySize) {
    HarMusic_Pos = 0;
    Serial.println("REBOBINAR EL ARREGLO");
  }

  if (firstCandidate == -1) {
    Serial.print("SELECTED HAR ");
    Serial.println(secondCandidate);
    return secondCandidate;
  }

  Serial.print("SELECTED HAR ");
  Serial.println(firstCandidate);
  return firstCandidate;
}

void initPlaying() {
  Serial.println("initPlaying()");
  harmonica[curr_harmonica].play();
  Serial.print("curr_harmonica: ");
  Serial.println(curr_harmonica);
  Serial.print("next_harmonica: ");
  Serial.println(next_harmonica);

  if (next_harmonica != curr_harmonica) {
    harmonica[next_harmonica].setMusic(currentNote, currentTempo);
    harmonica[next_harmonica].moveStepper_to_pos();
  }
}

void startPlaying() {
  Serial.println("startPlaying()");
  curr_harmonica = next_harmonica;
  harmonica[curr_harmonica].play();
  next_harmonica = get_suitable_harmonica();
  Serial.print("curr_harmonica: ");
  Serial.println(curr_harmonica);
  Serial.print("next_harmonica: ");
  Serial.println(next_harmonica);

  if (next_harmonica != curr_harmonica) {
    harmonica[next_harmonica].setMusic(currentNote, currentTempo);
    harmonica[next_harmonica].moveStepper_to_pos();
  }
}


void testArray_music() {
  for (int i = 0; i < 10; i++) {
    harmonica_Music [i][0] = random(10, 24);
    harmonica_Music [i][1] = random(1200, 2000);
    /* Serial.print(harmonica_Music [i][0]);
      Serial.print(" | ");
      Serial.println(harmonica_Music [i][0]);*/
    drums0_Music[i][1] = int(random(8));
    drums0_Music[i][0] = int(random(1000, 1500));
    drums1_Music[i][1] = int(random(8));
    drums1_Music[i][0] = int(random(2000, 2500));
    drums2_Music[i][1] = int(random(8));
    drums2_Music[i][0] = int(random(800, 1500));
    drums3_Music[i][1] = int(random(8));
    drums3_Music[i][0] = int(random(1200, 2500));
  }
  //Serial.println(" ");
}

void playHarmonicas() {

  for (int i = 0; i < 3; i++) {

    harmonica[i].move_(); // move current harmonica

    if (curr_harmonica == i &&
        curr_harmonica == next_harmonica &&
        !harmonica[i].isMoving_()  &&
        harmonica[curr_harmonica].check_if_finished()
       ) {
      Serial.println("SAME HARMONICA");
      harmonica[next_harmonica].setMusic(currentNote, currentTempo);
      harmonica[next_harmonica].moveStepper_to_pos();
      startPlaying();
    }
  }

  if (curr_harmonica != next_harmonica && harmonica[curr_harmonica].check_if_finished()) {

    Serial.println("OTHER HARMONICA");
    startPlaying(); // THE CASE OF OTHER THAN THE CURRENT HARMONICA
  }
}

void playFingers() {

  for (int i = 0; i < 4; i++) {

    finger[i].update_();

  }
}
