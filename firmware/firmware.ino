//buttons
int B1 = D0;
int B2 = D1;
int B3 = D2;
int B4 = D3;

//leds
int led[5] = {D4, D5, D6, D7, D8};

bool special = false; //specialmode
int curr = 0; //current led
int bright = 50; // brightness

void setup(){
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  pinMode(B4, INPUT_PULLUP);

  for(int i = 0; i < 5; i++){
    pinMode(led[i], OUTPUT);
  }

  long startTime = millis();
}


void loop(){
  bool b1 = (digitalRead(B1) == LOW);
  bool b2 = (digitalRead(B2) == LOW);
  bool b3 = (digitalRead(B3) == LOW);
  bool b4 = (digitalRead(B4) == LOW);

  // controls led w/ b1 and b2, increases brightness w/ b4, press b3 to exit
  if(special){
    if(b1){
      curr--;
      if(curr < 0){
        curr = 4;
      }
    }
    if(b2){
      curr++;
      if(curr > 4){
        curr = 0;
      }
    }
    if(b4){
      if(bright < 255){
        bright += 15;
      }
    }
    if(bright > 0){
      bright--;
    }

    for(int i = 0; i < 5; i++){
      if(i == curr) analogWrite(led[i], bright);
      else analogWrite(led[i], 0);
    }

    if(b3) special = false;
  }
  else{
    long b1time;
    long b2time;
    long b3time = 0;
    long b4time;

    if(b1){
      b1time = millis();
      digitalWrite(led[0], HIGH);
    } else{
      digitalWrite(led[0], LOW);
    }

    if(b2){
      b2time = millis();
    }

    if(abs(b2time-b1time) <= 2000){
      digitalWrite(led[1], HIGH);
    } else{
      digitalWrite(led[1], LOW);
    }

    if(b3){
      b3time++;
      digitalWrite(led[2], HIGH);
    } else{
      digitalWrite(led[2], LOW);
      b3time = 0;
    }
    
    // special mode if b3 is held for more than 800 loops
    if(b3time > 800){
      special = true;
      digitalWrite(led[4], HIGH);
    } else{
      digitalWrite(led[4], LOW);
    }

    if(b4){
      b4time = millis();
      digitalWrite(led[3], HIGH);
    } else{
      digitalWrite(led[3], LOW);
    }
  }
}