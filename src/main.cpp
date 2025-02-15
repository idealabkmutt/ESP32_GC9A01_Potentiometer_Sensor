#include <SPI.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Ticker.h>

#define Height 240
#define Width 240
#define Pot 34
#define Button1 5
#define Button2 16

TFT_eSPI tft = TFT_eSPI();
Adafruit_BMP280 bmp;
Ticker displayTicker;

volatile bool updateDisplay = false;
int displayMode = 0;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 150;  // ตั้งดีเลย์ให้มากพอ

void updateDisplayFlag() {
  updateDisplay = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(Pot, INPUT);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setFreeFont(&FreeSansBold24pt7b);
  tft.setTextPadding(250);

  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found!");
    while (1);
  }

  displayTicker.attach(0.5, updateDisplayFlag);
}

void loop() {
  // อ่านค่าปุ่ม
  bool buttonState = digitalRead(Button1) == LOW && digitalRead(Button2) == HIGH;

  // ตรวจสอบว่าปุ่มถูกกดและ debounce delay ผ่านไปแล้ว
  if (buttonState && !lastButtonState && (millis() - lastDebounceTime > debounceDelay)) {
    displayMode = (displayMode + 1) % 4;  // วนลูป 0 → 1 → 2 → 3 → 0
    updateDisplay = true;
    lastDebounceTime = millis();  // อัปเดตเวลา debounce
  }
  lastButtonState = buttonState;

  if (updateDisplay) {
    updateDisplay = false;
    tft.fillScreen(TFT_BLACK);

    int rawValue = analogRead(Pot);
    float Value = (4095.0 - rawValue) / 4095.0 * 100.0;

    switch (displayMode) {
      case 0:
        tft.drawString("Rotary:", Width / 2, Height / 3);
        tft.drawFloat(Value, 2, Width / 2, Height / 2);
        break;
      case 1:
        tft.drawString("Altitude:", Width / 2, Height / 3);
        tft.drawFloat(bmp.readAltitude(1013.25), 2, Width / 2, Height / 2);
        break;
      case 2:
        tft.drawString("Pressure:", Width / 2, Height / 3);
        tft.drawFloat(bmp.readPressure() / 100.0, 2, Width / 2, Height / 2);
        break;
      case 3:
        tft.drawString("Temperature:", Width / 2, Height / 3);
        tft.drawFloat(bmp.readTemperature(), 2, Width / 2, Height / 2);
        break;
    }

    Serial.print("Mode: "); Serial.print(displayMode);
    Serial.print(" | Temp: "); Serial.print(bmp.readTemperature());
    Serial.print(" | Pressure: "); Serial.print(bmp.readPressure() / 100.0);
    Serial.print(" | Altitude: "); Serial.print(bmp.readAltitude(1013.25));
    Serial.print(" | Rotary: "); Serial.println(Value);
  }
}
