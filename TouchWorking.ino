#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <FT6336U.h>

#define CPT_SDA 21
#define CPT_SCL 22
#define CPT_RST 12
#define CPT_INT 13

FT6336U ft6336u(CPT_SDA, CPT_SCL, CPT_RST, CPT_INT);
TFT_eSPI tft = TFT_eSPI(); // Create a TFT_eSPI object

NEW SKETCH

void setup() {
    // Initialize serial communication at 115200 baud
    Serial.begin(115200);

    // Initialize the TFT display
    tft.begin();
    tft.setRotation(1); // Set the orientation. Adjust as needed (0-3)

    // Initialize the FT6336U touch controller
    ft6336u.begin();

    // Fill the screen with black color
NEW SKETCH

    tft.fillScreen(TFT_BLACK);TouchWorking | Arduino IDE 2.3.2


    // Set the text color to white with a black background
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // Set the text size
    tft.setTextSize(3);
}

void loop() {
    // Check if the interrupt pin indicates a touch event
    if (digitalRead(CPT_INT) != -1) {
        // Read the touch data status (number of touch points)
        uint8_t touchCount = ft6336u.read_td_status();

        // If there's at least one touch detected, print the coordinates
        if (touchCount > 0) {
            // Read the coordinates for the first touch point
            int16_t x = ft6336u.read_touch1_x();
            int16_t y = ft6336u.read_touch1_y();

            // Clear the previous text area
            tft.fillRect(60, 60, 320, 50, TFT_BLACK); // Adjust the coordinates and size as needed

            // Set the cursor position and print the coordinates on the screen
            tft.setCursor(60, 60);
            tft.printf("Touch:(%d, %d)", x, y);
        }
    }

    // Optional: small delay to avoid overwhelming the display updates
    delay(100); // Adjust the delay as needed
}