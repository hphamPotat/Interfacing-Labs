#include <Bounce2.h>

int latchPin = 15;
int clockPin = 16;
int dataPin = 14;
int buttonPin = 9;
int randomSelection;
int previousSelection = -1;
int buttonState;
int firstNum = -1, secondNum = -2;
int gameRound = 0;
int roundCount = 0;
long timeStart;
long timeEnd;

int digits[10][8]={  // Ignore Last Bit because we are not using the decimal point. Invert everything. Then convert to decimal
  {1,1,1,1,1,1,0,0}, // 0 => 00000011 => 3
  {0,1,1,0,0,0,0,0}, // 1 => 10011111 => 159
  {1,1,0,1,1,0,1,0}, // 2 => 00100101 => 37
  {1,1,1,1,0,0,1,0}, // 3 => 00001101 => 13
  {0,1,1,0,0,1,1,0}, // 4 => 10011001 => 153
  {1,0,1,1,0,1,1,0}, // 5 => 01001001 => 73
  {1,0,1,1,1,1,1,0}, // 6 => 01000001 => 65 
  {1,1,1,0,0,0,0,0}, // 7 => 00011111 => 31 
  {1,1,1,1,1,1,1,0}, // 8 => 00000001 => 1
  {1,1,1,1,0,1,1,0}, // 9 => 00001001 => 9
  // {0,0,0,0,0,0,0,1}, // . => 11111110 => 254
                     // Turn All Off => 00000000 => 11111111 => 255
};

int shine[10] =     {3,159,37,13,153,73,65,31,1,9};
int actualNum[10] = {0,1,  2, 3, 4,  5, 6, 7, 8,9};


Bounce bounce = Bounce();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);
//  bounce.attach(buttonPin, INPUT_PULLUP);
//  bounce.interval(100);
  
//  attachInterrupt(digitalPinToInterrupt(buttonPin), interruptMethod, FALLING);
}

//void interruptMethod(){
//  Serial.println("Got in");  
//  digitalWrite(latchPin, LOW);
//  shiftOut(dataPin, clockPin, LSBFIRST,  shine[randomSelection]);
//  digitalWrite(latchPin, HIGH);
//}

void loop() {
//  bounce.update();
  
  buttonState = digitalRead(buttonPin);
//  buttonState = bounce.fell();
  
  Serial.println(buttonState);

  if (buttonState == HIGH){
    do{  
      randomSelection = random(0,10);
    } while(randomSelection == previousSelection);
    previousSelection = randomSelection;
  }
  
  if (buttonState == LOW){
    gameRound++;
    roundCount++;
    

    // If the user holds onto the button
    while (buttonState == HIGH){
      buttonState = digitalRead(buttonPin);
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST,  shine[randomSelection]);
      digitalWrite(latchPin, HIGH);

      // If the user presses once
      if (gameRound == 1){
        firstNum = shine[randomSelection];  
        
      }
      // If the user presses second time
      else if (gameRound == 2){
        secondNum = shine[randomSelection];
        delay(500);
      }

      // Comparing the numbers
      if (firstNum == secondNum){
        Serial.println("==> **MATCH**");
        timeStart = millis();
        timeEnd = timeStart;
        
        while(timeEnd - timeStart <= 2000){
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, LSBFIRST,  shine[randomSelection]);
          digitalWrite(latchPin, HIGH);
          delay(50);

          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, LSBFIRST,  255);
          digitalWrite(latchPin, HIGH);
          delay(50);

          timeEnd = millis();
        }
      }
      else if (gameRound == 2 && firstNum != secondNum){
        Serial.println("==> NO Match… period.");
        timeStart = millis();
        timeEnd = timeStart;

        while(timeEnd - timeStart <= 2000){
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, LSBFIRST,  254);
          digitalWrite(latchPin, HIGH);

          timeEnd = millis();
        }
      }
      
      if (gameRound == 2){
        gameRound = 0;
        firstNum = -1, 
        secondNum = -2;
        break;
      }
      
    }

    
  }
  else{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,  shine[randomSelection]);
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
  
}
