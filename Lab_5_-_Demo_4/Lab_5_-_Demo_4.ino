int latchPin = 15;
int clockPin = 16;
int dataPin = 14;

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
};

int shine[10] = {3,159,37,13,153,73,65,31,1,9};

IntervalTimer timer;
int time1 = 10000000;
volatile int a, b;

 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  timer.begin(setCountTimer,time1);
}

void setCountTimer(){
  a = 0;
  b = 0;
}

void loop() {
  for (a = 0; a < 10; a++){  
    for (b = 0; b < 10; b++){
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST,  shine[b]);
      shiftOut(dataPin, clockPin, LSBFIRST,  shine[a]);
      digitalWrite(latchPin, HIGH);
      delay(500);  
    }
  }
}
