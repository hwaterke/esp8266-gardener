#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Nokia 5110            Feather Huzzah
// 1 - RST               PIN 4
// 2 - CE                PIN 5
// 3 - DC                12
// 4 - DIN               13
// 5 - CLK               14
// 6 - VCC 3V
// 7 - Backlight        15
// 8 - GND

const int8_t BACK_LIGHT_PIN = 15;

#define DHT_22 2

DHT_Unified dht(DHT_22, DHT22);

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 12, 5, 4);

// TODO Move to hardware SPI
// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

void setup()
{
  Serial.begin(9600);

  // Turn LCD backlight on
  pinMode(BACK_LIGHT_PIN, OUTPUT);
  digitalWrite(BACK_LIGHT_PIN, LOW);

  dht.begin();
  display.begin();
  display.setContrast(50);
}

void loop()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);

  sensors_event_t event;

  dht.temperature().getEvent(&event);
  display.println("Temperature");
  display.println(event.temperature);

  dht.humidity().getEvent(&event);
  display.println("Humidity");
  display.println(event.relative_humidity);

  display.display();
  delay(4000);
}
