int greenLedPin = 20;
int blueLedPin = 21;
int redLedPin = 23;
int analogPin = A1;
double celsius, farenheit, measure;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(greenLedPin,OUTPUT);
  pinMode(blueLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  measure = analogRead(analogPin);
  celsius = 25 + (measure - 512) / 11.3;
  farenheit = celsius * 1.8 + 32;
  Serial.print("Celsius: ");
  Serial.println(celsius);
  Serial.print("Farenheit: ");
  Serial.println(farenheit);

  Serial.println();
  delay(1000);
}
