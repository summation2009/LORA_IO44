#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- LoRa Pins ----------------
#define LORA_SS    33
#define LORA_RST   -1
#define LORA_DIO0  25

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- Relay Pins ----------------
#define NO1 26
#define NO2 27
#define NO3 14
#define NO4 32

int b1, b2, b3, b4;

void setup() {
  Serial.begin(115200);
  Serial.println("LoRa Receiver with Relay + OLED");

  // ตั้งขารีเลย์เป็น OUTPUT
  pinMode(NO1, OUTPUT);
  pinMode(NO2, OUTPUT);
  pinMode(NO3, OUTPUT);
  pinMode(NO4, OUTPUT);

  // ปิดรีเลย์ทั้งหมดตอนเริ่มต้น
  digitalWrite(NO1, HIGH);
  digitalWrite(NO2, HIGH);
  digitalWrite(NO3, HIGH);
  digitalWrite(NO4, HIGH);

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
    Serial.println("LoRa start failed!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("LoRa Failed!");
    display.display();
    while (1);
  }

  Serial.println("LoRa Receiver Ready");
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Receiver Ready");
  display.display();
}

void loop() {

  int packetSize = LoRa.parsePacket();
  if (packetSize) {

    String incoming = "";
    while (LoRa.available()) incoming += (char)LoRa.read();

    Serial.print("Received: ");
    Serial.println(incoming);

    // ---------------- แปลงข้อความ Relay:x,x,x,x ----------------
    if (incoming.startsWith("Relay:")) {
      incoming.remove(0, 6);   // เอา "Relay:" ออก

      int idx1 = incoming.indexOf(',');
      int idx2 = incoming.indexOf(',', idx1 + 1);
      int idx3 = incoming.indexOf(',', idx2 + 1);

      b1 = incoming.substring(0, idx1).toInt();
      b2 = incoming.substring(idx1 + 1, idx2).toInt();
      b3 = incoming.substring(idx2 + 1, idx3).toInt();
      b4 = incoming.substring(idx3 + 1).toInt();

      // ---------------- ควบคุมรีเลย์ ----------------
      digitalWrite(NO1, b1);
      digitalWrite(NO2, b2);
      digitalWrite(NO3, b3);
      digitalWrite(NO4, b4);

      // ---------------- แสดงบน OLED ----------------
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("OutPut Values:");

      display.setCursor(0, 15);
      display.print("OUT1: "); display.println(b1);

      display.setCursor(0, 30);
      display.print("OUT2: "); display.println(b2);

      display.setCursor(64, 15);
      display.print("OUT3: "); display.println(b3);

      display.setCursor(64, 30);
      display.print("OUT4: "); display.println(b4);

      display.display();
    }
  }
}
