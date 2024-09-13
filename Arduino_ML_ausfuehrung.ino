
#include <LEDSteuerung.h>
Eloquent::ML::Port::RandomForest clf;

const int lichtSensorPin = A0;  // Lichtsensor an Pin A0

int LEDPin = 3;

int LEDStatus = 0;

int Helligkeit = 0; 

void setup() {
  // Initialisierung der seriellen Kommunikation
  Serial.begin(9600);
  // Setze den LED-Pin als Ausgang (falls du den LED-Wert nutzen willst)
  pinMode(LEDPin, OUTPUT);

}

void loop() {
  //Sensor auslesen
  Helligkeit = analogRead(lichtSensorPin);
  Serial.print("Helligkeit: ");
  Serial.println(Helligkeit);

  //Machine learning anwenden: 
  LEDStatus = clf.predict(Helligkeit); 
  delay(10);
  Serial.print("LED Status: ");
  Serial.println(LEDStatus);

  if (LEDStatus == 0){
    digitalWrite(LEDPin, HIGH); 
  }else{
    digitalWrite(LEDPin, LOW);
  }
}
