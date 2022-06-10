/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
 
   This example code is in the public domain.
*/

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int redLedPin = 23;
const int blueLedPin = 21;
const int greenLedPin = 20; 
volatile int countPressed = 0;
int buttonPin = 11;
int red;
int green;
int blue;



// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(buttonPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), interuptMethod, FALLING);
  Serial.begin(9600);
  
}

// the loop() methor runs over and over again,
// as long as the board has power

void interuptMethod(){
  countPressed++;
  if (countPressed == 1){
    Serial.println(countPressed);
  }
  else{
    Serial.println(countPressed);
    randomLights();
    if (countPressed == 10){
      countPressed = 0;
    }
  }
}


void randomLights() {
  red = random(256);
  green = random(256);
  blue = random(256);
  
  // initialize the digital pin as an output.
  analogWrite(redLedPin,red);
  analogWrite(greenLedPin,green);
  analogWrite(blueLedPin,blue);

  delay(300);
}

void loop() {
  if (countPressed == 0 || countPressed > 10){
      randomLights();
  }
}
