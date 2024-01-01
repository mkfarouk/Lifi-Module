#include <LiquidCrystal.h>

#define DO_PIN 7    // Arduino's pin connected to DO pin of the LDR module
#define LED_PIN 13  // Arduino's pin connected to the LED
#define BUTTON_PIN 8 // Arduino's pin connected to the button

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long lightStartTime = 0;
unsigned long lightElapsedTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(DO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // Set LED pin as output
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button pin as input with pull-up resistor
  lcd.begin(16, 2);
}

void loop() {
  int lightState = digitalRead(DO_PIN);
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState==LOW){
    delay(5000); // Keep the LED on for 5 seconds
    digitalWrite(LED_PIN, LOW); // Turn off the LED
    lcd.clear();
  }
  if (lightState == LOW) {
    if (lightStartTime == 0) {
      lightStartTime = millis();
    }
  } else {
    if (lightStartTime > 0) {
      lightElapsedTime = millis() - lightStartTime;
      lightStartTime = 0;
      lcd.clear();

      if (lightElapsedTime >= 2500 && lightElapsedTime < 3500) {
        lcd.print("Fire is detected");
        digitalWrite(LED_PIN, HIGH); // Turn on the LED
      } else if (lightElapsedTime >= 5500 && lightElapsedTime < 6500) {
        lcd.print("Door is opened");
        digitalWrite(LED_PIN, HIGH); // Turn on the LED
      } else if (lightElapsedTime >= 8500 && lightElapsedTime < 9500) {
        lcd.print("Intrusion is ");
        lcd.setCursor(0, 1);
        lcd.print("detected");
        digitalWrite(LED_PIN, HIGH); // Turn on the LED
      }
    }
  }
  delay(100);
}
