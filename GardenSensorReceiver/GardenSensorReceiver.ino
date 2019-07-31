#include <RH_ASK.h>
#include <LiquidCrystal.h>
#include <SPI.h> // Not actually used but needed to compile

#define HUM_SENSOR_WET 80
#define HUM_SENSOR_DRY 160

RH_ASK driver;
LiquidCrystal lcd(7, 8, 9, 10, 6 , 12);
int i = 0;
void setup()
{
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("Ts:   C Ta:   C");

  //lcd.write("Ta:");
  lcd.setCursor(0, 1);
  lcd.write("Humidity:    %");
}

void loop()
{


  uint8_t buf[12];

  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    // (col,row)
    Serial.print(buf[0] );
    Serial.print( buf[1] );
    Serial.print( buf[2] );
// TODO if statement for single digit to double digit humidity level change % position
    lcd.setCursor(10, 1);
    char Humidity [4];
    itoa(25, Humidity, 10);
    lcd.write({Humidity});

    lcd.setCursor(4, 0);
    char ts [2];
    itoa(buf[1], ts, 10);
    lcd.write({ts});

    lcd.setCursor(12, 0);
    char ta [2] ;
    itoa(buf[2], ta, 10);
    lcd.write({ta});

  }
}

uint8_t get_calibrated_humidity(uint8_t sens_val) {
  uint8_t range = HUM_SENSOR_DRY - HUM_SENSOR_WET;
  uint8_t how_wet = HUM_SENSOR_DRY - sens_val;
  uint8_t percent = how_wet * 100 / range;
  return percent;
}
