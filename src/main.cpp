#include <Arduino.h>
#include <LiquidCrystalRus.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystalRus lcd(13, 12, 11, 10, 9, 8);
Adafruit_BMP085 bmp;
DHT dht(7, DHT11);
OneWire oneWire(6);
DallasTemperature sensors(&oneWire);

byte degreeSign[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
};

void setup() {
    lcd.createChar(0, degreeSign);
    lcd.begin(16, 2);
    dht.begin();
    bmp.begin();
    sensors.begin();
}

void loop() {
    float h = dht.readHumidity();
    float pressure = (bmp.readPressure() / 101.325) * 0.760;
    sensors.requestTemperatures();

    lcd.setCursor(1, 0);
    lcd.print("Дом:   ");
    lcd.print(bmp.readTemperature(), 1);
    lcd.write(byte(0));
    lcd.print("C");
    lcd.setCursor(1, 1);
    lcd.print("Улица: ");
    lcd.print(sensors.getTempCByIndex(0), 1);
    lcd.write(byte(0));
    lcd.print("C");

    _delay_ms(5000);

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Влажнoсть:");
    lcd.print(h, 0);
    lcd.print("%");

    lcd.setCursor(1, 1);
    lcd.print("Атм.давл.:");
    lcd.print(pressure, 0);

    _delay_ms(5000);

    lcd.clear();
}
