#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <FT6336U.h>
#include <DHT11.h> // Include the DHT library

// Pin definitions for DHT11
#define DHTPIN 5      // Pin connected to DHT11 data pin
#define DHTTYPE DHT11 // DHT11 sensor type

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

DHT11 dht(DHTPIN);
FT6336U ft6336u(CPT_SDA, CPT_SCL, CPT_RST, CPT_INT);
TFT_eSPI tft = TFT_eSPI(); // Create a TFT_eSPI object

bool showBattery = false; // Flag for battery
bool showSettings = false; // Flag for settings
bool settingsScreenDrawn = false; // Flag for draw screen
int x, y; // Declare x and y variables

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  tft.begin(); // Initialize the TFT display
  tft.setRotation(1); // Set the orientation. Adjust as needed (0-3)
  tft.invertDisplay(true); // Invert display colors
  tft.fillScreen(TFT_WHITE); // Fill the screen with white color
  Serial.println("TFT initialized and screen filled with white.");

  ft6336u.begin(); // Initialize the FT6336U touch controller
  Serial.println("FT6336U touch controller initialized.");

  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the text color to white with a black background

  // Initial screen layout
  drawMainScreen();
}

void loop() {
  if (showSettings) {
    if (!settingsScreenDrawn) {
      displaySettingsScreen();
      settingsScreenDrawn = true;
    }

    // Handle touch inputs on the settings screen
    uint8_t touchCount = ft6336u.read_td_status();

    if (touchCount > 0) {
      x = ft6336u.read_touch1_x();
      y = ft6336u.read_touch1_y();

      Serial.printf("Touch detected at: (%d, %d)\n", x, y);

      // Check if the BACK button is touched
      if (x >= 20 && x <= 140 && y >= 270 && y <= 410) {
        showSettings = false;  // Go back to the main screen
        settingsScreenDrawn = false; // Reset the flag to allow drawing the main screen
        drawMainScreen(); // Call your function to draw the main screen
        Serial.println("BACK button touched");
      }
    }

    return;
  }

  // Handle touch inputs on the main screen
  uint8_t touchCount = ft6336u.read_td_status();

  if (touchCount > 0) {
    x = ft6336u.read_touch1_x();
    y = ft6336u.read_touch1_y();

    Serial.printf("Touch detected at: (%d, %d)\n", x, y);

    // Check if the internal temperature circle is touched
    if (x >= 100 && x <= 250 && y >= 285 && y <= 410) {
      showBattery = !showBattery; // Toggle the flag
      Serial.printf("showBattery toggled to: %d\n", showBattery); // Debugging line
      updateInternalCircle(); // Update the display
    }

    // Check if the first button is touched (for switching to settings screen)
    if (x >= 20 && x <= 100 && y >= 20 && y <= 150) {
      showSettings = true;
      settingsScreenDrawn = false; // Reset the flag to allow drawing
      Serial.println("Settings button touched");
      delay(100); // Add a small delay of 100 milliseconds
    }
  }

  // Read temperature as Celsius
  int temp = dht.readTemperature();

  if (!(temp)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Update only the external temperature display
    tft.setTextSize(4);
    tft.setCursor(85, 105);
    tft.print(temp);
    tft.print((char)247); // Degree symbol
    tft.print("C");

    if (!showBattery) {
    // Display internal temp
    tft.setCursor(305, 105);
    tft.print(temp);
    tft.print((char)247); // Degree symbol
    tft.print("C");
    }
  }
}

void drawMainScreen() {
  tft.fillRoundRect(5, 5, 470, 310, 25, TFT_BLACK); // Background
  tft.fillCircle(130, 120, 81, TFT_BLUE); // External temp circle
  tft.fillCircle(130, 120, 72, TFT_BLACK); // Inner black circle
  tft.fillCircle(350, 120, 81, TFT_RED); // Internal temp/battery circle
  tft.fillCircle(350, 120, 72, TFT_BLACK); // Inner black circle

  tft.drawSmoothRoundRect(20, 225, 20, 19, 140, 75, TFT_WHITE); // First button
  tft.drawSmoothRoundRect(170, 225, 20, 19, 140, 75, TFT_WHITE); // Second button
  tft.drawSmoothRoundRect(320, 225, 20, 19, 140, 75, TFT_WHITE); // Third button

  //Title project name
  tft.setTextSize(2); // Set the text size
  tft.setCursor(52, 12); // Set cursor position for title
  tft.print("/// THERMAL DUNE ENERGY STORAGE");

  tft.setTextSize(2); // Set the text size for the buttons
  tft.setCursor(43, 255); // Set cursor position for settings
  tft.print("Settings");
  tft.setCursor(181, 245); // Set cursor position for Start/Stop
  tft.print("Start/Stop");
  tft.setCursor(195, 265); // Set cursor position for Charging
  tft.print("Charging");
  tft.setCursor(332, 245); // Set cursor position for Start/Stop
  tft.print("Start/Stop");
  tft.setCursor(350, 265); // Set cursor position for Heating
  tft.print("Heating");
}

void updateInternalCircle() {
  tft.setTextSize(4);
  if (showBattery) {
    // Display battery percentage
    int batteryPercent = 100; // Example battery percentage
    tft.setCursor(305, 105);
    tft.print(batteryPercent);
    tft.print("%");
  } else {
    // Display internal temperature
    int temp = dht.readTemperature();
    if (temp) {
      tft.setCursor(305, 105);
      tft.print(temp);
      tft.print((char)247); // Degree symbol
      tft.print("C");
    }
  }
}

void displaySettingsScreen() {
  tft.fillScreen(TFT_WHITE); // Fill the screen with white color
  tft.fillRoundRect(5, 5, 470, 310, 25, TFT_BLACK); // Background
  
  tft.drawSmoothRoundRect(70, 225, 20, 19, 140, 75, TFT_WHITE); // First button
  tft.drawSmoothRoundRect(270, 225, 20, 19, 140, 75, TFT_WHITE); // Second button

  //Settings title
  tft.setTextSize(2); // Set the text size
  tft.setCursor(132, 12); // Set cursor position for title
  tft.print("/// USER SETTINGS");

  //Setting Options
  tft.setTextSize(2); // Set the text size for the buttons
  tft.setCursor(20, 45); // Set cursor position for settings
  tft.print("Charging Time: ");
  tft.setCursor(20, 90); // Set cursor position for Start/Stop
  tft.print("Heating Time: ");
  tft.setCursor(20, 135); // Set cursor position for settings
  tft.print("Ambient Temperature: ");
  tft.setCursor(20, 180); // Set cursor position for Start/Stop
  tft.print("Temperature Scale: ");

  tft.setTextSize(2); // Set the text size for the buttons
  tft.setCursor(118, 255); // Set cursor position for settings
  tft.print("SAVE");
  tft.setCursor(318, 255); // Set cursor position for Start/Stop
  tft.print("BACK");
}