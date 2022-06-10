/************************************************************
  * Practical Question: Spring 2021
  * Level Achieved: A+
  * Status: functional
  * @author Huy Pham
*************************************************************/

IntervalTimer myTimer1;
IntervalTimer myTimer2;
int latchPin = 15;
int clockPin = 16;
int dataPin = 14;
int analogPin = A3;
int raw;
double celsius = -99.0;
long interval1 = 2000;

const double MIN_TEMP = 15.0;    //no student has reported lower than 15 degrees Celsius
const double MAX_TEMP = 33.0;   //no student has reported higher than 33 degrees Celsius

int letters[3][8]={   // Invert everything. Then convert to decimal
  {0,0,1,0,1,0,1,0}, // n  => 11010101 => 213
  {0,0,0,1,1,1,0,1}, // L. => 11100010 => 226
  {0,1,1,0,1,1,1,1}, // H. => 10010000 => 144
};

int shine[3] = {213,226,144};



void displayOnSeg(int mode){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST,  shine[mode]);
  digitalWrite(latchPin, HIGH);
  delay(500);
}

void convertToCelsius(int code){
  if (code <= 289) {
    celsius = 5 + (code - 289) / 9.82;
  }
  if (code > 289 && code <= 342) {
    celsius = 10 + (code - 342) / 10.60;
  }
  if (code > 342 && code <= 398) {
    celsius = 15 + (code - 398) / 11.12;
  }
  if (code > 398 && code <= 455) {
    celsius = 20 + (code - 455) / 11.36;
  }
  if (code > 455 && code <= 512) {
    celsius = 25 + (code - 512) / 11.32;
  }
  if (code > 512 && code <= 566) {
    celsius = 30 + (code - 566) / 11.00;
  }
  if (code > 566 && code <= 619) {
    celsius = 35 + (code - 619) / 10.44;
  }
  if (code > 619 && code <= 667) {
    celsius = 40 + (code - 667) / 9.73;
  }
  if (code > 667) {
    celsius = 45 + (code - 712) / 8.90;
  }
}

void injectMockLowTemp(){
  Serial.println("INJECT: LOW");
  unsigned long currentMillis = millis();

  while (millis() - currentMillis < interval1){
    displayOnSeg(1);
  
    Serial.print("Temperature: -80");
    Serial.print(" (raw) ");
    convertToCelsius(-80);
    Serial.print(celsius);
    Serial.println(" Celsius");
  }
  
  myTimer1.end();
}

void injectMockHighTemp(){
  Serial.println("INJECT: HIGH");
  unsigned long currentMillis = millis();
  
  while (millis() - currentMillis < interval1){
    displayOnSeg(2);
    
    Serial.print("Temperature: 800");
    Serial.print(" (raw) ");
    convertToCelsius(800);
    Serial.print(celsius);
    Serial.println(" Celsius");

  }
  myTimer2.end();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  while (!Serial) {;}
  myTimer1.begin(injectMockLowTemp, 6000000);
  myTimer2.begin(injectMockHighTemp, 6000001);
}

void loop() {
  
  raw = analogRead(analogPin);
  convertToCelsius(raw);

  Serial.print("Temperature: ");
  Serial.print(raw);
  Serial.print(" (raw) ");
  Serial.print(celsius);
  Serial.println(" Celsius");

  if (celsius >= MIN_TEMP && celsius <= MAX_TEMP){
    displayOnSeg(0);
  }
  else if (celsius < MIN_TEMP){
    displayOnSeg(1);
  }
  else{
    displayOnSeg(2);
  }
  
  
  delay(400);

}
