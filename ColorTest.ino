#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <FT6336U.h>

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

FT6336U ft6336u(CPT_SDA, CPT_SCL, CPT_RST, CPT_INT);
TFT_eSPI tft = TFT_eSPI(); // Create a TFT_eSPI object

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  Serial.println("Initializing...");

  tft.begin(); // Initialize the TFT display
  tft.setRotation(1); // Set the orientation. Adjust as needed (0-3)
  tft.invertDisplay(true); // Invert display colors
  tft.fillScreen(TFT_BLACK); // Fill the screen with black color
  Serial.println("TFT initialized and screen filled with black.");

  ft6336u.begin(); // Initialize the FT6336U touch controller
  Serial.println("FT6336U initialized.");

  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the text color to white with a black background
  tft.setCursor(60, 40); // Set the initial cursor positions
  tft.setTextSize(3); // Set the text size for the temperature display

  Serial.println("Setup completed.");

  // Draw a simple shape on the screen for testing
  tft.fillCircle(160, 120, 50, TFT_RED); // Draw a red circle in the center
}

void loop() {
  // Scan for touch points
  FT6336U_TouchPointType touchData = ft6336u.scan();

  if (touchData.touch_count > 0) {
    for (uint8_t i = 0; i < touchData.touch_count; i++) {
      uint16_t x = touchData.tp[i].x;
      uint16_t y = touchData.tp[i].y;

      // Clear previous touch points
      tft.fillScreen(TFT_BLACK); // Fill the screen with black color

      // Draw a new circle at the touch point
      tft.fillCircle(x, y, 30, TFT_RED); // Draw a white circle at the touch position
    }
  }

  delay(100); // Small delay to avoid flooding the serial output
}