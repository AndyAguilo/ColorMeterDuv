#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_TCS34725.h"
#include <math.h>

// Button pin
#define BUTTON_PIN 2

// Define reference illuminant RGB values for D65
#define refRed 0.95047
#define refGreen 1.00000
#define refBlue 1.08883

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address 0x27, 16 columns, 2 rows

// TCS34725 configuration
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin(16,2);
  lcd.backlight();

  // Initialize TCS34725 sensor
  if (!tcs.begin()) {
    lcd.println("Error initializing TCS34725 sensor!");
    while (1); // Halts the program
  }

  // Initialize button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Display initial message on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hola amor!!!");
  lcd.setCursor(0, 1);
  lcd.print("aprietame");
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Capture RGB data
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);
    uint16_t colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    uint16_t lux = tcs.calculateLux(r, g, b);

    // Normalize measured RGB values
    float sum = r + g + b;
    float rNorm = r / sum;
    float gNorm = g / sum;
    float bNorm = b / sum;

    // Normalize reference illuminant RGB values
    float refSum = refRed + refGreen + refBlue;
    float refRNorm = refRed / refSum;
    float refGNorm = refGreen / refSum;
    float refBNorm = refBlue / refSum;

    // Calculate tint difference (Euclidean distance)
    float tintDiff = sqrt(pow((rNorm - refRNorm), 2) + pow((gNorm - refGNorm), 2) + pow((bNorm - refBNorm), 2));

    // Calculate chromaticity coordinates (u, v)
    float u = (4 * rNorm) / (-2 * rNorm + 12 * gNorm + 3);
    float v = (6 * gNorm) / (-2 * rNorm + 12 * gNorm + 3);

    // Calculate distance from the Planckian locus (Lfp)
    float Lfp = sqrt(pow((u - 0.292), 2) + pow((v - 0.24), 2));

    // Calculate Duv deviation (Lfp - Lbb)
    float a = acos((u - 0.292) / Lfp);
    float Lbb = (-0.00616793 * pow(a, 6)) + (0.0893944 * pow(a, 5)) + (-0.5179722 * pow(a, 4)) + (1.5317403 * pow(a, 3)) + (-2.423787 * pow(a, 2)) + (1.925865 * a) + (-0.471106);
    float Duv = Lfp - Lbb;

    // Determine the direction of the tint shift
    char tintDirection = (Duv < 0) ? 'M' : 'G';
    // Display RGB data, color temperature, Duv deviation, and tint direction on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CT:");
    lcd.print(colorTemp);
    lcd.print("K");
    lcd.setCursor(9, 0);
    lcd.print("Lx:");
    lcd.print(lux);
    lcd.setCursor(0, 1);
    lcd.print("Duv: ");
    lcd.print(Duv, 3);
    lcd.print(tintDirection);

    // Wait for button release to prevent multiple captures
    while (digitalRead(BUTTON_PIN) == LOW);
    delay(100); // Debouncing delay
  }
}
