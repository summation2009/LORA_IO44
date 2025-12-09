#include <Arduino.h>

#define INP1 36 //
#define INP2 39 //
#define INP3 35 //
#define INP4 15 //

#define NO1 26 //
#define NO2 27 //
#define NO3 14 //
#define NO4 32 //

#define DIP1 4 //
#define DIP2 5 //
#define DIP3 13 //
#define DIP4 14 //
#define DIP5 15 //
#define DIP6 32 //
#define DIP7 33 //
#define DIP8 34 //

void setup() {
  Serial.begin(115200);

  pinMode(INP1, INPUT_PULLUP);
  pinMode(INP2, INPUT_PULLUP);
  pinMode(INP3, INPUT_PULLUP);
  pinMode(INP4, INPUT_PULLUP);

  pinMode(NO1, OUTPUT);
  pinMode(NO2, OUTPUT);
  pinMode(NO3, OUTPUT);
  pinMode(NO4, OUTPUT);

  pinMode(DIP1, INPUT_PULLUP);
  pinMode(DIP2, INPUT_PULLUP);
  pinMode(DIP3, INPUT_PULLUP);
  pinMode(DIP4, INPUT_PULLUP);
  pinMode(DIP5, INPUT_PULLUP);
  pinMode(DIP6, INPUT_PULLUP);
  pinMode(DIP7, INPUT_PULLUP);
  pinMode(DIP8, INPUT_PULLUP);

  digitalWrite(NO1, HIGH);
  digitalWrite(NO2, HIGH);
  digitalWrite(NO3, HIGH);
  digitalWrite(NO4, HIGH);
}

void loop() {


//  digitalWrite(INP4, LOW);
// delay(500);
// digitalWrite(INP4, HIGH);

  // อ่านค่าจาก INP
  int inp1 = digitalRead(INP1);
  int inp2 = digitalRead(INP2);
  int inp3 = digitalRead(INP3);
  int inp4 = digitalRead(INP4);

  // ถ้า INP = LOW -> NO = LOW
  // ถ้า INP = HIGH -> NO = HIGH
  digitalWrite(NO1, inp1);
  digitalWrite(NO2, inp2);
  digitalWrite(NO3, inp3);
  digitalWrite(NO4, inp4);

  // อ่านค่า DIP switch (Active LOW → ON = 0, OFF = 1)
  int dip1 = digitalRead(DIP1);
  int dip2 = digitalRead(DIP2);
  int dip3 = digitalRead(DIP3);
  int dip4 = digitalRead(DIP4);
  int dip5 = digitalRead(DIP5);
  int dip6 = digitalRead(DIP6);
  int dip7 = digitalRead(DIP7);
  int dip8 = digitalRead(DIP8);

  // แสดงผลทั้งหมด
  Serial.print("INP: ");
  Serial.print(inp1); Serial.print(" ");
  Serial.print(inp2); Serial.print(" ");
  Serial.print(inp3); Serial.print(" ");
  Serial.print(inp4);
  
  Serial.print(" | DIP: ");
  Serial.print(dip1);
  Serial.print(dip2);
  Serial.print(dip3);
  Serial.print(dip4);
  Serial.print(dip5);
  Serial.print(dip6);
  Serial.print(dip7);
  Serial.println(dip8);

  delay(200);
}
