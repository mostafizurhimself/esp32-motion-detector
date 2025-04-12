#include <Arduino.h>

#define PIR_PIN 14    // PIR sensor output pin
#define BUZZER_PIN 27 // Buzzer control pin

void setup()
{
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Make sure buzzer is off initially

  Serial.println("Motion Detector with Buzzer Initialized");
}

void loop()
{
  int motionState = digitalRead(PIR_PIN);

  if (motionState == HIGH)
  {
    Serial.println("🚶 Motion detected!");
    digitalWrite(BUZZER_PIN, HIGH); // Turn buzzer ON
  }
  else
  {
    Serial.println("🛑 No motion");
    digitalWrite(BUZZER_PIN, LOW); // Turn buzzer OFF
  }

  delay(1000); // check every second
}
