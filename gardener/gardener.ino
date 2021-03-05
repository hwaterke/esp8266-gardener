#define MOISTURE_SENSOR_PIN A0
#define RELAY_PIN 2

unsigned long lastWatering = 0;
bool isRelayOn = false;

void setup()
{
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  digitalWrite(RELAY_PIN, HIGH);
}

void loop()
{

  int moisture = analogRead(MOISTURE_SENSOR_PIN);

  if (moisture > 450) {
    // Dry soil
    unsigned long now = millis();
    if (now - lastWatering > 86400000) {
      // Time to water
      digitalWrite(RELAY_PIN, LOW);
      delay(4000);
      digitalWrite(RELAY_PIN, HIGH);
      lastWatering = now;
    }
  }

  // Serial.println(moisture);

  delay(6000);
}
