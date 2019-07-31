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

    //TODO: confirm order of cursor (row, col) or (col,row)
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.write("Ts: ");
    lcd.setCursor(0, 9)
    lcd.write("Ta:");
    lcd.setCursor(1, 0);
    lcd.write("Humidity:");
    lcd.setCursor(1, 14);
    lcd.write("%");
        lcd.setCursor(0, 4)
        lcd.write(buf[0])
      }

      if (i == 1) {
        lcd.setCursor(0, 12)
        lcd.write(buf[1])
      }

      if (i == 2) {
        lcd.setCursor(1, 10)
        lcd.write(buf[2])
      }
    }



    // Message with a good checksum received, display it



    //lcd.setCursor(3, 0);
    //Serial.println(buf[0]);

    //  char hum_val[3];
    //itoa(buf[0], hum_val, 10);
    //lcd.write(hum_val);
  }
}
