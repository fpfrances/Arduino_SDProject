#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <FT6336U.h>
#include <DHT11.h>
#include "MAX6675.h"

// Pin definitions for DHT11
#define DHTPIN 5      // Pin connected to the first DHT11 data pin
#define DHTPIN2 16    // Pin connected to the second DHT11 data pin

// Pin definitions for TFT display
#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST   4 // Or set to -1 if connected to ESP32 reset line

// Pin definitions for FT6336U touch controller
#define CPT_SDA 21
#define CPT_SCL 22
#define CPT_RST 12
#define CPT_INT 13

// SPI connection for k-type thermocouple
#define kTypeCS1 25  // Chip Select pin for the thermocouple
#define kTypeCS2 26  // CS pin for the second thermocouple
#define kTypeSO 19  // MISO pin for the thermocouple
#define kTypeSCK 18 // SCK pin for the thermocouple (use the same as HSPI_CLK)

TFT_eSPI tft = TFT_eSPI(); // Create a TFT_eSPI object


MAX6675 thermoCouple1(kTypeCS1, kTypeSO, kTypeSCK); // First thermocouple
MAX6675 thermoCouple2(kTypeCS2, kTypeSO, kTypeSCK); // Second thermocouple

void setup() {
  Serial.begin(115200);

  thermoCouple1.begin();
  thermoCouple2.begin();

  Serial.println("MAX6675 Dual Thermocouple Test");
}

void loop() {
  delay(1000);

  // Read temperature from first thermocouple
  int status1 = thermoCouple1.read();
  float temp1 = thermoCouple1.getTemperature();
  Serial.print("Thermocouple 1 - Status: ");
  Serial.print(status1);
  Serial.print(" Temperature: ");
  Serial.println(temp1);

  // Read temperature from second thermocouple
  int status2 = thermoCouple2.read();
  float temp2 = thermoCouple2.getTemperature();
  Serial.print("Thermocouple 2 - Status: ");
  Serial.print(status2);
  Serial.print(" Temperature: ");
  Serial.println(temp2);

  delay(2000);
}