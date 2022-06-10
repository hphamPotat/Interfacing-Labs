#include <Bounce2.h>

Bounce bounce = Bounce();

int latchPin = 15;
int clockPin = 16;
int dataPin = 14;
int buttonPin = 9;

int randomSelection;
int previousSelection = -1;

int firstNum = -1, secondNum = -2;

int gameRound = 0;
int roundCount = 1;
bool roundStart = true;

long timeStart;
long timeEnd;


int digits[10][8]={  // Ignore Last Bit because we are not using the decimal point. Invert everything. Then convert to decimal
  {1,1,1,1,1,1,0,0},    // 0 => 00000011 => 3
  {0,1,1,0,0,0,0,0},    // 1 => 10011111 => 159
  {1,1,0,1,1,0,1,0},    // 2 => 00100101 => 37
  {1,1,1,1,0,0,1,0},    // 3 => 00001101 => 13
  {0,1,1,0,0,1,1,0},    // 4 => 10011001 => 153
  {1,0,1,1,0,1,1,0},    // 5 => 01001001 => 73
  {1,0,1,1,1,1,1,0},    // 6 => 01000001 => 65 
  {1,1,1,0,0,0,0,0},    // 7 => 00011111 => 31 
  {1,1,1,1,1,1,1,0},    // 8 => 00000001 => 1
  {1,1,1,1,0,1,1,0},    // 9 => 00001001 => 9
  // {0,0,0,0,0,0,0,1}, // . => 11111110 => 254
                        // Turn All Off => 00000000 => 11111111 => 255
};

int shine[10]     = {3,159,37,13,153,73,65,31,1,9};
byte byteShine[10] = {
  B00000011, 
  B10011111, 
  B00100101, 
  B00001101, 
  B10011001, 
  B01001001, 
  B01000001, 
  B00011111, 
  B00000001, 
  B00001001
  };



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  bounce.attach(buttonPin, INPUT_PULLUP);
  bounce.interval(25);
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), interruptMethod, FALLING);
  while (!Serial) {;}
}

void displayNum(int value){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST,  shine[value]);
  digitalWrite(latchPin, HIGH);
  delay(500);  
}

void displayLoss(int value){
  timeStart = millis();
  timeEnd = timeStart;

  while(timeEnd - timeStart <= 2000){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,  byteShine[value] ^ B00000001);
    digitalWrite(latchPin, HIGH);

    timeEnd = millis();
  }
}

void blinkNum(int value){
  timeStart = millis();
  timeEnd = timeStart;
  
  while(timeEnd - timeStart <= 2000){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,  shine[value]);
    digitalWrite(latchPin, HIGH);
    delay(50);

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,  255);
    digitalWrite(latchPin, HIGH);
    delay(50);

    timeEnd = millis();
  }
}

void interruptMethod(){
  gameRound++;
  if (gameRound == 1){
     firstNum = randomSelection;
     Serial.println("PBS press #1 ==> " + String(firstNum));
     delay(2000);
  }
  else if (gameRound == 2) {
    secondNum = randomSelection;
    Serial.println("PBS press #2 ==> " + String(secondNum));
    delay(2000);
  }
  else gameRound == 0;
}

void loop() {
  bounce.update();

  if (roundStart == true){
    Serial.println("Round #" + String(roundCount) + "...");
    roundStart = false;  
  }
  
//  do{  
    randomSelection = random(0,10);
//  } while(randomSelection == previousSelection);
//  previousSelection = randomSelection;

  displayNum(randomSelection);

  //Serial.println(gameRound);
  if (gameRound == 2){
    if (firstNum == secondNum){
      Serial.println("=> **Match**");
      blinkNum(firstNum);
      Serial.println();
    }
    else {
      Serial.println("=> NO Match... period.");
      displayLoss(firstNum);
      Serial.println();
    }
    
    firstNum = -1;
    secondNum = -2;
    roundCount++;
    roundStart = true;
    gameRound = 0;
  }
}
