int greenLedPin = 17;
int blueLedPin = 16;
int redLedPin = 14;
int buttonPin = 11;
int buttonPin2 = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(greenLedPin,OUTPUT);
  pinMode(blueLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);

  pinMode(buttonPin,INPUT);
  pinMode(buttonPin2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(redLedPin,255);
  delay(500);
  analogWrite(redLedPin,0);
  delay(500);
}
