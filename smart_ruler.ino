#include <LiquidCrystal_I2C.h>
#include "Adafruit_VL53L1X.h"
#define IRQ_PIN 2
#define XSHUT_PIN 3
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  Serial.begin(115200);
  Wire.begin();
  if(!vl53.begin(0x29, &Wire)) {
    Serial.println("Error");
  }
  if(!vl53.startRanging()) {
    Serial.println("Error");
  }
  vl53.setTimingBudget(50);
}

void loop() {
  int distance;
  if(vl53.dataReady()){
    distance = vl53.distance();
    lcd.clear();
    if(distance==-1) {
      lcd.print("error");
    }
    lcd.print(((String)distance)+"mm");
    vl53.clearInterrupt();
    delay(1000);
  }
}
