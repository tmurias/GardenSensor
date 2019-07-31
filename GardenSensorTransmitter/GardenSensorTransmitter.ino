#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 14

RH_ASK driver;
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

int numberOfDevices; // Number of temperature devices found

void setup()
{
  Serial.begin(9600);    // Debugging only
  if (!driver.init())
    Serial.println("init failed");


  sensors.begin(); // Start up the library
  numberOfDevices = sensors.getDeviceCount();   // Grab a count of devices on the wire

  Serial.println("Done setup");
}

void loop()
{
  // Read humidity sensor
  int hum_sens_val = analogRead(A1);
  uint8_t hum_byte = (hum_sens_val + 1) / 4 - 1; //converting to byte (1023 -> 255)

  // If it's 255 that means it looped around
  if (hum_byte == 255) {
    hum_byte = 0;
  }

  uint8_t temps[2] = {0, 0};
  get_temperatures(temps);

  Serial.print("Humidity: ");
  Serial.println(hum_byte);
  Serial.print("Temp1: ");
  Serial.println(temps[0]);
  Serial.print("Temp2: ");
  Serial.println(temps[1]);

  const uint8_t msg[12] = {hum_byte, temps[0], temps[1], 0, 0, 0, 0, 0, 0, 0, 0, 0};
  
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  
  delay(5000);
}

void get_temperatures(uint8_t* values)
{
  float offset = 50;
  sensors.requestTemperatures(); // Send the command to get temperatures

  // Loop through each device, print out temperature data
  for (int i = 0; i < numberOfDevices; i++) {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i)) {

      float t = sensors.getTempC(tempDeviceAddress);
      //convert to byte
      if ( t > 50 ) {
        t = 50 ;
      }
      if ( t < -50 ) {
        t = -50  ;
      }

      t = t + offset;

      values[i] = (uint8_t)t;
    }
  }
}
