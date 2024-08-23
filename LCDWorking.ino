#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <FT6336U.h>
#include <DHT11.h>

#define DHTPIN 5     // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // DHT 11
#define GPIO_PIN 33  // Pin to toggle

// DHT dht(DHTPIN, DHTTYPE);
DHT11 dht11(DHTPIN);

// Create an instance of the TFT_eSPI class
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

void setup() {

    // Initialize the GPIO pin as an output
  pinMode(GPIO_PIN, OUTPUT);
  digitalWrite(GPIO_PIN, HIGH);
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);

  // Initialize the TFT display
  tft.begin();
  tft.setRotation(1); // Set the orientation. Adjust as needed (0-3)

  // Fill the screen with black color
  tft.fillScreen(TFT_BLACK);

  // Set the text color to white with a black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // Set the text size
  tft.setTextSize(3);
}

void loop() {
   for (;;) {
    // Read temperature as Celsius
    int temp = dht11.readTemperature(); // truncating value so it looks nicer

    // Check if any reads failed and exit early (to try again).
    if (!(temp)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      // Print the temperature to the serial monitor
      tft.print("External Temperature: ");
      tft.print(temp);
      tft.print((char)247);  // Printing the degree symbol followed by C
      tft.print("C");  // Printing the degree symbol followed by C
      delay(2000);
      tft.fillScreen(TFT_BLACK); //clear the screen
      tft.setCursor(0, 280); //set the position
    }
  }
}