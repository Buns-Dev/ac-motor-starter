// ============================================
// 3-Phase Motor Control - MASTER FINAL VERSION
// ============================================
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define FWD_BTN 2
#define REV_BTN 3
#define STOP_BTN 4
#define EMERGENCY 5

#define FWD_RELAY1 6
#define FWD_RELAY2 7
#define REV_RELAY1 11
#define REV_RELAY2 12

#define GREEN_LED 8
#define YELLOW_LED 9
#define RED_LED 10

#define CURRENT_PIN A1
#define VOLTAGE_PIN A2

const float CURRENT_CALIBRATION = 0.074; 
const float VOLTAGE_CALIBRATION = 3.5;   
const int CURRENT_TRIP_LIMIT = 300;      

enum State { IDLE, FORWARD, REVERSE, LOCKED };
State motorStatus = IDLE;

unsigned long lastLCDUpdate = 0;

void setup() {
  Serial.begin(9600); // Opens communication with laptop
  Serial.println("SYSTEM STARTING...");

  pinMode(FWD_BTN, INPUT_PULLUP);
  pinMode(REV_BTN, INPUT_PULLUP);
  pinMode(STOP_BTN, INPUT_PULLUP);
  pinMode(EMERGENCY, INPUT_PULLUP);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(FWD_RELAY1, OUTPUT);
  pinMode(FWD_RELAY2, OUTPUT);
  pinMode(REV_RELAY1, OUTPUT);
  pinMode(REV_RELAY2, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  updateStatus("STAT: BOOTING...");
  
  stopAll(); 
  delay(1000);
}

void stopAll() {
  digitalWrite(FWD_RELAY1, HIGH);
  digitalWrite(FWD_RELAY2, HIGH);
  digitalWrite(REV_RELAY1, HIGH);
  digitalWrite(REV_RELAY2, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  
  if (motorStatus != LOCKED) {
      motorStatus = IDLE;
      updateStatus("STAT: IDLE      ");
  }
}

void updateStatus(String statusText) {
  lcd.setCursor(0, 0);
  lcd.print(statusText);
  lcd.print("                "); 
  Serial.println(statusText); // Sends current status to laptop
}

void checkSafetySensors() {
  int currentRaw = analogRead(CURRENT_PIN);
  int voltageRaw = analogRead(VOLTAGE_PIN);

  int currentDiff = abs(currentRaw - 512);
  int voltageDiff = abs(voltageRaw - 512);

  if (currentDiff < 5) currentDiff = 0; 
  if (voltageDiff < 8) voltageDiff = 0;

  if (millis() - lastLCDUpdate > 500) {
      float realAmps = currentDiff * CURRENT_CALIBRATION;
      float realVolts = voltageDiff * VOLTAGE_CALIBRATION;

      // Update LCD
      lcd.setCursor(0, 1);
      lcd.print("V:"); lcd.print((int)realVolts); lcd.print("V   "); 
      lcd.setCursor(8, 1);
      lcd.print("I:"); lcd.print(realAmps, 1); lcd.print("A  "); 

      // Update Serial Monitor
      Serial.print("VOLTS: "); Serial.print((int)realVolts);
      Serial.print(" | AMPS: "); Serial.println(realAmps, 1);
      
      lastLCDUpdate = millis();
  }

  if (currentDiff > CURRENT_TRIP_LIMIT && motorStatus != LOCKED && motorStatus != IDLE) {
      stopAll();
      digitalWrite(RED_LED, HIGH);
      motorStatus = LOCKED;
      updateStatus("STAT: OVERLOAD! ");
  }
}

void loop() {
  if (digitalRead(EMERGENCY) == LOW) {
    stopAll();
    digitalWrite(RED_LED, HIGH);
    if (motorStatus != LOCKED) {
        motorStatus = LOCKED;
        updateStatus("STAT: E-STOP!   ");
    }
  }

  checkSafetySensors();

  if (digitalRead(STOP_BTN) == LOW) {
    if (motorStatus == LOCKED) {
        digitalWrite(RED_LED, LOW);
        motorStatus = IDLE;
        updateStatus("STAT: RESETTING ");
        delay(500); 
        updateStatus("STAT: IDLE      ");
    } 
    else if (motorStatus != IDLE) {
        stopAll();
    }
  }

  if (digitalRead(FWD_BTN) == LOW && motorStatus == IDLE) {
    delay(50); 
    if (digitalRead(FWD_BTN) == LOW) {
        updateStatus("STAT: STARTING..");
        digitalWrite(FWD_RELAY1, LOW); 
        delay(100);                    
        digitalWrite(FWD_RELAY2, LOW); 
        digitalWrite(GREEN_LED, HIGH);
        motorStatus = FORWARD;
        updateStatus("STAT: FORWARD   ");
    }
  }

  if (digitalRead(REV_BTN) == LOW && motorStatus == IDLE) {
    delay(50); 
    if (digitalRead(REV_BTN) == LOW) {
        updateStatus("STAT: STARTING..");
        digitalWrite(REV_RELAY1, LOW); 
        delay(100);                    
        digitalWrite(REV_RELAY2, LOW);
        digitalWrite(YELLOW_LED, HIGH);
        motorStatus = REVERSE;
        updateStatus("STAT: REVERSE   ");
    }
  }
}
