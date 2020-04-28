#include "RTClib.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int running_index = 0;

void setup () {
  // Serial.begin(57600);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW); // Keep device switched on after PWR button was pressed
  u8g2.begin();
  rtc.begin();
  if (! rtc.initialized()) {
    // Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
  DateTime now = rtc.now();  
  if(running_index < 2) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.setCursor(0, 32);  // Seperate cursor position from print statement
    u8g2.print(now.hour());
    u8g2.print(":");
    if(now.minute() < 10) u8g2.print("0");
    u8g2.print(now.minute());
    u8g2.print(":");
    if(now.second() < 10) u8g2.print("0");
    u8g2.print(now.second());
    u8g2.sendBuffer();
  }
  if(running_index > 1 && running_index < 3) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso22_tr);
    u8g2.setCursor(0, 32);  
    u8g2.print(daysOfTheWeek[now.dayOfTheWeek()]);
    u8g2.print(" ");
    u8g2.print(now.day());
    u8g2.print(".");
    if(now.month() < 10) u8g2.print("0");
    u8g2.print(now.month());
    u8g2.print(".");
    u8g2.sendBuffer();
  }
  delay(1000);
  running_index ++;
  if(running_index > 3) {
    u8g2.setPowerSave(1);
    pinMode(5, INPUT); // Switch device off
  }
}
