/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
 
   This example code is in the public domain.
*/

#include <Bounce2.h>

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int redLedPin = 23;
const int blueLedPin = 21;
const int greenLedPin = 20; 
volatile int countPressed = 0;
int buttonPin = 11;
int buttonPin2 = 9;
int red;
int green;
int blue;
int state;
int redBrightness = 255;

Bounce a = Bounce();
Bounce b = Bounce();


// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  
  //pinMode(buttonPin,INPUT);
  a.attach(buttonPin,INPUT);
  a.interval(50);
  
  //pinMode(buttonPin2,INPUT_PULLUP);
  b.attach(buttonPin2,INPUT_PULLUP);
  b.interval(50);
  
  Serial.begin(9600);
}

void loop() {
//  if (digitalRead(buttonPin) == LOW){
//    state = 1;
//  }
//  else if (digitalRead(buttonPin2) == LOW){
//    state = 2;
//  }
  
  a.update();
  b.update();
  if (a.fell()){
    state = 1;
    Serial.println("State 1");
  }
  else if (b.fell()){
    state = 2;
    Serial.println("State 2");
  }


  analogWrite(redLedPin,redBrightness);
  if (state == 1){
    analogWrite(greenLedPin, 255 - redBrightness);
    analogWrite(blueLedPin, 0);
  }
  else if (state == 2){
    analogWrite(blueLedPin, 255 - redBrightness);
    analogWrite(greenLedPin, 0);
  }

  if (state == 1 || state == 2){
    redBrightness--;
  }

  if (redBrightness == 0){
    redBrightness = 255;
    analogWrite(greenLedPin, 0);
    analogWrite(blueLedPin, 0);
  }

  delay(10);
}
