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

// ---------------- ปุ่ม INPUT ----------------
#define INP1 36
#define INP2 39
#define INP3 35
#define INP4 15

int b1, b2, b3, b4; // เก็บค่าสถานะปุ่ม

void setup() {
  Serial.begin(115200);
  Serial.println("Starting LoRa + OLED...");

  pinMode(INP1, INPUT);
  pinMode(INP2, INPUT);
  pinMode(INP3, INPUT);
  pinMode(INP4, INPUT);

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

  // อ่านปุ่ม
  b1 = digitalRead(INP1);
  b2 = digitalRead(INP2);
  b3 = digitalRead(INP3);
  b4 = digitalRead(INP4);

  // เตรียมข้อความส่ง LoRa
  String packet = "Relay:" + String(b1) + "," + String(b2) + "," +
                           String(b3) + "," + String(b4);

  Serial.println("Sending: " + packet);

  // ส่งข้อมูล LoRa
  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();

  // แสดงบน OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("INPUT State:");

  display.setCursor(0, 15);
  display.print("IN1: "); display.println(b1);

  display.setCursor(0, 30);
  display.print("IN2: "); display.println(b2);

  display.setCursor(64, 15);
  display.print("IN3: "); display.println(b3);

  display.setCursor(64, 30);
  display.print("IN4: "); display.println(b4);

  display.display();

  delay(300);
}
