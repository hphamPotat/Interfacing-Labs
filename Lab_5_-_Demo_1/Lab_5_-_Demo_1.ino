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
  // put your main code here, to run repeatedly:
  if (state == 1){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, counter);
    delay(500);   
    digitalWrite(latchPin, HIGH);
    
    counter = counter << 1;
    if (counter == 128){
      state = 2;
    }
  }
  else if (state == 2){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, counter);
    delay(500);   
    digitalWrite(latchPin, HIGH);
    
    counter = counter >> 1;
    if (counter == 1){
      state = 1;
    }
  }
   
}
