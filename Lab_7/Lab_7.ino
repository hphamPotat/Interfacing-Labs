int buzzerPin = A0;
int ledPin = 15;
int touchPin = 0;

int sensorValue = 0;
int sensorMin = 1023;
int sensorMax = 0;
int len = 0;
int total = 0;

int average;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(13, HIGH); 
  while (millis() < 8000) {
    sensorValue = touchRead(touchPin);
    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
    
    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }

    total += sensorValue;
    len++;
  }

  
  digitalWrite(13, LOW);
  
  Serial.print("Minimum Value:");
  Serial.print(sensorMin);
  Serial.print(" Maximum Value:");
  Serial.println(sensorMax);
  delay(500);
}

void loop() {
  Serial.print("Original Value:");
  sensorValue = touchRead(touchPin);
  Serial.println(sensorValue);
  
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);

  average = ((total / len));
//  if (sensorValue > average){
//    tone(buzzerPin, 200, 500);
//  }
  
  
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  Serial.print("Converted Value (Within Range of 0-255):");
  Serial.println(sensorValue);

  if (sensorValue > 50){
    tone(buzzerPin, sensorValue, 100);
  }

//  tone(buzzerPin, sensorValue, 1);

  analogWrite(ledPin, sensorValue);

  total += sensorValue;
  len++;

  Serial.print("Average: ");
  Serial.print(average);
  Serial.print(" Total: ");
  Serial.print(total);
  Serial.print(" Len: ");
  Serial.print(len);
  Serial.print(" Changed sensor value: ");
  Serial.print(sensorValue);
  Serial.println("");
  
  //tone(buzzerPin, sensorValue, 500);

  
}
