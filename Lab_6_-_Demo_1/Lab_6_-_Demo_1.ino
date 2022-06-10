int greenLedPin = 20;
int blueLedPin = 21;
int redLedPin = 23;
int analogPin = A0;
int redIntensity = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(greenLedPin,OUTPUT);
  pinMode(blueLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  redIntensity = analogRead(analogPin) / 4;
  analogWrite(redLedPin, redIntensity);
  analogWrite(greenLedPin, 255 - redIntensity);
  analogWrite(blueLedPin, 0);

  delay(100);
}
