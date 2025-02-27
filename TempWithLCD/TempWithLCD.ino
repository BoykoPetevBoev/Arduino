#include <Wire.h> 
#include <DS1302.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_HTU21DF.h>

const int CE_PIN = 5;
const int IO_PIN = 6;
const int SCLK_PIN = 7;

DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

LiquidCrystal_I2C lcd(0x27,12,2);
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

unsigned long previousMillis = 0;
const long interval = 3000;
bool showTemperature = true;

void setup()
{
  Serial.begin(9600);

  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }

  Time t(2024, 2, 26, 20, 18, 50, Time::kSunday);
  rtc.time(t);

  lcd.init();
  lcd.backlight();
}


void showTemp() {
  float temp = htu.readTemperature();
  float rel_hum = htu.readHumidity();

  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C");
  Serial.print("\t\t");
  Serial.print("Humidity: "); Serial.print(rel_hum); Serial.println(" %");

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(rel_hum);
}


void showTime() {
  Time t = rtc.time();

  Serial.print("Time: "); Serial.print(t.hr);

  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  if (t.hr < 10) lcd.print("0");
  lcd.print(t.hr);
  lcd.print(":");
  if (t.min < 10) lcd.print("0");
  lcd.print(t.min);
  lcd.print(":");
  if (t.sec < 10) lcd.print("0");
  lcd.print(t.sec);
  lcd.print(" ");
  
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  if (t.date < 10) lcd.print("0");
  lcd.print(t.date);
  lcd.print("/");
  if (t.mon < 10) lcd.print("0");
  lcd.print(t.mon);
  lcd.print("/");
  lcd.print(t.yr);
}


void loop()
{
  unsigned long currentMillis = millis();
 if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    showTemperature = !showTemperature;
  }

  if (showTemperature) {
    showTemp();
  } else {
    showTime();
  }
 
  delay(1000);
}
