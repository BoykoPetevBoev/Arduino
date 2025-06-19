#include <Wire.h>
#include <DS1302.h>
// #include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_HTU21DF.h>

const int DS1302_CE_PIN = 5;
const int DS1302_IO_PIN = 6;
const int DS1302_SCLK_PIN = 7;
const int BUTTON_PIN = 13;


// dht DHT11;

DS1302 rtc(DS1302_CE_PIN, DS1302_IO_PIN, DS1302_SCLK_PIN);

LiquidCrystal_I2C lcd(0x27, 12, 2);
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

int displayLoop = 0;

void setup() {
  Serial.begin(9600);

  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }

  rtc.writeProtect(false);
  rtc.halt(false);
  Time t(2025, 5, 6, 16, 6, 30, Time::kSunday);
  rtc.time(t);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // pinMode(DS1302_IO_PIN, INPUT);

  lcd.init();
  lcd.backlight();
}


// void showOutsideTemp() {
//   int readData = DHT11.read11(DHT11_PIN);

//   float t = DHT11.temperature;
//   float h = DHT11.humidity;

//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Temp: ");
//   lcd.print(t);
//   lcd.setCursor(0, 1);
//   lcd.print("Humidity: ");
//   lcd.print(h);
// }

void showInsideTemp() {
  float temp = htu.readTemperature();
  float rel_hum = htu.readHumidity();

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C");
  Serial.print("\t\t");
  Serial.print("Humidity: ");
  Serial.print(rel_hum);
  Serial.println(" %");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(rel_hum);
}

void showTime() {
  Time t = rtc.time();

  lcd.clear();
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

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    displayLoop += 1;
    if(displayLoop > 1){
      displayLoop = 0;
    }
    if(displayLoop == 0) {
      lcd.clear();
      lcd.print("Inside Temp");
    }
    // else if(displayLoop == 1) {
    //   lcd.clear();
    //   lcd.print("Outside Temp");
    // }
    else if(displayLoop == 1) {
      lcd.clear();
      lcd.print("Date and Time");
    }
    delay(1000);
  }


  if (displayLoop == 0) {
    showInsideTemp();
  } else {
    showTime();
  }

  delay(1000);
}
