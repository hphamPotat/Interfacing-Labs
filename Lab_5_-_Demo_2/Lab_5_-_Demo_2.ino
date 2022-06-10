int latchPin = 15;
int clockPin = 16;
int dataPin = 14;

int counter = 1;
int state = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
}

void loop() {
//  for (int i = 1; i < 256; i *= 2){
//    digitalWrite(latchPin, LOW);
//    shiftOut(dataPin, clockPin, LSBFIRST,  0);
//    shiftOut(dataPin, clockPin, LSBFIRST, i);
//    delay(500);   
//    digitalWrite(latchPin, HIGH);
//
//    if (i == 128){
//      for (int a = 1; a < 256; a*=2){
//        digitalWrite(latchPin, LOW);
//        shiftOut(dataPin, clockPin, LSBFIRST, a);
//        shiftOut(dataPin, clockPin, LSBFIRST, 0);
//        delay(500);   
//        digitalWrite(latchPin, HIGH);
//      
//        if (a == 128){
//          for (int b = 128; b > 0; b /= 2){
//            digitalWrite(latchPin, LOW);
//            shiftOut(dataPin, clockPin, LSBFIRST, b);
//            shiftOut(dataPin, clockPin, LSBFIRST, 0);
//            delay(500);   
//            digitalWrite(latchPin, HIGH);
//          }
//
//          for (int b = 128; b > 0; b /= 2){
//            digitalWrite(latchPin, LOW);
//            shiftOut(dataPin, clockPin, LSBFIRST, 0);
//            shiftOut(dataPin, clockPin, LSBFIRST, b);
//            delay(500);   
//            digitalWrite(latchPin, HIGH);
//          }
//        }
//      }
//    }
//  }

  counter = 1;
  
  for (int i = 1; i < 256; i |= counter){
    counter = counter << 1;

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,  0);
    shiftOut(dataPin, clockPin, LSBFIRST, i);
    delay(50);   
    digitalWrite(latchPin, HIGH);
    
  }

  counter = 1;

  for (int i = 1; i < 256; i |= counter){
    counter = counter << 1;

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,  i);
    shiftOut(dataPin, clockPin, LSBFIRST, 0xFF);
    delay(50);   
    digitalWrite(latchPin, HIGH);
  }

  counter = 255;

  for (int i = 255; i > 0; i &= counter){
    counter = counter >> 1;

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,  i);
    shiftOut(dataPin, clockPin, LSBFIRST, 0xFF);
    delay(50);   
    digitalWrite(latchPin, HIGH);

    if (i == 0){
      break;
    }
  }

  counter = 255;


  for (int i = 255; i > 0; i &= counter){
    counter = counter >> 1;

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    shiftOut(dataPin, clockPin, LSBFIRST, i);
    delay(50);   
    digitalWrite(latchPin, HIGH);
  }
  
}
