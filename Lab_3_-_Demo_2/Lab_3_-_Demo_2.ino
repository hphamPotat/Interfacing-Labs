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
int times = 0;
int red = 255;
int green = 0;
int blue = 0;


// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
  times = 0;
  
  while (times <= 25){
    analogWrite(redLedPin, red);
    analogWrite(greenLedPin, green);
    analogWrite(blueLedPin, blue);
    
    if (times < 5){
      green += 64;
      if (green == 256){
        green--;
      }
    }
    else if (times >= 5 && times <= 8){
      red -= 64;
      if (red < 0){
        red++;
      }
    }
    else if (times >= 9 && times <= 12){
      blue += 64;
      if (blue == 256){
        blue--;
      }
    }
    else if (times >= 13 && times <= 16){
      green -= 64;
      if (green < 0){
        green++;
      }
    }
    else if (times >= 17 && times <= 20){
      red += 64;
      if (red == 256){
        red--;
      }
    }
    else if (times >= 21 && times <= 24){
      blue -= 64;
      if (blue < 0){
        blue++;
      }
    }

    times++;
    delay(200);
  }
}
