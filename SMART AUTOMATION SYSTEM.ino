#include <WiFi.h>
#include <HTTPClient.h>

// Pin Configuration
const int ldrPin = 34;
const int ledPin = 2;

// Wokwi Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ThingSpeak Configuration
const char* apiKey = "YOUR_WRITE_API_KEY";
const char* server = "http://api.thingspeak.com/update";

void setup() {

  Serial.begin(115200);

  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Connect ESP32 to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Smart Automation System Started");
}

void loop() {

  // Read LDR sensor value
  int lightValue = analogRead(ldrPin);

  // Low light = LED ON
  // Bright light = LED OFF

  if (lightValue > 500) {

    digitalWrite(ledPin, HIGH);

    Serial.println("Low Light - LED ON");
  }

  else {

    digitalWrite(ledPin, LOW);

    Serial.println("Enough Light - LED OFF");
  }

  // Display sensor value
  Serial.print("Light Value: ");
  Serial.println(lightValue);

  // Send data to ThingSpeak

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    // 1 = LED ON
    // 0 = LED OFF

    int ledStatus = (lightValue > 500) ? 1 : 0;

    String url = String(server) +
                 "?api_key=" + apiKey +
                 "&field1=" + String(lightValue) +
                 "&field2=" + String(ledStatus);

    http.begin(url);

    int httpCode = http.GET();

    Serial.print("ThingSpeak Response: ");
    Serial.println(httpCode);

    http.end();
  }

  // ThingSpeak requires delay between updates
  delay(16000);
}