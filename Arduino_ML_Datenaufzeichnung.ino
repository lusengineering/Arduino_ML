#include <SPI.h>
#include <SD.h>

const int chipSelect = 5;
const int lichtSensorPin = A0;  // Lichtsensor an Pin A0
int TasterPin = 2; 
int LEDPin = 3;
int LEDStatus = 13;                   // Beispielwert für die LED-Variable
int Helligkeit;                 // Variable für den Lichtsensorwert

unsigned long previousMillis = 0; // Speichert den letzten Zeitpunkt, an dem die Daten geschrieben wurden
const long interval = 10;        // Intervall für das Schreiben (in Millisekunden, 100 ms = 0,1 Sekunden)

void setup() {
  // Initialisierung der seriellen Kommunikation
  Serial.begin(9600);

  // Initialisierung des SD-Karten-Moduls
  if (!SD.begin(chipSelect)) {
    Serial.println("SD-Karte konnte nicht initialisiert werden.");
    return;
  }
  Serial.println("SD-Karte erfolgreich initialisiert.");
  
  // Setze den LED-Pin als Ausgang (falls du den LED-Wert nutzen willst)
  pinMode(LEDPin, OUTPUT);
  pinMode(TasterPin, INPUT_PULLUP);
}

void loop() {

  // Lese den Wert des Lichtsensors (zwischen 0 und 1023)
  Helligkeit = analogRead(lichtSensorPin);

  //Stautus des Buttons abfragen und im Seriellen Monitor ausgeben
  LEDStatus = digitalRead(TasterPin);
  Serial.print("LED Status: ");
  Serial.println(LEDStatus);

  //LED anschalten wenn der Button gedrückt wurde
  if (LEDStatus == 0){
    digitalWrite(LEDPin, HIGH); 
  }else{
    digitalWrite(LEDPin, LOW);
  }

  // Aktuelle Zeit ermitteln
  unsigned long currentMillis = millis();

  // Überprüfen, ob 0,1 Sekunden vergangen sind
  if (currentMillis - previousMillis >= interval) {
    // Die Zeit aktualisieren
    previousMillis = currentMillis;

    // Öffne oder erstelle die Datei und schreibe die Daten
    File dataFile = SD.open("LEDdaten.txt", FILE_WRITE);

    // Überprüfe, ob die Datei erfolgreich geöffnet wurde
    if (dataFile) {
      dataFile.print(Helligkeit);
      dataFile.print(",");
      dataFile.println(LEDStatus);

      // Datei schließen
      dataFile.close();

      // Serieller Monitor zur Kontrolle
      Serial.print("Helligkeit: ");
      Serial.println(Helligkeit);
      Serial.println("Daten erfolgreich gespeichert.");
    } else {
      // Wenn die Datei nicht geöffnet werden konnte
      Serial.println("Fehler beim Öffnen der Datei.");
    }
  }
}
