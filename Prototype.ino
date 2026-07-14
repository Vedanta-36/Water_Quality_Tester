#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//All the pin locations for each electrical component
int redLED = 4;
int yellowLED = 3;
int greenLED = 2;

int buzzer = 5;

int turbidityPin = A0;
int waterLevelPin = A1;  

// Values taken from external sensors and then placed here
float pH = 7.2;
int TDS = 300;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  int turbidity = analogRead(turbidityPin);
  int conductivityProxy = analogRead(waterLevelPin);

  Serial.print("Turbidity: ");
  Serial.print(turbidity);
  Serial.print("  ConductivityProxy: ");
  Serial.println(conductivityProxy);

  // Display values
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(turbidity);

  lcd.setCursor(8, 0);
  lcd.print("C:");
  lcd.print(conductivityProxy);

  lcd.setCursor(0, 1);

  //UNSAFE

  if (turbidity > 600 || conductivityProxy > 700 || pH < 5.5 || pH > 8.5 || TDS > 1000) {

    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);

    lcd.print("UNSAFE WATER ");

    digitalWrite(buzzer, HIGH);
  }

  //  MODERATE
  else if (turbidity > 300 || conductivityProxy > 400 || pH < 6.5 || pH > 8.0 || TDS > 500) {

    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);

    lcd.print("MODERATE WATER");

    digitalWrite(buzzer, HIGH);
    delay(150);
    digitalWrite(buzzer, LOW);
  }

  // SAFE
  else {

    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);

    lcd.print("SAFE WATER    ");

    digitalWrite(buzzer, LOW);
  }

  delay(1000);
}