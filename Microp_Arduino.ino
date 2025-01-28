#include "DHT11.h"

// Define pins and types
#define DHTPIN PA0              // DHT11 connected to pin PA0
#define TEMP_LED_PIN PB0        // Red LED for temperature threshold
#define LIGHT_LED_PIN PB1       // LED for light intensity threshold
#define LDR_PIN PA1             // LDR sensor connected to analog pin PA1

// Threshold values
#define TEMP_THRESHOLD 20       // Temperature threshold in Celsius
#define LDR_THRESHOLD 1000      // ADC threshold value for light intensity

// Initialize DHT sensor
DHT11 dht(DHTPIN);             // Changed from DHT to DHT11

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Initialize LED pins
  pinMode(TEMP_LED_PIN, OUTPUT);
  pinMode(LIGHT_LED_PIN, OUTPUT);
  
  // Initialize the DHT sensor
  dht.begin();
  
  Serial.println("System initialized");
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  
  // Handle DHT read error
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    // Check temperature threshold
    if (temperature >= TEMP_THRESHOLD) {
      digitalWrite(TEMP_LED_PIN, HIGH);  // Turn on temperature LED
    } else {
      digitalWrite(TEMP_LED_PIN, LOW);   // Turn off temperature LED
    }
  }
  
  // Read light intensity from LDR
  int lightIntensity = analogRead(LDR_PIN);
  Serial.print("Light Intensity: ");
  Serial.println(lightIntensity);
  
  // Check light intensity threshold
  if (lightIntensity <= LDR_THRESHOLD) {
    digitalWrite(LIGHT_LED_PIN, HIGH);   // Turn on light LED
  } else {
    digitalWrite(LIGHT_LED_PIN, LOW);    // Turn off light LED
  }
  
  // Delay for stability
  delay(1000); // 1-second delay
}
