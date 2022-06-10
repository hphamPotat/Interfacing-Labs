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
int countPressed = 0;
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
  Serial.begin(9600);
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
  red = random(256);
  green = random(256);
  blue = random(256);

  analogWrite(redLedPin,red);
  analogWrite(greenLedPin,green);
  analogWrite(blueLedPin,blue);

  if (digitalRead(buttonPin) == LOW){
    countPressed++;
    Serial.println(countPressed);
    delay(1000);
    while (countPressed < 10){
        if (digitalRead(buttonPin) == LOW){
          red = random(256);
          green = random(256);
          blue = random(256);
          
          countPressed++;
          Serial.println(countPressed);
          
          
          analogWrite(redLedPin,red);
          analogWrite(greenLedPin,green);
          analogWrite(blueLedPin,blue);
          delay(300);
        }
    }

    Serial.println("oof");
    if(countPressed == 10){
      countPressed = 0; 
    }
    
  }
  
  delay(300);
}
