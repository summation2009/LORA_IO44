#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- กำหนดขา LoRa ----------------
#define LORA_SS    33
#define LORA_RST   -1
#define LORA_DIO0  25

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting LoRa + OLED...");

  // ---------------- OLED Start ----------------
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("OLED failed");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(23, 20);
  display.println("SUMTECH");
  display.display();
  delay(1000);

  // ---------------- LoRa Start ----------------
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("LoRa Failed!");
    display.display();
    while (1);
  }

  Serial.println("Sending LoRa Ready");
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Sending LoRa Ready");
  display.display();
}

void loop() {
  String message = "Hello LoRa!";

  Serial.println("Sending: " + message);

  // ส่ง LoRa
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  // แสดงบน OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Sending LoRa:");
  display.setCursor(0, 15);
  display.println(message);
  display.display();

  delay(1000);
}
