#include <RH_ASK.h>
#include <LiquidCrystal.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
LiquidCrystal lcd(7, 8, 9, 10, 6 , 12);

void setup()
{
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    // Message with a good checksum received, display it
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.write("VALUE: ");
    lcd.setCursor(7, 0);
    char hum_val[3];
    itoa(buf[0], hum_val, 10);
    lcd.write(hum_val);
  }
}
